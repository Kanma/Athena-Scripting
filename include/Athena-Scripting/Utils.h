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
    /// @brief	Convert an JavaScript Object to a C++ one
    //------------------------------------------------------------------------------------
    template<typename T>
    T* CastJSObject(v8::Handle<v8::Value> const &h)
    {
        if (!h->IsObject())
            return 0;
        
        v8::Local<v8::Object> obj = h->ToObject();
        if (obj->InternalFieldCount() != 1)
            return 0;
        
        v8::Local<v8::External> external = v8::Local<v8::External>::Cast(obj->GetInternalField(0));

        return static_cast<T*>(external->Value());
    }
}
}

#endif
