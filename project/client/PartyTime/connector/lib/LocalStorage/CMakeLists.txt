cmake_minimum_required(VERSION 3.18)
PROJECT(LocalStorage)
set(CMAKE_CXX_STANDARD 20)

set(Include_dir ${CMAKE_CURRENT_SOURCE_DIR}/interface/
        ${CMAKE_CURRENT_SOURCE_DIR}/implementation/include)

include_directories(PUBLIC ${Include_dir})


AUX_SOURCE_DIRECTORY(implementation/src SOURCES)

add_library(${PROJECT_NAME} ${SOURCES})

set(LocalStorageLibs ${PROJECT_NAME} PARENT_SCOPE)
set(LocalStorageIncludeDirs ${Include_dir} PARENT_SCOPE)