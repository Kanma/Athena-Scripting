set(SRCS module.cpp
         Base.cpp
         Derived.cpp
)

# Declaration of the test module 1
xmake_create_dynamic_library(ATHENA_SCRIPTING_TEST_MODULE_1 Athena-Scripting-test-module1 1.0.0 1.0.0 "${SRCS}")
xmake_project_link(ATHENA_SCRIPTING_TEST_MODULE_1 ATHENA_SCRIPTING V8)
set_target_properties(Athena-Scripting-test-module1 PROPERTIES OUTPUT_NAME "module1"
                                                               LIBRARY_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/bin/modules")
configure_file(Point3D.js "${XMAKE_BINARY_DIR}/bin/modules/js/Point3D.js" COPYONLY)

# Declaration of the test module 2
xmake_create_dynamic_library(ATHENA_SCRIPTING_TEST_MODULE_2 Athena-Scripting-test-module2 1.0.0 1.0.0 "${SRCS}")
xmake_project_link(ATHENA_SCRIPTING_TEST_MODULE_2 ATHENA_SCRIPTING V8)
set_target_properties(Athena-Scripting-test-module2 PROPERTIES OUTPUT_NAME "module2"
                                                               LIBRARY_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/bin/modules/test")
configure_file(Point3D.js "${XMAKE_BINARY_DIR}/bin/modules/test/js/Point3D.js" COPYONLY)

# Declaration of the test module 3
xmake_create_dynamic_library(ATHENA_SCRIPTING_TEST_MODULE_3 Athena-Scripting-test-module3 1.0.0 1.0.0 "${SRCS}")
xmake_project_link(ATHENA_SCRIPTING_TEST_MODULE_3 ATHENA_SCRIPTING V8)
set_target_properties(Athena-Scripting-test-module3 PROPERTIES OUTPUT_NAME "module3"
                                                               LIBRARY_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/bin/modules/test")
