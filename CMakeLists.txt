cmake_minimum_required(VERSION 3.5)

project(QSpellWork VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

include_directories(
    src
    src/DBC
)

set(TS_FILES QSpellWork_en_GB.ts)

set(PROJECT_SOURCES
    src/DBC/DBCStructures.hpp
    src/DBC/DBCFileLoader.hpp
    src/DBC/DBCFileLoader.cpp
    src/DBC/DBCStructures.cpp
    src/DBC/DBCStores.hpp
    src/DBC/DBCStores.cpp
    src/DBC/SpellInfoHelper.cpp
    src/SpellInfoTabEvents.cpp
    src/Enums/SpellEnums.hpp
    src/JsonData/JsonData.hpp
    src/JsonData/JsonData.cpp
    src/Globals/appSettings.hpp
    src/Globals/appSettings.cpp
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.hpp
    src/mainwindow.ui
    src/${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QSpellWork
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QSpellWork APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(QSpellWork SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QSpellWork
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(QSpellWork PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(QSpellWork PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QSpellWork
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QSpellWork)
endif()
