/**	@file	Functions.h
	@author	Philip Abbet

	Declaration of the custom global functions
*/

#ifndef _ATHENA_SCRIPTING_FUNCTIONS_H_
#define _ATHENA_SCRIPTING_FUNCTIONS_H_

#include <Athena-Scripting/Prerequisites.h>
#include <v8.h>


namespace Athena {
namespace Scripting {

    //------------------------------------------------------------------------------------
    /// @brief	The callback that is invoked by v8 whenever the JavaScript 'print()'
    //          function is called. Prints its arguments on stdout separated by spaces.
    //------------------------------------------------------------------------------------
    extern v8::Handle<v8::Value> Print(const v8::Arguments& args);

    //------------------------------------------------------------------------------------
    /// @brief	The callback that is invoked by v8 whenever the JavaScript 'import_module()'
    //          function is called. Import an external module.
    ///
    /// @param	strModuleName   Name of the module
    /// @return				    'true' if successful
    //------------------------------------------------------------------------------------
    extern v8::Handle<v8::Value> Import(const v8::Arguments& args);

    //------------------------------------------------------------------------------------
    /// @brief	The callback that is invoked by v8 whenever the JavaScript 'load()'
    //          function is called. Load and execute an JavaScript file.
    ///
    /// @param	strFileName	Path of the script to execute
    /// @return				The return value of the script
    //------------------------------------------------------------------------------------
    extern v8::Handle<v8::Value> Load(const v8::Arguments& args);
}
}

#endif
