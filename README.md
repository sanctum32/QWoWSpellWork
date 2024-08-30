QSpellwork is a basic crossplatform tool to show basic information about "World of Warcraft" game spells (originally is inspired by https://github.com/trinitycore/spellwork).
The tool is written in C++ and uses Qt UI framework.

Currently, the tool supports only 4.3.4 (build 15595) data (tested with enGB client)

## Features:
* Cross platform. Runs in Windows and Linux system natively
* Displays spell and spell effect information
* Themes support
* Native look in Linux systems (OS X is not tested)
* JSON data support (mainly used to define definitions names and descriptions)
* JSON formatting - It is possible to customize spell related descriptions without making application code changes
* MariaDB/MySQL connection support. Currently supports only "Cataclysm preservation project's" trinitycore database structure

## Setup:
*To run application, you must have extracted '4.3.4 (build 15595)" dbcs archive files (not provided in this project).*
*json folder contains necessary definitions*

### Requirements:
* CMake 3.5 (or higher)
* Qt5 or Qt6 framework libraries
* C++ compiler with C++20 standart support
* MySQL 8+/MariaDB 10.3+ for sql

### Final setup steps:
1. Copy dbc files to dbc folder in the application executable folder ("appExecutableFolder"/dbc).
2. Copy [json folder](json) to application executable folder ("appExecutableFolder"/json)
3. The application should be ready to be started.

Notes: statusbar at the bottom will indicate the status if DBC and JSON information was loaded successfully
