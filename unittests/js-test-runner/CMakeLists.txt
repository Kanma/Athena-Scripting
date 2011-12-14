# Setup the search paths
xmake_import_search_paths(ATHENA_SCRIPTING)


# Declaration of the executable
xmake_create_executable(JS_TEST_RUNNER js_test_runner main.cpp)

xmake_project_link(JS_TEST_RUNNER ATHENA_SCRIPTING)

xmake_add_to_list_property(JS_TEST_RUNNER COMPILE_DEFINITIONS "ATHENA_SCRIPTING_JS_TEST_RUNNER_PATH=\"${ATHENA_SCRIPTING_SOURCE_DIR}/unittests/js-test-runner/\"")
