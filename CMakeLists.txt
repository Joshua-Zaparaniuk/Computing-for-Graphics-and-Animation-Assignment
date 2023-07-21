if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
    set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

cmake_minimum_required(VERSION 3.5)

project(FlockGUIBUILD VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ui)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(NGL CONFIG REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(include $ENV{HOME}/NGL/include)
include_directories(include {$PROJECT_SOURCE_DIR}/include)

add_executable(${target_sources} FlockGUI)

target_sources(FlockGUI PRIVATE
        src/main.cpp
        src/mainwindow.cpp
        src/Boid.cpp
        src/Flock.cpp
        src/NGLScene.cpp
        src/NGLSceneMouseControls.cpp
        include/mainwindow.h
        include/WindowParams.h
        include/Flock.h
        include/Boid.h
        include/NGLScene.h
        ui/mainwindow.ui
)

target_link_libraries(FlockGUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets NGL)

add_custom_target(FlockGUICopyShaders ALL
 COMMAND ${CMAKE_COMMAND} -E copy_directory
 ${CMAKE_CURRENT_SOURCE_DIR}/shaders
 ${CMAKE_BUILD_DIR}/shaders
 )
