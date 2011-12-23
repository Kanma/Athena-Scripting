/**	@file	Utils.h
	@author	Philip Abbet

	Declaration of some utilities related to scripting
*/

#ifndef _ATHENA_SCRIPTING_UTILS_H_
#define _ATHENA_SCRIPTING_UTILS_H_

#include <Athena-Scripting/Prerequisites.h>
#include <v8.h>


namespace Athena {
namespace Scripting {

    //------------------------------------------------------------------------------------
    /// @brief	Create a JavaScript Object from a C++ one
    //------------------------------------------------------------------------------------
    template<typename T>
    v8::Persistent<v8::Object> createJSObject(const v8::Handle<v8::ObjectTemplate>& object_template,
                                              v8::WeakReferenceCallback weak_callback,
                                              T* p, size_t size, off_t class_id)
    {
        v8::Persistent<v8::Object> h = v8::Persistent<v8::Object>::New(object_template->NewInstance());
        h->SetInternalField(0, v8::External::New(p));
        h->SetInternalField(1, v8::External::New((void*) class_id));
        h.MakeWeak(0, weak_callback);

        v8::V8::AdjustAmountOfExternalAllocatedMemory(size + sizeof(off_t));

        return h;
    }


    //------------------------------------------------------------------------------------
    /// @brief	Convert an JavaScript Object to a C++ one
    //------------------------------------------------------------------------------------
    template<typename T>
    T* CastJSObject(v8::Handle<v8::Value> const &h, off_t class_id)
    {
        // Ensure that the handle is an object
        if (!h->IsObject())
            return 0;
        
        // Retrieve the object
        v8::Local<v8::Object> obj = h->ToObject();
        if (obj->InternalFieldCount() != 2)
            return 0;

        // Ensure that the class ID match
        v8::Local<v8::External> external = v8::Local<v8::External>::Cast(obj->GetInternalField(1));
        if ((off_t) external->Value() != class_id)
            return 0;
        
        // Retrieve the C++ obect
        external = v8::Local<v8::External>::Cast(obj->GetInternalField(0));
        return static_cast<T*>(external->Value());
    }
}
}

#endif
