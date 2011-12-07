/** @file   Prerequisites.h
    @author Philip Abbet
    
    Declaration of the types of the Athena-Scripting module
*/

#ifndef _ATHENA_SCRIPTING_PREREQUISITES_H_
#define _ATHENA_SCRIPTING_PREREQUISITES_H_

#include <Athena-Core/Prerequisites.h>


//----------------------------------------------------------------------------------------
/// @brief	Main namespace. All the components of the Athena engine belongs to this
///			namespace
//----------------------------------------------------------------------------------------
namespace Athena
{
	//------------------------------------------------------------------------------------
	/// @brief	Contains all the scripting-related classes
	//------------------------------------------------------------------------------------
    namespace Scripting
    {
        class ScriptingManager;
    }
}

#endif
