# Outer Makefile (MousePaw Media Build System)
# Version: 3.2.0

# CHANGE: Library name
LIB_PROJECT = SIMPLEXpress

# CHANGE: Executable name
EXE_PROJECT = SIMPLEXpress Tester

# CHANGE: Project base filenames
LIB_NAME = simplexpress
EXE_NAME = $(LIB_NAME)-tester

# CHANGE: Target/alias name for executable (optional)
EXE_NICKNAME = tester

# CHANGE: Uncomment for header-only libraries.
#HEADER_ONLY = 1

# CHANGE: Library source directory
LIB_SRC = $(LIB_NAME)-source
# CHANGE: Executable source directory
EXE_SRC = $(EXE_NAME)

# CHANGE: Ready directory name
READY_DIR = $(LIB_NAME)

# Includes outer makefile logic. (Change if necessary to point to outer.mk)
include build_system/outer.mk
