QSpellwork is a basic crossplatform tool to show basic information about "World of Warcraft" game spells (originally is inspired by https://github.com/trinitycore/spellwork).
The tool is written in C++ and uses Qt UI framework.

Currently, the tool supports only 4.3.4 (build 15595) data (tested with enGB client).

NOTING: tool is not in alpha or beta stage. Tool development currently is at design/creation stage.

## Features:
* Cross platform. Runs in Windows and Linux system natively
* Displays spell and spell effect information
* Themes support
* JSON data support (mainly used to define definitions names and descriptions)
* JSON formatting - It is possible to customize spell related descriptions without making application code changes
* MariaDB/MySQL connection support. Currently supports only "Cataclysm preservation project's" trinitycore database structure
* Spell filters
* DBC and DB2 archive support

## Setup:
*To run application, you must have extracted '4.3.4 (build 15595)" dbcs archive files (not provided in this project).*
*json folder contains necessary definitions*

### Requirements:
* CMake >= 3.16
* Qt5 or Qt6 framework libraries (https://www.qt.io)
* C++ compiler with C++20 standart support (Mingw, GCC >= 8, MSVC >= 16.0 (visual studio 2019), clang >= 10)
* MySQL 8+/MariaDB 10.3+ for sql

### CMake notes:
* In order to have SQL support, generate cmake build with options -DWITH_SQL_SUPPORT=1.
If you build in windows, use -DMYSQL_ROOT=root_path_to_mysql, for example: -DMYSQL_ROOT=C:/MySQL (or -DMYSQL_ROOT=C:/MariaDB)
* JSON and Themes folders can be copied after build, for this option use -DCOPY_EXTRA_FILES=1

### Final setup steps:
1. Copy dbc files to dbc folder in the application executable folder ("appExecutableFolder"/dbc).
2. Rename file appSettings.json.const to appSettings.json (can be found in json folder which can be found in executable binary folder).
    Once file is renamed, you can customize settings in appSettings.json (can be opened with most text editors, for example - notepad or kate).
2. The application should be ready to be started.

PS: statusbar at the bottom will indicate the status about SQL, DBC and JSON status

If json fails to load, spell information may will lack some details
