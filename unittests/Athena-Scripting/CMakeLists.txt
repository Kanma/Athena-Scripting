# Setup the search paths
xmake_import_search_paths(ATHENA_SCRIPTING)
xmake_import_search_paths(UNITTEST_CPP)


# List the source files
set(SRCS main.cpp
         test_ScriptingManager.cpp
         test_JSFunctions.cpp
)


# Declaration of the executable
xmake_create_executable(UNITTESTS_ATHENA_SCRIPTING UnitTests-Athena-Scripting ${SRCS})

xmake_project_link(UNITTESTS_ATHENA_SCRIPTING UNITTEST_CPP)
xmake_project_link(UNITTESTS_ATHENA_SCRIPTING ATHENA_SCRIPTING)

xmake_add_to_list_property(UNITTESTS_ATHENA_SCRIPTING COMPILE_DEFINITIONS "ATHENA_SCRIPTING_UNITTESTS_SCRIPTS_PATH=\"${ATHENA_SCRIPTING_SOURCE_DIR}/unittests/scripts/\"")


# Declaration of the test module 1
xmake_create_dynamic_library(ATHENA_SCRIPTING_TEST_MODULE_1 Athena-Scripting-test-module1 1.0.0 1.0.0 "module.cpp")
xmake_project_link(ATHENA_SCRIPTING_TEST_MODULE_1 ATHENA_SCRIPTING V8)
set_target_properties(Athena-Scripting-test-module1 PROPERTIES OUTPUT_NAME "module1"
                                                               LIBRARY_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/bin/modules")
configure_file(Point3D.js "${XMAKE_BINARY_DIR}/bin/modules/js/Point3D.js" COPYONLY)

# Declaration of the test module 2
xmake_create_dynamic_library(ATHENA_SCRIPTING_TEST_MODULE_2 Athena-Scripting-test-module2 1.0.0 1.0.0 "module.cpp")
xmake_project_link(ATHENA_SCRIPTING_TEST_MODULE_2 ATHENA_SCRIPTING V8)
set_target_properties(Athena-Scripting-test-module2 PROPERTIES OUTPUT_NAME "module2"
                                                               LIBRARY_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/bin/modules/test")
configure_file(Point3D.js "${XMAKE_BINARY_DIR}/bin/modules/test/js/Point3D.js" COPYONLY)

# Declaration of the test module 3
xmake_create_dynamic_library(ATHENA_SCRIPTING_TEST_MODULE_3 Athena-Scripting-test-module3 1.0.0 1.0.0 "module.cpp")
xmake_project_link(ATHENA_SCRIPTING_TEST_MODULE_3 ATHENA_SCRIPTING V8)
set_target_properties(Athena-Scripting-test-module3 PROPERTIES OUTPUT_NAME "module3"
                                                               LIBRARY_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/bin/modules/test")


# Run the unit tests
get_property(PATH TARGET UnitTests-Athena-Scripting PROPERTY RUNTIME_OUTPUT_DIRECTORY)
add_custom_target(Run-UnitTests-Athena-Scripting ALL UnitTests-Athena-Scripting
                  DEPENDS UnitTests-Athena-Scripting Athena-Scripting-test-module1 Athena-Scripting-test-module2 Athena-Scripting-test-module3
                  WORKING_DIRECTORY ${PATH}
                  COMMENT "Unit testing: Athena-Scripting..." VERBATIM)
