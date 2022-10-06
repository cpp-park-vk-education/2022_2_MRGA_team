cmake_minimum_required(VERSION 3.23)
PROJECT(connector)
set(CMAKE_CXX_STANDARD 20)

set(cxx_flags "-Wall -Wextra -Wpedantic -fprofile -fprofile-arcs -Wredundant-decls -Wsign-conversion -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal")
set(sanitizers_flags "-fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
set(CMAKE_CXX_FLAGS ${cxx_flags})

if (NOT DEFINED MAIN_DIR)
    set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../.. CACHE PATH MAIN_DIR FORCE)
    message("MAIN_DIR in connector dir: ${MAIN_DIR}\n\n")
endif ()

OPTION(WITH_DEBUG "Run with debug" OFF)
OPTION(WITH_TESTING "Run with testing" OFF)
OPTION(WITH_MEMCHECK "Run with memcheck" OFF)
OPTION(WITH_SANITIZE "Run with sanitize" OFF)


if(WITH_DEBUG)
    message("RUN with debugging")
    set(cxx_flags "${cxx_flags} -g -O0")
    set(CMAKE_CXX_FLAGS ${cxx_flags})
    message("cxx flags = ${CMAKE_CXX_FLAGS}")
endif()


add_subdirectory(lib)

if(WITH_TESTING)
    if(WITH_MEMCHECK)
        message("\n\nRun with memcheck\n\n")

    elseif(WITH_SANITIZE)
        set(cxx_flags "${cxx_flags} ${sanitizers_flags}")
        set(CMAKE_CXX_FLAGS ${cxx_flags})
        message("cxx flags = ${CMAKE_CXX_FLAGS}")

        message("\n\nRun with sanitize\n\n")
    endif()
    message("\n\nrun with testing\n\n")
    enable_testing()
    add_subdirectory(tests)
endif()
