cmake_minimum_required(VERSION 3.18)
project(connector)

set(Include_dir ${CMAKE_CURRENT_SOURCE_DIR}/interface/
        ${CMAKE_CURRENT_SOURCE_DIR}/implementation)


if (NOT DEFINED MAIN_DIR)
    set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../.. CACHE PATH MAIN_DIR FORCE)
    message("MAIN_DIR in connector lib dir: ${MAIN_DIR}\n\n")
endif ()

set(deps_include_dir "${MAIN_DIR}/deps/include")
# message("deps_include_dir: ${deps_include_dir}\n\n")

message(WARNING "systems ${CMAKE_SYSTEM_INCLUDE_PATH}")

include_directories(SYSTEM ${Include_dir} ${deps_include_dir} /usr/local/include)


AUX_SOURCE_DIRECTORY(implementation/source SOURCES)


add_library(${PROJECT_NAME} ${SOURCES})
# message(WARNING "building library with these flags: ${CMAKE_CXX_FLAGS}")
if (WITH_TESTING)
    message(WARNING "testing flags: ${testing_flags}")
endif()

message("SOURCES = ${SOURCES}, \n Include_dir = ${Include_dir} \n deps_include_dir = ${deps_include_dir}")
