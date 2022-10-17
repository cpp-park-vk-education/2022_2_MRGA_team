cmake_minimum_required(VERSION 3.18)
PROJECT(connector)
set(CMAKE_CXX_STANDARD 20)

set(cxx_flags "-Werror -Wall -Wextra -Wpedantic\
        -Wredundant-decls -Wsign-conversion\
        -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal")
set(sanitizers_flags "-fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
set(testing_flags "-fprofile-arcs -ftest-coverage -fPIC -O0")
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
    message("WARNING RUN with debugging")
    set(cxx_flags "${cxx_flags} -g -O0")
    set(CMAKE_CXX_FLAGS ${cxx_flags})
    message(WARNING "new cxx flags while debugging:\n ${CMAKE_CXX_FLAGS}")
endif()

if(WITH_TESTING)
    message(WARNING "RUN with testing")
    set(cxx_flags "${cxx_flags} ${testing_flags}")
    set(CMAKE_CXX_FLAGS ${cxx_flags})
    message(WARNING "********\t new cxx flags while testing:\n ${testing_flags}\n")
    message(WARNING "********\t new cxx-linker flags while testing:\n ${CMAKE_EXE_LINKER_FLAGS}\n")
endif()

add_subdirectory(lib)

if(WITH_TESTING)
    if(WITH_MEMCHECK)
        message("\n\nRun with memcheck\n\n")

    elseif(WITH_SANITIZE)
        set(cxx_flags "${cxx_flags} ${sanitizers_flags}")
        set(CMAKE_CXX_FLAGS ${cxx_flags})
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage")
        message("cxx flags = ${CMAKE_CXX_FLAGS}")

        message("\n\nRun with sanitize\n\n")
    endif()
    message("\nrun with testing\n")
    set(MEMORYCHECK_COMMAND "/usr/local/bin/valgrind")
#    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()
