/** @file   Conversions.cpp
    @author Philip Abbet

    Implementation of the scripting-related conversion functions for the Athena-Core
    module
*/

#include <Athena-Scripting/Conversions.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Core/Utils/PropertiesList.h>
#include <Athena-Core/Utils/Describable.h>

using namespace Athena::Signals;
using namespace Athena::Scripting;
using namespace Athena::Utils;
using namespace v8;


Signal* Athena::Signals::fromJSSignal(Handle<Value> value)
{
    if (value->IsObject())
    {
        Signal* pSignal = 0;
        GetObjectPtr(value, &pSignal);
        return pSignal;
    }

    return 0;
}

//-----------------------------------------------------------------------

Handle<Object> Athena::Signals::createJSSignal()
{
    HandleScope handle_scope;

    Handle<FunctionTemplate> func = ScriptingManager::getSingletonPtr()->getClassTemplate(
                                                        "Athena.Signals.Signal");

    Handle<Object> jsSignal = func->GetFunction()->NewInstance();

    return handle_scope.Close(jsSignal);
}

//-----------------------------------------------------------------------

Handle<Value> Athena::Signals::toJavaScript(Signal* pSignal)
{
    // Assertions
    assert(pSignal);

    HandleScope handle_scope;

    Handle<FunctionTemplate> func = ScriptingManager::getSingletonPtr()->getClassTemplate(
                                                        "Athena.Signals.Signal");

    Handle<Value> argv[1];
    argv[0] = External::New(pSignal);

    Handle<Object> jsSignal = func->GetFunction()->NewInstance(1, argv);

    return handle_scope.Close(jsSignal);
}

//-----------------------------------------------------------------------

SignalsList* Athena::Signals::fromJSSignalsList(Handle<Value> value)
{
    if (value->IsObject())
    {
        SignalsList* pList = 0;
        GetObjectPtr(value, &pList);
        return pList;
    }

    return 0;
}

//-----------------------------------------------------------------------

Handle<Object> Athena::Signals::createJSSignalsList()
{
    HandleScope handle_scope;

    Handle<FunctionTemplate> func = ScriptingManager::getSingletonPtr()->getClassTemplate(
                                                        "Athena.Signals.SignalsList");

    Handle<Object> jsList = func->GetFunction()->NewInstance();

    return handle_scope.Close(jsList);
}

//-----------------------------------------------------------------------

Handle<Value> Athena::Signals::toJavaScript(SignalsList* pList)
{
    // Assertions
    assert(pList);

    HandleScope handle_scope;

    Handle<FunctionTemplate> func = ScriptingManager::getSingletonPtr()->getClassTemplate(
                                                        "Athena.Signals.SignalsList");

    Handle<Value> argv[1];
    argv[0] = External::New(pList);

    Handle<Object> jsList = func->GetFunction()->NewInstance(1, argv);

    return handle_scope.Close(jsList);
}

//-----------------------------------------------------------------------

Describable* Athena::Utils::fromJSDescribable(Handle<Value> value)
{
    if (value->IsObject())
    {
        Describable* pDescribable = 0;
        GetObjectPtr(value, &pDescribable);
        return pDescribable;
    }

    return 0;
}

//-----------------------------------------------------------------------

Handle<Object> Athena::Utils::createJSDescribable()
{
    HandleScope handle_scope;

    Handle<FunctionTemplate> func = ScriptingManager::getSingletonPtr()->getClassTemplate(
                                                        "Athena.Utils.Describable");

    Handle<Object> jsDescribable = func->GetFunction()->NewInstance();

    return handle_scope.Close(jsDescribable);
}

//-----------------------------------------------------------------------

Handle<Value> Athena::Utils::toJavaScript(Describable* pDescribable)
{
    // Assertions
    assert(pDescribable);

    HandleScope handle_scope;

    Handle<FunctionTemplate> func = ScriptingManager::getSingletonPtr()->getClassTemplate(
                                                        "Athena.Utils.Describable");

    Handle<Value> argv[1];
    argv[0] = External::New(pDescribable);

    Handle<Object> jsDescribable = func->GetFunction()->NewInstance(1, argv);

    return handle_scope.Close(jsDescribable);
}

//-----------------------------------------------------------------------

PropertiesList* Athena::Utils::fromJSPropertiesList(Handle<Value> value)
{
    if (value->IsObject())
    {
        PropertiesList* pList = 0;
        GetObjectPtr(value, &pList);
        return pList;
    }

    return 0;
}

//-----------------------------------------------------------------------

Handle<Object> Athena::Utils::createJSPropertiesList()
{
    HandleScope handle_scope;

    Handle<FunctionTemplate> func = ScriptingManager::getSingletonPtr()->getClassTemplate(
                                                        "Athena.Utils.PropertiesList");

    Handle<Object> jsList = func->GetFunction()->NewInstance();

    return handle_scope.Close(jsList);
}

//-----------------------------------------------------------------------

Handle<Value> Athena::Utils::toJavaScript(PropertiesList* pList)
{
    // Assertions
    assert(pList);

    HandleScope handle_scope;

    Handle<FunctionTemplate> func = ScriptingManager::getSingletonPtr()->getClassTemplate(
                                                        "Athena.Utils.PropertiesList");

    Handle<Value> argv[1];
    argv[0] = External::New(pList);

    Handle<Object> jsList = func->GetFunction()->NewInstance(1, argv);

    return handle_scope.Close(jsList);
}
