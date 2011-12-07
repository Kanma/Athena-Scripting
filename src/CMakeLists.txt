# List the source files
set(SRCS ScriptingManager.cpp
)


# List the include paths
set(INCLUDE_PATHS "${ATHENA_SCRIPTING_SOURCE_DIR}/include")

include_directories(${INCLUDE_PATHS})

xmake_import_search_paths(ATHENA_CORE)
xmake_import_search_paths(V8)


# Declaration of the library
if (NOT ATHENA_SCRIPTING_STATIC)
    xmake_create_dynamic_library(ATHENA_SCRIPTING Athena-Scripting 1.0.0 1.0.0 ${SRCS})
else()
    xmake_create_static_library(ATHENA_SCRIPTING Athena-Scripting ${SRCS})
endif()

xmake_project_link(ATHENA_SCRIPTING ATHENA_CORE V8)

xmake_add_to_property(ATHENA_SCRIPTING COMPILE_DEFINITIONS "ATHENA_EXPORTS")


# Exportations
xmake_export_include_paths(ATHENA_SCRIPTING ${INCLUDE_PATHS})
