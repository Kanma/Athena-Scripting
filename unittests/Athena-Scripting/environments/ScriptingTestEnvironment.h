#ifndef _SCRIPTINGTESTENVIRONMENT_H_
#define _SCRIPTINGTESTENVIRONMENT_H_

#include <Athena-Scripting/ScriptingManager.h>


struct ScriptingTestEnvironment
{
    Athena::Scripting::ScriptingManager* pScriptingManager;
    v8::Persistent<v8::Context>          context;

    ScriptingTestEnvironment()
    : pScriptingManager(0)
    {
        pScriptingManager = new Athena::Scripting::ScriptingManager();
    }

    ~ScriptingTestEnvironment()
    {
        if (!context.IsEmpty())
            context.Dispose();

        delete pScriptingManager;
    }
};


#endif
