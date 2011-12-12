#include <UnitTest++.h>
#include <Athena-Scripting/ScriptingManager.h>
#include "environments/ScriptingTestEnvironment.h"
#include <iostream>


using namespace Athena::Scripting;
using namespace v8;


TEST(ScriptingManager_Singleton)
{
	CHECK(!ScriptingManager::getSingletonPtr());
	
	ScriptingManager* pScriptingManager = new ScriptingManager();
	CHECK(pScriptingManager);
	CHECK(pScriptingManager == ScriptingManager::getSingletonPtr());

	delete pScriptingManager;
	CHECK(!ScriptingManager::getSingletonPtr());
}


#define USE_MAIN_CONTEXT
#include "test_ScriptingManager_impl.cpp"

#undef USE_MAIN_CONTEXT
#include "test_ScriptingManager_impl.cpp"
