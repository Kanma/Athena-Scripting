# File generation
configure_file(${ATHENA_SCRIPTING_SOURCE_DIR}/src/module.cpp.in
               ${XMAKE_BINARY_DIR}/generated/Athena-Scripting/module.cpp)


# List the header files
set(HEADERS ../include/Athena-Scripting/ScriptingManager.h
            ../include/Athena-Scripting/Functions.h
            ../include/Athena-Scripting/Conversions.h
            ../include/Athena-Scripting/Prerequisites.h
            ../include/Athena-Scripting/Utils.h
)


# List the source files
set(SRCS ${XMAKE_BINARY_DIR}/generated/Athena-Scripting/module.cpp
         ScriptingManager.cpp
         Functions.cpp
         Conversions.cpp
)


# List the include paths
set(INCLUDE_PATHS "${ATHENA_SCRIPTING_SOURCE_DIR}/include")

include_directories(${INCLUDE_PATHS})

xmake_import_search_paths(ATHENA_CORE)
xmake_import_search_paths(V8)


# Declaration of the library
xmake_create_dynamic_library(ATHENA_SCRIPTING Athena-Scripting
                             "${ATHENA_SCRIPTING_VERSION_MAJOR}.${ATHENA_SCRIPTING_VERSION_MINOR}.${ATHENA_SCRIPTING_VERSION_PATCH}"
                             "${ATHENA_SCRIPTING_VERSION_MAJOR}.${ATHENA_SCRIPTING_VERSION_MINOR}.${ATHENA_SCRIPTING_VERSION_PATCH}"
                             ${HEADERS} ${SRCS})

xmake_add_to_list_property(ATHENA_SCRIPTING COMPILE_DEFINITIONS "ATHENA_SCRIPTING_EXPORTS")

xmake_project_link(ATHENA_SCRIPTING ATHENA_CORE V8)

if (UNIX)
    xmake_link_libraries(ATHENA_SCRIPTING dl)
endif()


# Exportations
xmake_export_include_paths(ATHENA_SCRIPTING ${INCLUDE_PATHS})
