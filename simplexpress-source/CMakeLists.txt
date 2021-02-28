# CMake Config (MousePaw Media Build System)
# Version: 3.2.0

# CHANGE: Name your project here
project("SIMPLEXpress")

# Specify the verison being used.
cmake_minimum_required(VERSION 3.8)

# Import user-specified library path configuration
message("Using ${CONFIG_FILENAME}.config")
include(${CMAKE_HOME_DIRECTORY}/../${CONFIG_FILENAME}.config)

# CHANGE: Specify output binary name
set(TARGET_NAME "simplexpress")

# SELECT: Project artifact type
set(ARTIFACT_TYPE "library")
#set(ARTIFACT_TYPE "executable")

# CHANGE: Find dynamic library dependencies.



# CHANGE: Include headers of dependencies.
set(INCLUDE_LIBS
    ${NIMBLY_DIR}/include
    ${GOLDILOCKS_DIR}/include
    ${IOSQUEAK_DIR}/include
    ${ONESTRING_DIR}/include
    ${ARCTICTERN_DIR}/include
    ${EVENTPP_DIR}/include
)

# CHANGE: Include files to compile.
set(FILES
    include/simplexpress/char_sets.hpp
    include/simplexpress/lex_test.hpp
    include/simplexpress/rules.hpp
    include/simplexpress/simplex.hpp
    include/simplexpress/simplex_test.hpp
    include/simplexpress/snag_test.hpp
    include/simplexpress/specifier.hpp
    include/simplexpress/unit.hpp
    include/simplexpress/unit_parser.hpp
    include/simplexpress/unit_parser_test.hpp
    include/simplexpress/utf_tools.hpp
    src/char_sets.cpp
    src/lex_test.cpp
    src/rules.cpp
    src/simplex.cpp
    src/simplex_test.cpp
    src/snag_test.cpp
    src/specifier.cpp
    src/unit.cpp
    src/unit_parser.cpp
    src/unit_parser_test.cpp
    src/utf_tools.cpp
)

# CHANGE: Link against dependencies.
set(LINK_LIBS
    ${NIMBLY_DIR}/lib/libnimbly.a
    ${GOLDILOCKS_DIR}/lib/libgoldilocks.a
    ${IOSQUEAK_DIR}/lib/libiosqueak.a
)

# Imports build script. (Change if necessary to point to build.cmake)
include(${CMAKE_HOME_DIRECTORY}/../build_system/build.cmake)
