# File generation
configure_file(${ATHENA_SCRIPTING_SOURCE_DIR}/src/module.cpp.in
               ${XMAKE_BINARY_DIR}/generated/Athena-Scripting/module.cpp)

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
if (NOT ATHENA_SCRIPTING_STATIC)
    xmake_create_dynamic_library(ATHENA_SCRIPTING Athena-Scripting
                                 "${ATHENA_SCRIPTING_VERSION_MAJOR}.${ATHENA_SCRIPTING_VERSION_MINOR}.${ATHENA_SCRIPTING_VERSION_PATCH}"
                                 "${ATHENA_SCRIPTING_VERSION_MAJOR}.${ATHENA_SCRIPTING_VERSION_MINOR}.${ATHENA_SCRIPTING_VERSION_PATCH}"
                                 ${SRCS})

    xmake_add_to_list_property(ATHENA_SCRIPTING COMPILE_DEFINITIONS "ATHENA_SCRIPTING_EXPORTS")
else()
    xmake_create_static_library(ATHENA_SCRIPTING Athena-Scripting ${SRCS})
endif()

xmake_project_link(ATHENA_SCRIPTING ATHENA_CORE V8)

if (UNIX AND NOT ATHENA_SCRIPTING_STATIC)
    xmake_add_to_property(ATHENA_SCRIPTING LINK_FLAGS "-ldl")
endif()


# Exportations
xmake_export_include_paths(ATHENA_SCRIPTING ${INCLUDE_PATHS})

if (UNIX)
    xmake_export_link_flags(ATHENA_SCRIPTING "-ldl")
endif()
