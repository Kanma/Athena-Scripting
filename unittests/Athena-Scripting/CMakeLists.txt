# Setup the search paths
xmake_import_search_paths(ATHENA_SCRIPTING)
xmake_import_search_paths(UNITTEST_CPP)


# List the source files
set(SRCS main.cpp
         tests/ScriptingManager.cpp
         tests/JSFunctions.cpp
)


# Declaration of the executable
xmake_create_executable(UNITTESTS_ATHENA_SCRIPTING UnitTests-Athena-Scripting ${SRCS})

xmake_project_link(UNITTESTS_ATHENA_SCRIPTING UNITTEST_CPP)
xmake_project_link(UNITTESTS_ATHENA_SCRIPTING ATHENA_SCRIPTING)

xmake_add_to_list_property(UNITTESTS_ATHENA_SCRIPTING COMPILE_DEFINITIONS "ATHENA_SCRIPTING_UNITTESTS_SCRIPTS_PATH=\"${ATHENA_SCRIPTING_SOURCE_DIR}/unittests/scripts/\"")


# Process subdirectories
add_subdirectory(module)


# Run the unit tests
set(WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
if (WIN32)
    set(WORKING_DIRECTORY "${WORKING_DIRECTORY}/$(OutDir)")
endif()

add_custom_target(Run-UnitTests-Athena-Scripting ALL UnitTests-Athena-Scripting
                  DEPENDS UnitTests-Athena-Scripting Athena-Scripting-test-module1 Athena-Scripting-test-module2 Athena-Scripting-test-module3
                  WORKING_DIRECTORY ${WORKING_DIRECTORY}
                  COMMENT "Unit testing: Athena-Scripting..." VERBATIM)
