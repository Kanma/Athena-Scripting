#include <UnitTest++.h>
#include <Athena-Scripting/ScriptingManager.h>
#include "environments/ScriptingTestEnvironment.h"
#include <iostream>


using namespace Athena::Scripting;
using namespace v8;


#define USE_MAIN_CONTEXT
#include "test_JSFunctions_impl.cpp"

#undef USE_MAIN_CONTEXT
#include "test_JSFunctions_impl.cpp"
