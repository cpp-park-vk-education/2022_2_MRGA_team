cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "PartyTime")
project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)

set(TS_FILES PartyTime_ru_RU.ts)
set(COMPONENTS)

# GENERAL INCLUDES FINISHED

enable_testing()


add_subdirectory(Pages)
add_subdirectory(Components)
add_subdirectory(API)
set(API_LIB_NAME "network")

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

target_link_libraries(${PROJECT_NAME} PUBLIC ${API_LIB} ${PAGES_LIB} ${COMPONENTS_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC ${API_INCLUDE_DIRS} ${PAGES_INCLUDE_DIRS} ${COMPONENTS_INCLUDE_DIRS})

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(PartyTime SHARED
            ${PROJECT_SOURCES}
            target_link_libraries(${PROJECT_NAME} PUBLIC ${API_LIB} ${PAGES_LIB} ${COMPONENTS_LIB})
            target_include_directories(${PROJECT_NAME} PUBLIC ${API_INCLUDE_DIRS} ${PAGES_INCLUDE_DIRS} ${COMPONENTS_INCLUDE_DIRS})
        )
    else()
        add_executable(PartyTime
            ${PROJECT_SOURCES}
            target_link_libraries(${PROJECT_NAME} PUBLIC ${API_LIB} ${PAGES_LIB} ${COMPONENTS_LIB})
            target_include_directories(${PROJECT_NAME} PUBLIC ${API_INCLUDE_DIRS} ${PAGES_INCLUDE_DIRS} ${COMPONENTS_INCLUDE_DIRS})
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

#target_link_libraries(PartyTime PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(PartyTime PRIVATE Qt6::Network)

set_target_properties(PartyTime PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
