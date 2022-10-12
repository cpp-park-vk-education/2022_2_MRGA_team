cmake_minimum_required(VERSION 3.5)

project(PartyTime VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Network)

set(TS_FILES PartyTime_ru_RU.ts)
set(COMPONENTS)

#file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/pages/**/*.cpp)
#file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/pages/**/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/pages/**/*.h)

#add_library(${LIB_NAME} ${SOURCES} ${HEADERS})

include_directories(pages pages/AuthorizationPage componentes componentes/UI/Button componentes/UI/Input componentes/UI/Loader componentes/UI/Select componentes/UI/MyModal components/EventFilter)
#include_directories(componentes componentes/EventFilter)
#componentes/EventForm componentes/EventItem componentes/EventList componentes/Ui componentes/Ui/Button componentes/Ui/Input componentes/Ui/Loader componentes/Ui/MyModal componentes/Ui/Navbar componentes/Ui/Select API API/GetService API/PostService

set(PROJECT_SOURCES
        main.cpp
        base.cpp
        base.h
        base.ui
        painter.hpp
        painter.cpp
        pages/AuthorizationPage/authorization.cpp
        pages/AuthorizationPage/authorization.hpp
        pages/EventViewPage/eventView.cpp
        pages/EventViewPage/eventView.hpp

        static.qrc
#        componentes/EventFilter/EventFilter.cpp
#        componentes/EventFilter/EventFilter.hpp
#        componentes/EventFilter/EventForm.cpp
#        componentes/EventFilter/EventForm.hpp
#        componentes/EventFilter/EventItem.cpp
#        componentes/EventFilter/EventItem.hpp
#        componentes/EventFilter/EventList.cpp
#        componentes/EventFilter/EventList.hpp
#        API/GetService/GetService.cpp
#        API/GetService/GetService.hpp
#        API/GetService/PostService.cpp
#        API/GetService/PostService.hpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PartyTime
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PartyTime APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(PartyTime SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PartyTime
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(PartyTime PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(PartyTime PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PartyTime)
endif()
