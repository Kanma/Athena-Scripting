/**	@file	ScriptingManager.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Scripting::ScriptingManager'
*/

#ifndef _ATHENA_SCRIPTING_SCRIPTINGMANAGER_H_
#define _ATHENA_SCRIPTING_SCRIPTINGMANAGER_H_

#include <Athena-Scripting/Prerequisites.h>
#include <v8.h>


namespace Athena {
namespace Scripting {


//----------------------------------------------------------------------------------------
/// @brief	Represents the Scripting Manager
///
/// This manager is the entry point for all the scripting-related features.
///
/// It maintains a 'main context', and allows the execution of scripts in their own
/// separate contexts.
/// 
/// @remark This class is a singleton
//----------------------------------------------------------------------------------------
class ATHENA_SYMBOL ScriptingManager: public Utils::Singleton<ScriptingManager>
{
	//_____ Construction / Destruction __________
public:
    //------------------------------------------------------------------------------------
    /// @brief	Constructor
    //------------------------------------------------------------------------------------
	ScriptingManager();

    //------------------------------------------------------------------------------------
    /// @brief	Destructor
    //------------------------------------------------------------------------------------
	~ScriptingManager();

    //------------------------------------------------------------------------------------
    /// @brief	Returns a reference to the instance of the Scripting Manager
    /// @return	A reference to the manager
    //------------------------------------------------------------------------------------
	static ScriptingManager& getSingleton();

    //------------------------------------------------------------------------------------
    /// @brief	Returns a pointer to the instance of the Scripting Manager
    /// @return	A pointer to the manager
    //------------------------------------------------------------------------------------
	static ScriptingManager* getSingletonPtr();


	//_____ Methods __________
public:
    //------------------------------------------------------------------------------------
    /// @brief	Execute the JavaScript code contained in a string
    ///
    /// @param	strScript	The script to execute
    /// @param	context	    Context in which to execute the script, empty to use the main
    ///                     one
    /// @return				'true' if successful
    //------------------------------------------------------------------------------------
	v8::Handle<v8::Value> execute(const std::string& strScript,
	                              v8::Persistent<v8::Context> context = v8::Persistent<v8::Context>());

    //------------------------------------------------------------------------------------
    /// @brief	Return the error message of the last error that occured
    //------------------------------------------------------------------------------------
    inline std::string getLastError() const
    {
        return m_strLastError;
    }
	

	//_____ Attributes __________
private:
    v8::Persistent<v8::Context> m_mainContext;
    std::string                 m_strLastError;
};

}
}

#endif
