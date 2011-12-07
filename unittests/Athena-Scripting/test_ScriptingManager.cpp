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


SUITE(ScriptingManagerTests)
{
	TEST_FIXTURE(ScriptingTestEnvironment, TestFixture)
	{
		CHECK(pScriptingManager);
	}
 
	TEST_FIXTURE(ScriptingTestEnvironment, ExecuteSimpleOperation)
	{
        HandleScope handle_scope;

		Handle<Value> result = pScriptingManager->execute("10 * 5");

        CHECK(!result.IsEmpty());
        CHECK(!result->ToInt32().IsEmpty());
        CHECK_EQUAL(50, result->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ExecuteInvalidOperation)
	{
        HandleScope handle_scope;

		Handle<Value> result = pScriptingManager->execute("unknown_variable");

        CHECK(result.IsEmpty());
        CHECK(!pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, ContextsSeparation)
	{
        HandleScope handle_scope;

		Handle<Value> result1 = pScriptingManager->execute("var a = 5;");
        CHECK(!result1.IsEmpty());
        CHECK(pScriptingManager->getLastError().empty());

        Persistent<Context> myContext = Context::New();

		Handle<Value> result2 = pScriptingManager->execute("a", myContext);
        CHECK(result2.IsEmpty());
        CHECK(!pScriptingManager->getLastError().empty());
        
        myContext.Dispose();
	}


	TEST_FIXTURE(ScriptingTestEnvironment, GlobalVariablesAreAccessibleAcrossCalls)
	{
        HandleScope handle_scope;

		Handle<Value> result1 = pScriptingManager->execute("var a = 5;");
        CHECK(!result1.IsEmpty());
        CHECK(pScriptingManager->getLastError().empty());

		Handle<Value> result2 = pScriptingManager->execute("a");
        CHECK(!result2.IsEmpty());
        CHECK(!result2->ToInt32().IsEmpty());
        CHECK_EQUAL(5, result2->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, GlobalVariablesAreAccessibleAcrossCallsUsingOwnContext)
	{
        HandleScope handle_scope;

        Persistent<Context> myContext = Context::New();

		Handle<Value> result1 = pScriptingManager->execute("var a = 5;", myContext);
        CHECK(!result1.IsEmpty());
        CHECK(pScriptingManager->getLastError().empty());

		Handle<Value> result2 = pScriptingManager->execute("a", myContext);
        CHECK(!result2.IsEmpty());
        CHECK(!result2->ToInt32().IsEmpty());
        CHECK_EQUAL(5, result2->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
        
        myContext.Dispose();
	}


	TEST_FIXTURE(ScriptingTestEnvironment, FunctionsAreAccessibleAcrossCalls)
	{
        HandleScope handle_scope;

		Handle<Value> result1 = pScriptingManager->execute("function f(a, b) { return a + b; } f(10, 5);");
        CHECK(!result1.IsEmpty());
        CHECK(!result1->ToInt32().IsEmpty());
        CHECK_EQUAL(15, result1->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());

		Handle<Value> result2 = pScriptingManager->execute("f(100, 200);");
        CHECK(!result2.IsEmpty());
        CHECK(!result2->ToInt32().IsEmpty());
        CHECK_EQUAL(300, result2->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
	}


	TEST_FIXTURE(ScriptingTestEnvironment, FunctionsAreAccessibleAcrossCallsUsingOwnContext)
	{
        HandleScope handle_scope;

        Persistent<Context> myContext = Context::New();

		Handle<Value> result1 = pScriptingManager->execute("function f(a, b) { return a + b; } f(10, 5);", myContext);
        CHECK(!result1.IsEmpty());
        CHECK(!result1->ToInt32().IsEmpty());
        CHECK_EQUAL(15, result1->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());

		Handle<Value> result2 = pScriptingManager->execute("f(100, 200);", myContext);
        CHECK(!result2.IsEmpty());
        CHECK(!result2->ToInt32().IsEmpty());
        CHECK_EQUAL(300, result2->ToInt32()->Value());
        CHECK(pScriptingManager->getLastError().empty());
        
        myContext.Dispose();
	}
}
