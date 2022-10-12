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

set(LIB_NAME client_interface)

#file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
#file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)

#add_library(${LIB_NAME} ${SOURCES} ${HEADERS})

#target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Pages/AuthorizationPage)

#enable_testing()
#add_subdirectory(API)
#add_subdirectory(Components)
#add_subdirectory(Pages)

#message("NumbersCounterLib_LIB = ${NumbersCounterLib_LIB}")
#message("NumbersCounterLib_INCLUDE_DIRS = ${NumbersCounterLib_INCLUDE_DIRS}")

#add_executable(${PROJECT_NAME} main.cpp)

#target_link_libraries(${PROJECT_NAME} PRIVATE ${NumbersCounterLib_LIB})
#target_include_directories(${PROJECT_NAME} PUBLIC ${NumbersCounterLib_INCLUDE_DIRS}

include_directories(Pages Pages/AuthorizationPage
    Componentes Components/UI Components/UI/Button Components/UI/Input Components/UI/Loader Components/UI/MyModal Components/UI/Navbar Components/UI/Select
    Components/EventFilter Components/EventForm Components/EventItem Components/EventList
    API API/PostService API/GetService)

set(PROJECT_SOURCES
        main.cpp
        base.cpp
        base.h
        base.ui
        painter.hpp
        painter.cpp
        Pages/AuthorizationPage/authorization.cpp
        Pages/AuthorizationPage/authorization.hpp
        Pages/EventViewPage/eventView.cpp
        Pages/EventViewPage/eventView.hpp
        Components/UI/Button/Button.cpp
        Components/UI/Button/Button.hpp
        Components/UI/Input/Input.cpp
        Components/UI/Input/Input.hpp
        Components/UI/Loader/Loader.cpp
        Components/UI/Loader/Loader.hpp
        Components/UI/MyModal/MyModal.cpp
        Components/UI/MyModal/MyModal.hpp
        Components/UI/Navbar/Navbar.cpp
        Components/UI/Navbar/Navbar.hpp
        Components/UI/Select/Select.cpp
        Components/UI/Select/Select.hpp
        Components/EventFilter/EventFilter.cpp
        Components/EventFilter/EventFilter.hpp
        Components/EventForm/EventForm.cpp
        Components/EventForm/EventForm.hpp
        Components/EventItem/EventItem.cpp
        Components/EventItem/EventItem.hpp
        Components/EventList/EventList.cpp
        Components/EventList/EventList.hpp
        API/PostService/PostService.cpp
        API/PostService/PostService.hpp
        API/GetService/GetService.cpp
        API/GetService/GetService.hpp

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
