# Setup the search paths
xmake_import_search_paths(ATHENA_SCRIPTING)
xmake_import_search_paths(UNITTEST_CPP)


# List the source files
set(SRCS main.cpp
         test_ScriptingManager.cpp
)


# Declaration of the executable
xmake_create_executable(UNITTESTS_ATHENA_SCRIPTING UnitTests-Athena-Scripting ${SRCS})

xmake_project_link(UNITTESTS_ATHENA_SCRIPTING UNITTEST_CPP)
xmake_project_link(UNITTESTS_ATHENA_SCRIPTING ATHENA_SCRIPTING)

xmake_add_to_property(UNITTESTS_ATHENA_SCRIPTING COMPILE_DEFINITIONS "ATHENA_SCRIPTING_UNITTESTS_SCRIPTS_PATH=\"${ATHENA_SCRIPTING_SOURCE_DIR}/unittests/scripts/\"")

# Run the unit tests
get_property(PATH TARGET UnitTests-Athena-Scripting PROPERTY RUNTIME_OUTPUT_DIRECTORY)
add_custom_target(Run-UnitTests-Athena-Scripting ALL UnitTests-Athena-Scripting
                  DEPENDS UnitTests-Athena-Scripting
                  WORKING_DIRECTORY ${PATH}
                  COMMENT "Unit testing: Athena-Scripting..." VERBATIM)
