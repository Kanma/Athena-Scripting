#include <v8.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <string>

using namespace v8;
using namespace Athena::Scripting;


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

    bool init_module(Handle<Object> parent, const std::string& modulePath)
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
        Handle<Value> result = ScriptingManager::getSingletonPtr()->executeFile(
                                                                modulePath + "js/Point3D.js",
                                                                Context::GetCurrent());
        if (result.IsEmpty())
            return false;

        return true;
    }

}
