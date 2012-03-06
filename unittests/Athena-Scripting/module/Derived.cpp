#include <v8.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <string>
#include "Classes.h"

using namespace v8;
using namespace Athena::Scripting;


/**************************************** MACROS ***************************************/

#undef GetObjectPtr
#define GetObjectPtr(HANDLE) GetObjectPtr<Derived>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Construction callback
Handle<Value> Derived_New(const Arguments& args)
{
    if ((args.Length() != 2) || !args[0]->IsInt32() || !args[1]->IsInt32())
        return ThrowException(String::New("Invalid parameters, expected two integers"));

    return SetObjectPtr(args.This(), new Derived(args[0]->Int32Value(), args[1]->Int32Value()));
}


/************************************** PROPERTIES *************************************/

Handle<Value> Derived_GetB(Local<String> property, const AccessorInfo &info)
{
    Derived* ptr = GetObjectPtr(info.This());
    assert(ptr);

    return Integer::New(ptr->b);
}

//-----------------------------------------------------------------------

void Derived_SetB(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    Derived* ptr = GetObjectPtr(info.This());
    assert(ptr);

    ptr->b = value->Int32Value();
}


/**************************************** METHODS ***************************************/

Handle<Value> Derived_H(const Arguments& args)
{
    Derived* ptr = GetObjectPtr(args.This());
    assert(ptr);

    ptr->h();

    return Handle<Value>();
}


/****************************** INITIALISATION OF THE MODULE ****************************/

bool bind_Derived(Handle<Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    Handle<FunctionTemplate> derived = pManager->getClassTemplate("Tests.Derived");

    if (derived.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Tests.Base").IsEmpty());

        // Declaration of the class
        derived = FunctionTemplate::New(Derived_New);
        derived->InstanceTemplate()->SetInternalFieldCount(1);
        derived->Inherit(pManager->getClassTemplate("Tests.Base"));

        // Attributes
        AddAttribute(derived, "b", Derived_GetB, Derived_SetB);

        // Methods
        AddMethod(derived, "h", Derived_H);

        // Register the class with the Scripting Manager
        pManager->declareClassTemplate("Tests.Derived", derived);
    }

    // Add the class to the parent
    return parent->Set(String::New("Derived"), derived->GetFunction());
}
