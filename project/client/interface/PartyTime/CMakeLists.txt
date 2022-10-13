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
find_package(Qt6 REQUIRED COMPONENTS Network)

set(TS_FILES PartyTime_ru_RU.ts)
set(COMPONENTS)

# GENERAL INCLUDES FINISHED

enable_testing()

add_subdirectory(Components)
add_subdirectory(Pages)
set(INTERFACE_LIB_NAME "interface")
add_subdirectory(API)
set(API_LIB_NAME "network")

#add_subdirectory(tests)

set(PROJECT_SOURCES
        main.cpp
        base.cpp
        base.h
        painter.cpp
        painter.hpp
        base.ui
        static.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

target_link_libraries(${PROJECT_NAME} PRIVATE ${API_LIB} ${PAGES_LIB} ${COMPONENTS_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC ${API_INCLUDE_DIRS} ${PAGES_INCLUDE_DIRS} ${COMPONENTS_INCLUDE_DIRS})

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(PartyTime SHARED
            ${PROJECT_SOURCES}
            target_link_libraries(${PROJECT_NAME} PRIVATE ${API_LIB} ${PAGES_LIB} ${COMPONENTS_LIB})
            target_include_directories(${PROJECT_NAME} PUBLIC ${API_INCLUDE_DIRS} ${PAGES_INCLUDE_DIRS} ${COMPONENTS_INCLUDE_DIRS})
        )
    else()
        add_executable(PartyTime
            ${PROJECT_SOURCES}
            target_link_libraries(${PROJECT_NAME} PRIVATE ${API_LIB} ${PAGES_LIB} ${COMPONENTS_LIB})
            target_include_directories(${PROJECT_NAME} PUBLIC ${API_INCLUDE_DIRS} ${PAGES_INCLUDE_DIRS} ${COMPONENTS_INCLUDE_DIRS})
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(PartyTime PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
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

#cmake_minimum_required(VERSION 3.5)

#project(NewMeeUpClient VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
#find_package(Qt6 REQUIRED COMPONENTS Network)


#set(PROJECT_SOURCES
#        main.cpp
#        painter.cpp
#        painter.hpp
#        base.cpp
#        base.h
#        static.qrc
#)

#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#    qt_add_executable(NewMeeUpClient
#        MANUAL_FINALIZATION
#        ${PROJECT_SOURCES}
#    )
## Define target properties for Android with Qt 6 as:
##    set_property(TARGET NewMeeUpClient APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
##                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
## For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
#else()
#    if(ANDROID)
#        add_library(NewMeeUpClient SHARED
#            ${PROJECT_SOURCES}
#        )
## Define properties for Android with Qt 5 after find_package() calls as:
##    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    else()
#        add_executable(NewMeeUpClient
#            ${PROJECT_SOURCES}
#        )
#    endif()
#endif()

#target_link_libraries(NewMeeUpClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(NewMeeUpClient PRIVATE Qt6::Network)

#set_target_properties(NewMeeUpClient PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE TRUE
#)

#if(QT_VERSION_MAJOR EQUAL 6)
#    qt_finalize_executable(NewMeeUpClient)
#endif()
