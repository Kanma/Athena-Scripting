/** @file   Conversions.h
    @author Philip Abbet

    Scripting-related conversion functions for the Athena-Core module. They can't be part
    of the Athena-Core module due to circular dependencies between it and Athena-Scripting.
*/

#ifndef _ATHENA_SCRIPTING_CONVERSIONS_H_
#define _ATHENA_SCRIPTING_CONVERSIONS_H_

#include <Athena-Scripting/Prerequisites.h>
#include <Athena-Core/Prerequisites.h>
#include <v8.h>


namespace Athena {

    namespace Signals {

        //--------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ Signal wrapped by a JavaScript one
        //--------------------------------------------------------------------------------
        Signal* ATHENA_SCRIPTING_SYMBOL fromJSSignal(v8::Handle<v8::Value> value);

        //--------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript Signal (wrapping a new C++ one)
        //--------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_SCRIPTING_SYMBOL createJSSignal();

        //--------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript Signal around a C++ one
        //--------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_SCRIPTING_SYMBOL toJavaScript(Signal* pSignal);


        //--------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ SignalsList wrapped by a JavaScript one
        //--------------------------------------------------------------------------------
        SignalsList* ATHENA_SCRIPTING_SYMBOL fromJSSignalsList(v8::Handle<v8::Value> value);

        //--------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript SignalsList (wrapping a new C++ one)
        //--------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_SCRIPTING_SYMBOL createJSSignalsList();

        //--------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript SignalsList around a C++ one
        //--------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_SCRIPTING_SYMBOL toJavaScript(SignalsList* pList);
    }


    namespace Utils {

        //--------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ Describable wrapped by a JavaScript one
        //--------------------------------------------------------------------------------
        Describable* ATHENA_SCRIPTING_SYMBOL fromJSDescribable(v8::Handle<v8::Value> value);

        //--------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript Describable (wrapping a new C++ one)
        //--------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_SCRIPTING_SYMBOL createJSDescribable();

        //--------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript Describable around a C++ one
        //--------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_SCRIPTING_SYMBOL toJavaScript(Describable* pDescribable);


        //--------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ PropertiesList wrapped by a JavaScript one
        //--------------------------------------------------------------------------------
        PropertiesList* ATHENA_SCRIPTING_SYMBOL fromJSPropertiesList(v8::Handle<v8::Value> value);

        //--------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript PropertiesList (wrapping a new C++ one)
        //--------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_SCRIPTING_SYMBOL createJSPropertiesList();

        //--------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript PropertiesList around a C++ one
        //--------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_SCRIPTING_SYMBOL toJavaScript(PropertiesList* pList);
    }
}

#endif
