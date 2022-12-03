cmake_minimum_required(VERSION 3.18)
project(struct_mapping_lib)

file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS *.hpp)

include_directories(options)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
        ${PROJECT_NAME}
        INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(STRUCT_MAPPING_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(STRUCT_MAPPING_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)