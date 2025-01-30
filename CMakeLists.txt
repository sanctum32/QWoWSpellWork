cmake_minimum_required(VERSION 3.16)

project(QSpellWork VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# append modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake/modules")

# find REQUIRED components
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/options.cmake)

if (WITH_SQL_SUPPORT)
    find_package(MySQL)

    if (NOT MYSQL_FOUND)
        message(FATAL_ERROR "MYSQL was not found!")
    endif()
endif()

set(TS_FILES
    src/Translations/QSpellWork_en_GB.ts
)

set(UI_FILES
    src/Forms/searchFilter.ui
    src/Forms/searchFilter.hpp
    src/Forms/searchFilter.cpp
    src/Forms/mainwindow.ui
    src/Forms/mainwindow.hpp
    src/Forms/mainwindow.cpp
)

set(PROJECT_SOURCES
    src/DataStores/Loaders/DB2FileLoader.hpp
    src/DataStores/Loaders/DB2FileLoader.cpp
    src/DataStores/Loaders/DBCFileLoader.hpp
    src/DataStores/Loaders/DBCFileLoader.cpp
    src/DataStores/Loaders/DataStoresDefines.hpp
    src/DataStores/Structures/DB2Structures.hpp
    src/DataStores/Structures/DB2Structures.cpp
    src/DataStores/Structures/DBCStructures.hpp
    src/DataStores/Structures/DBCStructures.cpp
    src/DataStores/DataStorage.hpp
    src/DataStores/DataStorage.cpp
    src/Spell/SpellInfo.cpp
    src/Spell/SpellInfoTabEvents.cpp
    src/JsonData/JsonData.hpp
    src/JsonData/JsonData.cpp
    src/Globals/appSettings.hpp
    src/Globals/appSettings.cpp
    src/Globals/SharedDefines.hpp
    src/Globals/ValueComparition.hpp
    src/Globals/ValueComparition.cpp
    src/Globals/SearchFiltersStore.hpp
    src/Globals/SearchFiltersStore.cpp
    src/Enums/SpellEnums.hpp
    src/Enums/UnitDefines.hpp
    src/Enums/CreatureDefines.hpp
    src/main.cpp
    ${UI_FILES}
    ${TS_FILES}
)

if (WITH_SQL_SUPPORT)
    list(APPEND PROJECT_SOURCES
        src/SQL/sqlConnection.hpp
        src/SQL/sqlConnection.cpp)
endif()

set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/src/Forms")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${PROJECT_SOURCES}
    )


# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME} ${PROJECT_SOURCES}
            json/SummonProperties.json)
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${MySQL_LIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    src
    src/DataStores
    src/DataStores/Loaders
    src/DataStores/Structures
    src/Enums
    src/Globals
    src/JsonData
    src/Translations
    src/Forms
    ${MySQL_INCLUDE_DIRS}
)

target_link_directories(${PROJECT_NAME} PRIVATE
    ${MySQL_INCLUDE_DIRS}
)

if (WITH_SQL_SUPPORT)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SPELLWORK_BUILD_SQL)
endif()

if (MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

if (COPY_EXTRA_FILES)
    # copy json
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "$<TARGET_PROPERTY:${PROJECT_NAME},SOURCE_DIR>/json"
            "$<TARGET_PROPERTY:${PROJECT_NAME},BINARY_DIR>/json"
    )

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "$<TARGET_PROPERTY:${PROJECT_NAME},SOURCE_DIR>/themes"
            "$<TARGET_PROPERTY:${PROJECT_NAME},BINARY_DIR>/themes"
    )

    # copy qtlogging.ini
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_PROPERTY:${PROJECT_NAME},SOURCE_DIR>/qtlogging.ini.const"
            "$<TARGET_PROPERTY:${PROJECT_NAME},BINARY_DIR>/qtlogging.ini.const"
    )
endif()


