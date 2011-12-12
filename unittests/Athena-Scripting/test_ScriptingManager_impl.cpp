#ifdef USE_MAIN_CONTEXT
SUITE(ScriptingManagerTests_UsingMainContext)
#else
SUITE(ScriptingManagerTests_UsingOwnContext)
#endif
{
	TEST_FIXTURE(ScriptingTestEnvironment, TestFixture)
	{
		CHECK(pScriptingManager);

        HandleScope handle_scope;

        #ifdef USE_MAIN_CONTEXT
            context = ScriptingManager::createContext();
        #endif
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ExecuteSimpleOperation)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result = pScriptingManager->execute("10 * 5", context);

        CHECK(!result.IsEmpty());
        CHECK(!result->ToInt32().IsEmpty());
        CHECK_EQUAL(50, result->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ExecuteInvalidOperation)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result = pScriptingManager->execute("unknown_variable", context);

        CHECK(result.IsEmpty());
        CHECK(!pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ContextsSeparation)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result1 = pScriptingManager->execute("var a = 5;", context);
        CHECK(!result1.IsEmpty());
        CHECK(pScriptingManager->getLastError().empty());

        Persistent<Context> myContext = ScriptingManager::createContext();

		Handle<Value> result2 = pScriptingManager->execute("a", myContext);
        CHECK(result2.IsEmpty());
        CHECK(!pScriptingManager->getLastError().empty());

        myContext.Dispose();
	}


	TEST_FIXTURE(ScriptingTestEnvironment, GlobalVariablesAreAccessibleAcrossCalls)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result1 = pScriptingManager->execute("var a = 5;", context);
        CHECK(!result1.IsEmpty());
        CHECK(pScriptingManager->getLastError().empty());

		Handle<Value> result2 = pScriptingManager->execute("a", context);
        CHECK(!result2.IsEmpty());
        CHECK(!result2->ToInt32().IsEmpty());
        CHECK_EQUAL(5, result2->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, FunctionsAreAccessibleAcrossCalls)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result1 = pScriptingManager->execute("function f(a, b) { return a + b; } f(10, 5);", context);
        CHECK(!result1.IsEmpty());
        CHECK(!result1->ToInt32().IsEmpty());
        CHECK_EQUAL(15, result1->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());

		Handle<Value> result2 = pScriptingManager->execute("f(100, 200);", context);
        CHECK(!result2.IsEmpty());
        CHECK(!result2->ToInt32().IsEmpty());
        CHECK_EQUAL(300, result2->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ExecuteUnknownFile)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result = pScriptingManager->executeFile("unknown.js", context);

        CHECK(result.IsEmpty());
        CHECK(!pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ExecuteFile)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result = pScriptingManager->executeFile(ATHENA_SCRIPTING_UNITTESTS_SCRIPTS_PATH "simple.js", context);

        CHECK(!result.IsEmpty());
        CHECK(!result->ToInt32().IsEmpty());
        CHECK_EQUAL(15, result->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ImportUnknownModule)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		CHECK(!pScriptingManager->import("unknown", context));
        CHECK(!pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ImportModuleFromRootFolder)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		CHECK(pScriptingManager->import("module1", context));
        CHECK(pScriptingManager->getLastError().empty());

		Handle<Value> result = pScriptingManager->execute("module1.sum(10, 5);", context);

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

		CHECK(pScriptingManager->import("test.module2", context));
        CHECK(pScriptingManager->getLastError().empty());

		Handle<Value> result = pScriptingManager->execute("test.module2.sum(10, 5);", context);

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

		CHECK(pScriptingManager->import("test.module2", context));
        CHECK(pScriptingManager->getLastError().empty());

		CHECK(pScriptingManager->import("test.module3", context));
        CHECK(pScriptingManager->getLastError().empty());

		Handle<Value> result = pScriptingManager->execute("test.module2.sum(10, test.module3.sum(20, 30));", context);

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

		CHECK(pScriptingManager->import("module1", context));
        CHECK(pScriptingManager->getLastError().empty());

		CHECK(pScriptingManager->import("module1", context));
        CHECK(pScriptingManager->getLastError().empty());

		Handle<Value> result = pScriptingManager->execute("module1.sum(10, 5);", context);

        CHECK(!result.IsEmpty());
        CHECK(!result->ToInt32().IsEmpty());
        CHECK_EQUAL(15, result->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ClassBinding)
	{
        HandleScope handle_scope;

#ifdef USE_MAIN_CONTEXT
        context = ScriptingManager::createContext();
#endif

		Handle<Value> result = pScriptingManager->executeFile(ATHENA_SCRIPTING_UNITTESTS_SCRIPTS_PATH "points.js", context);

        CHECK(!result.IsEmpty());
        CHECK(!result->ToInt32().IsEmpty());
        CHECK_EQUAL(20, result->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}
}
