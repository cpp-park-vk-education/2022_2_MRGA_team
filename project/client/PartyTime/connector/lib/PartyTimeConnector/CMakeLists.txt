PROJECT(PartyTimeConnector)
set(CMAKE_CXX_STANDARD 20)


set(Include_dir
        ${CMAKE_CURRENT_SOURCE_DIR}/interface/
        ${CMAKE_CURRENT_SOURCE_DIR}/implementation/include
        ${HTTPConnectorIncludeDirs}
        ${LocalStorageIncludeDirs})

include_directories(PUBLIC ${Include_dir})
include_directories(SYSTEM /usr/local/include)

AUX_SOURCE_DIRECTORY(implementation/src SOURCES)

add_library(${PROJECT_NAME} ${SOURCES})


set(PartyTimeConnectorLibs ${PROJECT_NAME} PARENT_SCOPE)
set(PartyTimeConnectorIncludeDirs ${Include_dir} PARENT_SCOPE)