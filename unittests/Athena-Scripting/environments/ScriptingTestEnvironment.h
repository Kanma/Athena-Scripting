#ifndef _SCRIPTINGTESTENVIRONMENT_H_
#define _SCRIPTINGTESTENVIRONMENT_H_

#include <Athena-Scripting/ScriptingManager.h>


struct ScriptingTestEnvironment
{
    Athena::Scripting::ScriptingManager* pScriptingManager;

	ScriptingTestEnvironment()
	: pScriptingManager(0)
	{
        pScriptingManager = new Athena::Scripting::ScriptingManager();
	}

	~ScriptingTestEnvironment()
	{
        delete pScriptingManager;
	}
};


#endif
