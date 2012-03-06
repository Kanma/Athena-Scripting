/** @file   Prerequisites.h
    @author Philip Abbet

    Declaration of the types of the Athena-Scripting module
*/

#ifndef _ATHENA_SCRIPTING_PREREQUISITES_H_
#define _ATHENA_SCRIPTING_PREREQUISITES_H_

#include <Athena-Core/Prerequisites.h>

/// Used to export symbols from the library
#if (ATHENA_PLATFORM == ATHENA_PLATFORM_WIN32) && !ATHENA_SCRIPTING_STATIC
#    ifdef ATHENA_SCRIPTING_EXPORTS
#        define ATHENA_SCRIPTING_SYMBOL  __declspec(dllexport)
#    else
#        define ATHENA_SCRIPTING_SYMBOL  __declspec(dllimport)
#    endif
#else
#    define ATHENA_SCRIPTING_SYMBOL
#endif


/// To be used by the modules to export their init function
#if ATHENA_PLATFORM == ATHENA_PLATFORM_WIN32
#   define MODULE_INITIALISATION_FUNCTION __declspec(dllexport)
#else
#   define MODULE_INITIALISATION_FUNCTION
#endif


//----------------------------------------------------------------------------------------
/// @brief  Main namespace. All the components of the Athena engine belongs to this
///         namespace
//----------------------------------------------------------------------------------------
namespace Athena
{
    //------------------------------------------------------------------------------------
    /// @brief  Contains all the scripting-related classes
    //------------------------------------------------------------------------------------
    namespace Scripting
    {
        class ScriptingManager;

        extern const char* VERSION;
    }
}

#endif
