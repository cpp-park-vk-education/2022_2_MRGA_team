cmake_minimum_required(VERSION 3.14)

project("PagesLib")

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/**/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/**/*.h)

find_package(QT NAMES Qt6 COMPONENTS Widgets SvgWidgets LinguistTools test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets SvgWidgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS MultimediaWidgets)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
set(PAGES_LIB_NAME pages)
set(PAGES_LIB_DEP ${CMAKE_CURRENT_SOURCE_DIR}/AuthorizationPage ${CMAKE_CURRENT_SOURCE_DIR}/EventViewPage
${CMAKE_CURRENT_SOURCE_DIR}/LoadingPage ${CMAKE_CURRENT_SOURCE_DIR}/OrganizerPage ${CMAKE_CURRENT_SOURCE_DIR}/ProfilePage ${CMAKE_CURRENT_SOURCE_DIR}/RegistrationPage
${CMAKE_CURRENT_SOURCE_DIR}/VisitorEventListPage ${CMAKE_CURRENT_SOURCE_DIR}/VisitorPage ${CMAKE_CURRENT_SOURCE_DIR}/Settings)

add_library(${PAGES_LIB_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PAGES_LIB_NAME} ${COMPONENTS_LIB} Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::SvgWidgets Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets)
target_include_directories(${PAGES_LIB_NAME} PUBLIC ${PAGES_LIB_DEP} ${COMPONENTS_INCLUDE_DIRS})

# подключение зависимости connector.
target_include_directories(${PAGES_LIB_NAME} PUBLIC ${PartyTimeConnectorIncludeDirs})
target_link_libraries(${PAGES_LIB_NAME}  ${PartyTimeConnectorLibs})

set(PAGES_LIB ${PAGES_LIB_NAME})
set(PAGES_LIB ${PAGES_LIB} PARENT_SCOPE)
set(PAGES_INCLUDE_DIRS ${PAGES_LIB_NAME} ${PAGES_LIB_DEP})
set(PAGES_INCLUDE_DIRS ${PAGES_INCLUDE_DIRS} PARENT_SCOPE)

message("PAGES_LIB = ${PAGES_LIB}")
message("PAGES_INCLUDE_DIRS = ${PAGES_INCLUDE_DIRS}")
