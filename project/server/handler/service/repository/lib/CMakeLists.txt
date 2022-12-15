cmake_minimum_required(VERSION 3.14)
project(postgres_lib)

if(WITH_TESTING)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_TEST_FLAGS}")
endif()

include_directories(SYSTEM ${MAIN_DIR}/deps/include)

set(MY_INCLUDE_DIRS "include")
set(MY_INTERFACE_DIRS "interface")

file(GLOB SOURCES "src/*.cpp")
file(GLOB INCLUDE_DIRS ${MY_INCLUDE_DIRS})
file(GLOB INTERFACE_DIRS ${MY_INTERFACE_DIRS})

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS} ${INTERFACE_DIRS})

set(POSTGRES_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(POSTGRES_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
