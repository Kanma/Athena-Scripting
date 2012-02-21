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
    /// @brief	Retrieve the C++ object associated with a JavaScript one
    //------------------------------------------------------------------------------------
    template<typename T>
    T* GetObjectPtr(v8::Handle<v8::Value> const &h)
    {
        // Ensure that the handle is an object
        if (!h->IsObject())
            return 0;
        
        // Retrieve the object
        v8::Local<v8::Object> obj = h->ToObject();
        if (obj->InternalFieldCount() != 1)
            return 0;

        // Retrieve the C++ object
        return static_cast<T*>(obj->GetPointerFromInternalField(0));
    }


    //------------------------------------------------------------------------------------
    /// @brief	Retrieve the C++ object associated with a JavaScript one
    //------------------------------------------------------------------------------------
    template<typename T>
    void GetObjectPtr(v8::Handle<v8::Value> const &h, T** ptr)
    {
        // Ensure that the handle is an object
        if (!h->IsObject())
        {
            *ptr = 0;
            return;
        }
        
        // Retrieve the object
        v8::Local<v8::Object> obj = h->ToObject();
        if (obj->InternalFieldCount() != 1)
        {
            *ptr = 0;
            return;
        }

        // Retrieve the C++ object
        *ptr = static_cast<T*>(obj->GetPointerFromInternalField(0));
    }


    //------------------------------------------------------------------------------------
    /// @brief	Default 'WeakReferenceCallback', that delete the C++ object associated
    ///         with a JavaScript one when the GC kicks in
    //------------------------------------------------------------------------------------
    template<typename T>
    void DefaultWeakCallback(v8::Persistent<v8::Value> value, void* data)
    {
        if (value.IsNearDeath())
        {
            T* p = GetObjectPtr<T>(value);
            delete p;
        }
    }


    //------------------------------------------------------------------------------------
    /// @brief	Associate a C++ object to a JavaScript one
    //------------------------------------------------------------------------------------
    template<typename T>
    v8::Persistent<v8::Object> SetObjectPtr(v8::Handle<v8::Object> object, T* ptr)
    {
        v8::Persistent<v8::Object> self = v8::Persistent<v8::Object>::New(object);

        self->SetPointerInInternalField(0, ptr);
        self.MakeWeak(0, &DefaultWeakCallback<T>);

        v8::V8::AdjustAmountOfExternalAllocatedMemory(sizeof(T));

        return self;
    }


    //------------------------------------------------------------------------------------
    /// @brief	Associate a C++ object to a JavaScript one
    ///
    /// This function let you specify a custom 'WeakReferenceCallback' function, called to
    /// delete the C++ object associated with a JavaScript one when the GC kicks in
    //------------------------------------------------------------------------------------
    template<typename T>
    v8::Persistent<v8::Object> SetObjectPtr(v8::Handle<v8::Object> object, T* ptr,
                                            v8::WeakReferenceCallback weak_callback)
    {
        v8::Persistent<v8::Object> self = v8::Persistent<v8::Object>::New(object);

        self->SetPointerInInternalField(0, ptr);
        self.MakeWeak(0, weak_callback);

        v8::V8::AdjustAmountOfExternalAllocatedMemory(sizeof(T));

        return self;
    }


    //------------------------------------------------------------------------------------
    /// @brief	Associate a C++ object to a JavaScript one
    ///
    /// This function let you specify the size of the object in memory (use it when
    /// 'sizeof()' can't determine it)
    //------------------------------------------------------------------------------------
    template<typename T>
    v8::Persistent<v8::Object> SetObjectPtr(v8::Handle<v8::Object> object, T* ptr,
                                            size_t size)
    {
        v8::Persistent<v8::Object> self = v8::Persistent<v8::Object>::New(object);

        self->SetPointerInInternalField(0, ptr);
        self.MakeWeak(0, &DefaultWeakCallback<T>);

        v8::V8::AdjustAmountOfExternalAllocatedMemory(size);

        return self;
    }


    //------------------------------------------------------------------------------------
    /// @brief	Associate a C++ object to a JavaScript one
    ///
    /// This function let you specify a custom 'WeakReferenceCallback' function, called to
    /// delete the C++ object associated with a JavaScript one when the GC kicks in.
    ///
    /// It also let you specify the size of the object in memory (use it when 'sizeof()'
    /// can't determine it)
    //------------------------------------------------------------------------------------
    template<typename T>
    v8::Persistent<v8::Object> SetObjectPtr(v8::Handle<v8::Object> object, T* ptr,
                                            size_t size, v8::WeakReferenceCallback weak_callback)
    {
        v8::Persistent<v8::Object> self = v8::Persistent<v8::Object>::New(object);

        self->SetPointerInInternalField(0, ptr);
        self.MakeWeak(0, weak_callback);

        v8::V8::AdjustAmountOfExternalAllocatedMemory(size);

        return self;
    }


    //------------------------------------------------------------------------------------
    /// @brief	Add a method to the JavaScript template of a C++ class
    //------------------------------------------------------------------------------------
    inline void AddMethod(v8::Handle<v8::FunctionTemplate> function_template,
                          const std::string& name, v8::InvocationCallback callback)
    {
        function_template->PrototypeTemplate()->Set(
                                        v8::String::New(name.c_str()),
                                        v8::FunctionTemplate::New(callback)->GetFunction());
    }


    //------------------------------------------------------------------------------------
    /// @brief	Add an attribute to the JavaScript template of a C++ class
    //------------------------------------------------------------------------------------
    inline void AddAttribute(v8::Handle<v8::FunctionTemplate> function_template,
                             const std::string& name,
                             v8::AccessorGetter getter,
                             v8::AccessorSetter setter = 0)
    {
        function_template->PrototypeTemplate()->SetAccessor(
                                        v8::String::New(name.c_str()),
                                        getter, setter);
    }
}
}

#endif
