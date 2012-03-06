#include <v8.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <Athena-Core/Utils/StringUtils.h>
#include <string>

using namespace v8;
using namespace Athena::Scripting;
using namespace Athena::Utils;


/*********************************** EXTERNAL FUNCTIONS *********************************/

extern bool bind_Base(Handle<Object> parent);
extern bool bind_Derived(Handle<Object> parent);


/*************************************** FUNCTIONS **************************************/

Handle<Value> sum(const Arguments& args)
{
    HandleScope handle_scope;

    int result = args[0]->ToInt32()->Value() + args[1]->ToInt32()->Value();

    return handle_scope.Close(Int32::New(result));
}


Handle<Value> raiseException(const Arguments& args)
{
    return ThrowException(String::New("Something bad happened!"));
}


/****************************** INITIALISATION OF THE MODULE ****************************/

extern "C" {

    bool MODULE_INITIALISATION_FUNCTION init_module(Handle<Object> parent, const std::string& modulePath)
    {
        HandleScope handle_scope;

        // Bind the 'sum' function
        if (!parent->Set(String::New("sum"), FunctionTemplate::New(sum)->GetFunction()) ||
            !parent->Set(String::New("raiseException"), FunctionTemplate::New(raiseException)->GetFunction()))
            return false;

        // Bind the classes
        if (!bind_Base(parent) ||
            !bind_Derived(parent))
            return false;

        // Load the 'Point3D.js' script
        Handle<Value> result;

#if ATHENA_PLATFORM == ATHENA_PLATFORM_WIN32
        if (!StringUtils::endsWith(modulePath, "test\\"))
#else
        if (!StringUtils::endsWith(modulePath, "test/"))
#endif
        {
            result = ScriptingManager::getSingletonPtr()->executeFile(
                                                                modulePath + "js/module1/Point3D.js",
                                                                Context::GetCurrent());
        }
        else
        {
            result = ScriptingManager::getSingletonPtr()->executeFile(
                                                                modulePath + "js/module2/Point3D.js",
                                                                Context::GetCurrent());
        }

        if (result.IsEmpty())
            return false;

        return true;
    }

}
