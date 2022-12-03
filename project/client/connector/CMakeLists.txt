cmake_minimum_required(VERSION 3.18)
PROJECT(connector)
set(CMAKE_CXX_STANDARD 20)

include(cmake/flags.cmake)
include(cmake/options.cmake)
set(CMAKE_CXX_FLAGS ${cxx_flags})
include(cmake/conditions.cmake)



add_subdirectory(lib)

if(WITH_TESTING)
    message("\nrun with testing\n")
    add_subdirectory(tests)
endif()
