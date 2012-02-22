/**	@file	ScriptingManager.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Scripting::ScriptingManager'
*/

#include <Athena-Scripting/ScriptingManager.h>
#include <Athena-Scripting/Functions.h>
#include <Athena-Core/Log/LogManager.h>
#include <Athena-Core/Utils/StringUtils.h>
#include <Athena-Core/Utils/StringConverter.h>
#include <iostream>
#include <fstream>
#include <sys/types.h> 
#include <sys/stat.h> 

#if ATHENA_PLATFORM == ATHENA_PLATFORM_WIN32
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#else
#   include <dlfcn.h>
#endif


#if ATHENA_PLATFORM == ATHENA_PLATFORM_WIN32
#    define DYNLIB_HANDLE           hInstance
#    define DYNLIB_LOAD( a )        LoadLibraryEx( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#    define DYNLIB_GETSYM( a, b )   GetProcAddress( a, b )
#    define DYNLIB_UNLOAD( a )      !FreeLibrary( a )

struct HINSTANCE__;
typedef struct HINSTANCE__* hInstance;

#else
#    define DYNLIB_HANDLE           void*
#    define DYNLIB_LOAD( a )        dlopen( a, RTLD_NOW | RTLD_LOCAL )
#    define DYNLIB_GETSYM( a, b )   dlsym( a, b )
#    define DYNLIB_UNLOAD( a )      dlclose( a )

#endif


using namespace Athena::Scripting;
using namespace Athena::Utils;
using namespace Athena::Log;
using namespace std;
using namespace v8;


/************************************** CONSTANTS ***************************************/

/// Context used for logging
static const char* __CONTEXT__ = "Scripting manager";


/********************************** STATIC ATTRIBUTES ***********************************/

/// The instance of the singleton
template<> ScriptingManager* Singleton<ScriptingManager>::ms_Singleton = 0;



/****************************** CONSTRUCTION / DESTRUCTION ******************************/

ScriptingManager::ScriptingManager()
{
	ATHENA_LOG_EVENT("Creation");

    // Create the global template
    HandleScope handle_scope;
	
	// Create the main context
    m_mainContext = createContext();
}

//-----------------------------------------------------------------------

ScriptingManager::~ScriptingManager()
{
	ATHENA_LOG_EVENT("Destruction");

    // Dispose the main context
    m_mainContext.Dispose();
}

//-----------------------------------------------------------------------

ScriptingManager& ScriptingManager::getSingleton()
{
	assert(ms_Singleton);
	return *ms_Singleton;
}

//-----------------------------------------------------------------------

ScriptingManager* ScriptingManager::getSingletonPtr()
{
	return ms_Singleton;
}


/**************************************** METHODS ***************************************/

Handle<Value> ScriptingManager::execute(const std::string& strScript,
                                        const std::string& strSourceName,
                                        Handle<Context> context)
{
    // Assertions
    assert(!strScript.empty());

    // Initialisations
    m_strLastError = "";

    // Create a stack-allocated handle scope
    HandleScope handle_scope;
    TryCatch trycatch;

    // Retrieve the context to use
    if (context.IsEmpty())
        context = m_mainContext;
  
    // Enter the context for compiling and running the script 
    Context::Scope context_scope(context);

    // Create a string containing the JavaScript source code
    Handle<String> sourceCode = String::New(strScript.c_str(), strScript.size());

    // Create a string containing the origin of the source code
    Handle<String> origin;
    
    if (!strSourceName.empty())
        origin = String::New(strSourceName.c_str(), strSourceName.size());
    else
        origin = String::New("<unknown>", 9);

    // Compile the source code
    Handle<Script> script = Script::Compile(sourceCode, origin);
    if (script.IsEmpty())
    {   
        Handle<Value> exception = trycatch.Exception();
        String::AsciiValue exception_str(exception);
        m_strLastError = *exception_str;
    	ATHENA_LOG_ERROR(m_strLastError);
        return Handle<Value>();
    }
  
    // Run the script to get the result
    Handle<Value> result = script->Run();
    if (result.IsEmpty())
    {  
        Handle<Message> message = trycatch.Message();
        m_strLastError = *String::AsciiValue(message->GetScriptResourceName());
        m_strLastError += ":";
        m_strLastError += StringConverter::toString(message->GetLineNumber());
        m_strLastError += ": ";
        m_strLastError += *String::AsciiValue(message->Get());
        
    	ATHENA_LOG_ERROR(m_strLastError);

        return Handle<Value>();
    }

    // Return the result
    return handle_scope.Close(result);
}


Handle<Value> ScriptingManager::executeFile(const std::string& strFileName, Handle<Context> context)
{
    // Assertions
    assert(!strFileName.empty());

    // Declarations
    std::ifstream stream;
    
    // Open the file
    stream.open(strFileName.c_str(), ios_base::in);
    if (!stream.is_open())
    {
        m_strLastError = "Can't find the file '" + strFileName + "'";
    	ATHENA_LOG_ERROR(m_strLastError);
        return Handle<Value>();
    }

    // Load the content
    stream.seekg(0, std::ios::end);
    size_t size = stream.tellg();
    stream.seekg(0, std::ios::beg);

    char* pBuffer = new char[size + 1];
    pBuffer[size] = 0;
    stream.read(pBuffer, size);
	
    stream.close();

    // Execute the script
    Handle<Value> result = execute(pBuffer, strFileName, context);

    delete[] pBuffer;

    return result;
}


bool ScriptingManager::import(const std::string& strModuleName, v8::Handle<v8::Context> context)
{
    // Assertions
    assert(!strModuleName.empty());

    // Declarations
    DYNLIB_HANDLE                   handle;
    tModuleInitialisationFunction*  init_function;
    string                          strLibraryPath = "modules/";
    string                          strLibraryName = "";

    // Initialisations
    m_strLastError = "";

    StringUtils::tStringsList parts = StringUtils::split(strModuleName, ".");

    // Retrieve the context to use
    if (context.IsEmpty())
        context = m_mainContext;

    Context::Scope context_scope(context);

    // Retrieve or create the necessary namespace(s)
    Handle<Object> ns = context->Global();
    for (unsigned int i = 0; i < parts.size(); ++i)
    {
        Handle<String> name = String::New(parts[i].c_str());
        
        Handle<Value> ns2;
        
        if (ns->Has(name))
        {
            if (i == parts.size() - 1)
                return true;
            
            ns2 = ns->Get(name);
        }
        else
        {
            ns2 = Object::New();
            ns->Set(name, ns2);
        }
        
        ns = ns2->ToObject();
    }

    // Retrieve the path to the dynamic library
#if ATHENA_PLATFORM == ATHENA_PLATFORM_WIN32
    if (!StringUtils::endsWith(strLibraryPath, "\\"))
        strLibraryPath += "\\";
#else
    if (!StringUtils::endsWith(strLibraryPath, "/"))
        strLibraryPath += "/";
#endif

    for (int i = 0; i < parts.size() - 1; ++i)
        strLibraryPath += parts[i] + "/";
    
#if ATHENA_PLATFORM == ATHENA_PLATFORM_WIN32
    strLibraryName = strLibraryPath + parts[parts.size() - 1] + ".dll";
#elif ATHENA_PLATFORM == ATHENA_PLATFORM_APPLE
    strLibraryName = strLibraryPath + "lib" + parts[parts.size() - 1] + ".dylib";
#else
    strLibraryName = strLibraryPath + parts[parts.size() - 1] + ".so";
#endif

    // Load the dynamic library
    struct stat fileInfo;
    if (stat(strLibraryName.c_str(), &fileInfo) != 0)
    {
        m_strLastError = "Failed to find the module '" + strLibraryName + "')";
    	ATHENA_LOG_ERROR(m_strLastError);
        return false;
    }

    handle = DYNLIB_LOAD(strLibraryName.c_str());

    if (!handle)
    {
#if ATHENA_PLATFORM != ATHENA_PLATFORM_WIN32
        const char* e = dlerror();
        if (e)
            m_strLastError = e;
        else
#endif
            m_strLastError = "Failed to load the module '" + strLibraryName + "'";

    	ATHENA_LOG_ERROR(m_strLastError);

        return false;
    }

    // Retrieve the initialisation function of the module
    init_function = (tModuleInitialisationFunction*) DYNLIB_GETSYM(handle, "init_module");
    if (!init_function)
    {
        int ret = DYNLIB_UNLOAD(handle);
        m_strLastError = "No initialisation function found in the module '" + strLibraryName + "'";
    	ATHENA_LOG_ERROR(m_strLastError);
        return false;
    }

    // Initialise the module
    return init_function(ns, strLibraryPath);
}


Persistent<Context> ScriptingManager::createContext()
{
	// Create the context and enter it
    Persistent<Context> context = Context::New();
    Context::Scope context_scope(context);

    // Retrieve the global object
    Handle<Object> global = context->Global();

    // Bind our global functions
    global->Set(String::New("print"), FunctionTemplate::New(Print)->GetFunction());
    global->Set(String::New("import_module"), FunctionTemplate::New(Import)->GetFunction());
    global->Set(String::New("load"), FunctionTemplate::New(Load)->GetFunction());

    // Create the 'Athena.Scripting' namespace
    Handle<Object> ns1 = Object::New();
    global->Set(String::New("Athena"), ns1);

    Handle<Object> ns2 = Object::New();
    ns1->Set(String::New("Scripting"), ns2);

    // Bind the library version
    ns2->Set(String::New("VERSION"), String::New(Athena::Scripting::VERSION));

    return context;
}
