#ifdef USE_MAIN_CONTEXT
SUITE(JSFunctionsTests_UsingMainContext)
#else
SUITE(JSFunctionsTests_UsingOwnContext)
#endif
{
	TEST_FIXTURE(ScriptingTestEnvironment, Print)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result = pScriptingManager->execute("print('Hello from JavaScript\\n');", context);

        CHECK(!result.IsEmpty());
        CHECK(result->IsUndefined());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ImportUnknownModule)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result = pScriptingManager->execute("import_module('unknown');", context);

        CHECK(!result.IsEmpty());
        CHECK(result->IsBoolean());
        CHECK(!result->ToBoolean()->Value());
        CHECK(!pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ImportModuleFromRootFolder)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result = pScriptingManager->execute("import_module('module1');", context);

        CHECK(!result.IsEmpty());
        CHECK(result->IsBoolean());
        CHECK(result->ToBoolean()->Value());
        CHECK(pScriptingManager->getLastError().empty());

		result = pScriptingManager->execute("module1.sum(10, 5);", context);

        CHECK(!result.IsEmpty());
        CHECK(!result->ToInt32().IsEmpty());
        CHECK_EQUAL(15, result->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ImportModuleFromSubFolder)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result = pScriptingManager->execute("import_module('test.module2');", context);

        CHECK(!result.IsEmpty());
        CHECK(result->IsBoolean());
        CHECK(result->ToBoolean()->Value());
        CHECK(pScriptingManager->getLastError().empty());

		result = pScriptingManager->execute("test.module2.sum(10, 5);", context);

        CHECK(!result.IsEmpty());
        CHECK(!result->ToInt32().IsEmpty());
        CHECK_EQUAL(15, result->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ImportTwoModulesFromOneSubFolder)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result = pScriptingManager->execute("import_module('test.module2');", context);

        CHECK(!result.IsEmpty());
        CHECK(result->IsBoolean());
        CHECK(result->ToBoolean()->Value());
        CHECK(pScriptingManager->getLastError().empty());

		result = pScriptingManager->execute("import_module('test.module3');", context);

        CHECK(!result.IsEmpty());
        CHECK(result->IsBoolean());
        CHECK(result->ToBoolean()->Value());
        CHECK(pScriptingManager->getLastError().empty());

        result = pScriptingManager->execute("test.module2.sum(10, test.module3.sum(20, 30));", context);

        CHECK(!result.IsEmpty());
        CHECK(!result->ToInt32().IsEmpty());
        CHECK_EQUAL(60, result->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ImportAlreadyLoadedModule)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result = pScriptingManager->execute("import_module('module1');", context);

        CHECK(!result.IsEmpty());
        CHECK(result->IsBoolean());
        CHECK(result->ToBoolean()->Value());
        CHECK(pScriptingManager->getLastError().empty());

		result = pScriptingManager->execute("import_module('module1');", context);

        CHECK(!result.IsEmpty());
        CHECK(result->IsBoolean());
        CHECK(result->ToBoolean()->Value());
        CHECK(pScriptingManager->getLastError().empty());

		result = pScriptingManager->execute("module1.sum(10, 5);", context);

        CHECK(!result.IsEmpty());
        CHECK(!result->ToInt32().IsEmpty());
        CHECK_EQUAL(15, result->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, LoadUnknownFile)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result = pScriptingManager->execute("load('unknown.js');", context);

        CHECK(!result.IsEmpty());
        CHECK(result->IsNull());
        CHECK(!pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, Load)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result = pScriptingManager->execute("load('" ATHENA_SCRIPTING_UNITTESTS_SCRIPTS_PATH "simple.js" "');", context);

        CHECK(!result.IsEmpty());
        CHECK(!result->ToInt32().IsEmpty());
        CHECK_EQUAL(15, result->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}
}
