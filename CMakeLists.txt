cmake_minimum_required(VERSION 2.6)
project(ATHENA_SCRIPTING)

##########################################################################################
# Settings

set(ATHENA_SCRIPTING_ENABLED ON CACHE BOOL "Compile the scripting module of Athena")

if (NOT DEFINED ATHENA_SCRIPTING_STATIC)
    set(ATHENA_SCRIPTING_STATIC OFF CACHE BOOL "Build Athena-Scripting as a static library")
endif()


##########################################################################################
# Setup the dependencies

set(COMPILE_AS_STATIC ON)
if (WIN32)
    set(COMPILE_AS_STATIC OFF)
endif()

if (NOT DEFINED ATHENA_MATH_STATIC)
    set(ATHENA_MATH_STATIC ${COMPILE_AS_STATIC})
endif()

if (NOT DEFINED ATHENA_CORE_STATIC)
    set(ATHENA_CORE_STATIC ${COMPILE_AS_STATIC})
endif()


##########################################################################################
# Library version

set(ATHENA_SCRIPTING_VERSION_MAJOR 1)
set(ATHENA_SCRIPTING_VERSION_MINOR 0)
set(ATHENA_SCRIPTING_VERSION_PATCH 0)
set(ATHENA_SCRIPTING_VERSION_SUFFIX " (Dev)")


##########################################################################################
# XMake-related settings

# Set the output paths
if (NOT DEFINED XMAKE_BINARY_DIR)
    set(XMAKE_BINARY_DIR "${ATHENA_SCRIPTING_BINARY_DIR}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/bin")
endif()

# Set the dependencies path
if (NOT DEFINED XMAKE_DEPENDENCIES_DIR)
    set(XMAKE_DEPENDENCIES_DIR "${ATHENA_SCRIPTING_SOURCE_DIR}/dependencies")
endif()


##########################################################################################
# XMake importation

if (NOT EXISTS "${XMAKE_DEPENDENCIES_DIR}/XMake/XMake.cmake")
    message(FATAL_ERROR
"Missing dependency: XMake
Athena-Scripting requires the following dependencies:
   - XMake
   - Athena-Math
   - Athena-Core
   - V8
   - UnitTest++
They are provided as GIT submodules of this repository.
Did you forgot to execute the following commands?
   git submodule init
   git submodule update")
endif()

include("${XMAKE_DEPENDENCIES_DIR}/XMake/XMake.cmake")


##########################################################################################
# Functions

function(create_scripting_module PROJECT NAME JS_FILES)

    string(REPLACE "." ";" NAMESPACES "${NAME}")
    list(LENGTH NAMESPACES NB_NAMESPACES)

    list(GET NAMESPACES -1 LIBRARY_NAME)
    list(REMOVE_AT NAMESPACES -1)

    string(REPLACE ";" "/" LIBRARY_PATH "${NAMESPACES}")

    if (NOT LIBRARY_PATH STREQUAL "")
        set(LIBRARY_PATH "${LIBRARY_PATH}/")
    endif()

    set(JS_SUBFOLDER "${LIBRARY_NAME}/")

    set_target_properties(${XMAKE_${PROJECT}_TARGET} PROPERTIES OUTPUT_NAME "${LIBRARY_NAME}"
                                                                PREFIX "modules/${LIBRARY_PATH}")

    if (NOT JS_FILES STREQUAL "")
        if (WIN32)
            foreach (CONFIG ${CMAKE_CONFIGURATION_TYPES})
                foreach (JS_FILE ${JS_FILES})
                    configure_file("${JS_FILE}" "${XMAKE_BINARY_DIR}/bin/${CONFIG}/modules/${LIBRARY_PATH}js/${JS_SUBFOLDER}${JS_FILE}" COPYONLY)
                endforeach()
            endforeach()
        else()
            foreach (JS_FILE ${JS_FILES})
                configure_file("${JS_FILE}" "${XMAKE_BINARY_DIR}/bin/modules/${LIBRARY_PATH}js/${JS_SUBFOLDER}${JS_FILE}" COPYONLY)
            endforeach()
        endif()
    endif()
endfunction()


##########################################################################################
# Process subdirectories

add_subdirectory(dependencies)
add_subdirectory(src)
add_subdirectory(unittests)
