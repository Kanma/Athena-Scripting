#include <UnitTest++.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <Athena-Core/Log/LogManager.h>
#include <Athena-Core/Log/XMLLogListener.h>
#include "../environments/ScriptingTestEnvironment.h"
#include <iostream>


using namespace Athena::Scripting;
using namespace Athena::Log;
using namespace v8;


#define USE_MAIN_CONTEXT
#include "JSFunctions_impl.cpp"

#undef USE_MAIN_CONTEXT
#include "JSFunctions_impl.cpp"
