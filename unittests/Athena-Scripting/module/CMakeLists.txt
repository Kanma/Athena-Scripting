set(HEADERS Classes.h
)


set(SRCS module.cpp
         Base.cpp
         Derived.cpp
)

# Declaration of the test module 1
xmake_create_dynamic_library(ATHENA_SCRIPTING_TEST_MODULE_1 Athena-Scripting-test-module1 1.0.0 1.0.0 ${HEADERS} ${SRCS})
xmake_project_link(ATHENA_SCRIPTING_TEST_MODULE_1 ATHENA_SCRIPTING V8)

create_scripting_module(ATHENA_SCRIPTING_TEST_MODULE_1 "module1" "Point3D.js")


# Declaration of the test module 2
xmake_create_dynamic_library(ATHENA_SCRIPTING_TEST_MODULE_2 Athena-Scripting-test-module2 1.0.0 1.0.0 ${HEADERS} ${SRCS})
xmake_project_link(ATHENA_SCRIPTING_TEST_MODULE_2 ATHENA_SCRIPTING V8)

create_scripting_module(ATHENA_SCRIPTING_TEST_MODULE_2 "test.module2" "Point3D.js")


# Declaration of the test module 3
xmake_create_dynamic_library(ATHENA_SCRIPTING_TEST_MODULE_3 Athena-Scripting-test-module3 1.0.0 1.0.0 ${HEADERS} ${SRCS})
xmake_project_link(ATHENA_SCRIPTING_TEST_MODULE_3 ATHENA_SCRIPTING V8)

create_scripting_module(ATHENA_SCRIPTING_TEST_MODULE_3 "test.module3" "")
