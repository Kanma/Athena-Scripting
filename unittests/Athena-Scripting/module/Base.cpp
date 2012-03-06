#include <v8.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <string>
#include "Classes.h"

using namespace v8;
using namespace Athena::Scripting;


/**************************************** MACROS ***************************************/

#undef GetObjectPtr
#define GetObjectPtr(HANDLE) GetObjectPtr<Base>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Construction callback
Handle<Value> Base_New(const Arguments& args)
{
    if ((args.Length() != 1) || !args[0]->IsInt32())
        return ThrowException(String::New("Invalid parameter, expected an integer"));

    return SetObjectPtr(args.This(), new Base(args[0]->Int32Value()));
}


/************************************** PROPERTIES *************************************/

Handle<Value> Base_GetA(Local<String> property, const AccessorInfo &info)
{
    Base* ptr = GetObjectPtr(info.This());
    assert(ptr);

    return Integer::New(ptr->a);
}

//-----------------------------------------------------------------------

void Base_SetA(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    Base* ptr = GetObjectPtr(info.This());
    assert(ptr);

    ptr->a = value->Int32Value();
}


/**************************************** METHODS ***************************************/

Handle<Value> Base_F(const Arguments& args)
{
    Base* ptr = GetObjectPtr(args.This());
    assert(ptr);

    ptr->f();

    return Handle<Value>();
}

//-----------------------------------------------------------------------

Handle<Value> Base_G(const Arguments& args)
{
    Base* ptr = GetObjectPtr(args.This());
    assert(ptr);

    ptr->g();

    return Handle<Value>();
}


/****************************** INITIALISATION OF THE MODULE ****************************/

bool bind_Base(Handle<Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    Handle<FunctionTemplate> base = pManager->getClassTemplate("Tests.Base");

    if (base.IsEmpty())
    {
        // Declaration of the class
        base = FunctionTemplate::New(Base_New);
        base->InstanceTemplate()->SetInternalFieldCount(1);

        // Attributes
        AddAttribute(base, "a", Base_GetA, Base_SetA);

        // Methods
        AddMethod(base, "f", Base_F);
        AddMethod(base, "g", Base_G);

        // Register the class with the Scripting Manager
        pManager->declareClassTemplate("Tests.Base", base);
    }

    // Add the class to the parent
    return parent->Set(String::New("Base"), base->GetFunction());
}
