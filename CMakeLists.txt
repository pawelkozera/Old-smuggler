cmake_minimum_required(VERSION 3.5)

project(smuggler VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        map.cpp
        map.h
        island.cpp
        island.h
        movingspeed.cpp
        movingspeed.h
        playercharacter.cpp
        playercharacter.h
        eventhandler.cpp
        eventhandler.h
        interactiveobject.cpp
        interactiveobject.h
        resources.cpp
        resources.h
        playerplane.cpp
        playerplane.h
        settings.cpp
        settings.h
        alert.cpp
        alert.h
        fuel.cpp
        fuel.h
        sounds.cpp
        sounds.h
        interface.cpp
        interface.h
        receiver.cpp
        receiver.h
	menu.h
        menu.cpp
        wind.h
        wind.cpp
        compass.h
        compass.cpp
        score.h
        score.cpp
        hallOfFame.h
        hallOfFame.cpp
        antiaircraftgun.cpp
        antiaircraftgun.h
        bullet.cpp
        bullet.h
        cloud.h
        cloud.cpp
        enemyplane.cpp
        enemyplane.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(smuggler
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET smuggler APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(smuggler SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(smuggler
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(smuggler PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(smuggler PRIVATE Qt6::Multimedia)

set_target_properties(smuggler PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS smuggler
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(smuggler)
endif()
