cmake_minimum_required(VERSION 3.18)
project(connector)

if (NOT DEFINED MAIN_DIR)
    set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../.. CACHE PATH MAIN_DIR FORCE)
    include_directories(SYSTEM ${MAIN_DIR}/deps/include)
    message("MAIN_DIR in connector lib dir: ${MAIN_DIR}\n\n")
endif ()


add_subdirectory(HttpConnector)
add_subdirectory(LocalStorage)
add_subdirectory(PartyTimeConnector)
message(WARNING "building library with these flags: ${CMAKE_CXX_FLAGS}")

if (WITH_TESTING)
    message(WARNING "testing flags: ${testing_flags}")
endif()

set(PartyTimeConnectorLibs ${PartyTimeConnectorLibs} ${HTTPConnectorLibs} ${LocalStorageLibs} PARENT_SCOPE)
set(HTTPConnectorLibs ${HTTPConnectorLibs} PARENT_SCOPE)
set(LocalStorageLibs ${LocalStorageLibs} PARENT_SCOPE)

set(PartyTimeConnectorIncludeDirs ${PartyTimeConnectorIncludeDirs} PARENT_SCOPE)
set(LocalStorageIncludeDirs ${LocalStorageIncludeDirs} PARENT_SCOPE)
set(HTTPConnectorIncludeDirs ${HTTPConnectorIncludeDirs} PARENT_SCOPE)
