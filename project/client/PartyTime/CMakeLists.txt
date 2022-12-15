cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME "PartyTime")
project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

if (NOT DEFINED MAIN_DIR)
    set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../.. CACHE PATH MAIN_DIR FORCE)
    include_directories(SYSTEM ${MAIN_DIR}/deps/include)
endif ()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
SET(QT_USE_QTMULTIMEDIA TRUE)
SET(QT_USE_QTMULTIMEDIAWIDGETS TRUE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Widgets SvgWidgets LinguistTools test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets SvgWidgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS MultimediaWidgets)

set(TS_FILES PartyTime_ru_RU.ts)
set(COMPONENTS)

# GENERAL INCLUDES FINISHED

enable_testing()

include_directories(SYSTEM /opt/homebrew/include)

add_subdirectory(Components)
add_subdirectory(connector)
add_subdirectory(Pages)

set(PROJECT_SOURCES
        main.cpp
        base.cpp
        base.h
        base.ui
        static.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )


target_link_libraries(${PROJECT_NAME} PUBLIC ${API_LIB} ${PAGES_LIB} ${COMPONENTS_LIB} ${PartyTimeConnectorLibs} Qt${QT_VERSION_MAJOR}::SvgWidgets Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets)
target_include_directories(${PROJECT_NAME} PUBLIC ${API_INCLUDE_DIRS} ${PAGES_INCLUDE_DIRS} ${COMPONENTS_INCLUDE_DIRS} ${PartyTimeConnectorIncludeDirs})

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
            target_link_libraries(${PROJECT_NAME} PUBLIC ${API_LIB} ${PAGES_LIB} ${COMPONENTS_LIB} ${PartyTimeConnectorLibs} Qt${QT_VERSION_MAJOR}::SvgWidgets Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets)
            target_include_directories(${PROJECT_NAME} PUBLIC ${API_INCLUDE_DIRS} ${PAGES_INCLUDE_DIRS} ${COMPONENTS_INCLUDE_DIRS} ${PartyTimeConnectorIncludeDirs})
        )
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
            target_link_libraries(${PROJECT_NAME} PUBLIC ${API_LIB} ${PAGES_LIB} ${COMPONENTS_LIB} ${PartyTimeConnectorLibs} Qt${QT_VERSION_MAJOR}::SvgWidgets Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets)
            target_include_directories(${PROJECT_NAME} PUBLIC ${API_INCLUDE_DIRS} ${PAGES_INCLUDE_DIRS} ${COMPONENTS_INCLUDE_DIRS} ${PartyTimeConnectorIncludeDirs})
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Network Qt${QT_VERSION_MAJOR}::SvgWidgets Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

set(API_LIB ${API_LIB} PARENT_SCOPE)
set(PAGES_LIB ${PAGES_LIB} PARENT_SCOPE)
set(COMPONENTS_LIB ${COMPONENTS_LIB} PARENT_SCOPE)
