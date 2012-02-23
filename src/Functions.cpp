/** @file   functions.cpp
    @author Philip Abbet

    Implementation of the custom global functions
*/

#include <Athena-Scripting/Functions.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <v8.h>
#include <iostream>

using namespace Athena::Scripting;
using namespace std;
using namespace v8;


namespace Athena {
namespace Scripting {


Handle<Value> Print(const Arguments& args)
{
    HandleScope handle_scope;

    bool first = true;

    for (int i = 0; i < args.Length(); ++i)
    {
        if (first)
            first = false;
        else
            cout << " ";

        String::AsciiValue str(args[i]);

        cout << *str;
    }

    return Undefined();
}

//-----------------------------------------------------------------------

Handle<Value> Import(const Arguments& args)
{
    assert(ScriptingManager::getSingletonPtr());

    HandleScope handle_scope;

    String::AsciiValue str(args[0]);

    return handle_scope.Close(Boolean::New(ScriptingManager::getSingletonPtr()->import(*str, Context::GetCurrent())));
}

//-----------------------------------------------------------------------

Handle<Value> Load(const Arguments& args)
{
    assert(ScriptingManager::getSingletonPtr());

    HandleScope handle_scope;

    String::AsciiValue str(args[0]);

    Handle<Value> result = ScriptingManager::getSingletonPtr()->executeFile(*str, Context::GetCurrent());
    if (result.IsEmpty())
        return Null();

    return handle_scope.Close(result);
}

}
}
