/**	@file	ScriptingManager.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Scripting::ScriptingManager'
*/

#include <Athena-Scripting/ScriptingManager.h>
#include <Athena-Core/Log/LogManager.h>
#include <iostream>


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
	
	// Create the main context
    m_mainContext = Context::New();
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

Handle<Value> ScriptingManager::execute(const std::string& strScript, Persistent<Context> context)
{
    m_strLastError = "";

    // Create a stack-allocated handle scope
    HandleScope handle_scope;

    // Retrieve the context to use
    if (context.IsEmpty())
        context = m_mainContext;
  
    // Enter the context for compiling and running the script 
    Context::Scope context_scope(context);

    // Create a string containing the JavaScript source code
    Handle<String> source = String::New(strScript.c_str(), strScript.size());

    // Compile the source code
    Handle<Script> script = Script::Compile(source);
  
    // Run the script to get the result
    TryCatch trycatch;
    Handle<Value> result = script->Run();
    if (result.IsEmpty())
    {  
        Handle<Value> exception = trycatch.Exception();
        String::AsciiValue exception_str(exception);
        m_strLastError = *exception_str;
    	ATHENA_LOG_ERROR(m_strLastError);
        return Handle<Value>();
    }

    // Return the result
    return handle_scope.Close(result);
}
