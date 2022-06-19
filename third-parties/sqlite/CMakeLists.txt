# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only

####################################################################################################

# https://www.sqlite.org/howtocompile.html
# https://www.sqlite.org/compile.html

####################################################################################################

set(SQLITE_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/sqlite-amalgamation")

####################################################################################################

# Always compile with warnings
# if(CMAKE_COMPILER_IS_GNUCC)
#   # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter -std=c99 -pedantic")
#   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter -Wno-int-to-pointer-cast -Wno-maybe-uninitialized -Wno-parentheses")
# endif()
# if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter -Wno-int-to-pointer-cast -Wno-uninitialized -Wno-parentheses")
# endif()

####################################################################################################

# use "_at" suffix to be sure we don't confuse with system SQLite
add_library(sqlite_at SHARED)

target_include_directories(sqlite_at
  INTERFACE
  $<BUILD_INTERFACE:${SQLITE_SOURCE_PATH}>
  # $<INSTALL_INTERFACE:include/mylib>  # <prefix>/include/mylib
)

target_sources(sqlite_at PRIVATE ${SQLITE_SOURCE_PATH}/sqlite3.c)

target_compile_definitions(sqlite_at
  PRIVATE
    # -DSQLITE_THREADSAFE=0
    # -DSQLITE_OMIT_LOAD_EXTENSION
    # -DSQLITE_ENABLE_FTS4 or -DSQLITE_ENABLE_FTS5 for full-text search
    # -DSQLITE_ENABLE_DBSTAT_VTAB for the dbstat virtual table.
    # In order to see extra commentary in EXPLAIN listings, add the -DSQLITE_ENABLE_EXPLAIN_COMMENTS option
    # On unix systems, add -DHAVE_USLEEP=1 if the host machine supports the usleep() system call.

    # required by Qt for API like sqlite3_column_database_name16()
    SQLITE_ENABLE_COLUMN_METADATA

    # in Qt
    # SQLITE_ENABLE_FTS3
    # SQLITE_ENABLE_FTS3_PARENTHESIS

    SQLITE_ENABLE_FTS5
    SQLITE_ENABLE_RTREE # R*Tree index extension
    SQLITE_ENABLE_JSON1 # JSON SQL functions

    SQLITE_OMIT_COMPLETE # This option causes the sqlite3_complete() and sqlite3_complete16() interfaces to be omitted.

    # SQLITE_DISABLE_LFS # Large File System
)

if(ANDROID)
  target_compile_definitions(sqlite_at
    PRIVATE
      # https://www.sqlite.org/tempfiles.html
      # This is important - it causes SQLite to use memory for temp files. Since Android has no globally
      # writable temp directory, if this is not defined the application throws an exception when it
      # tries to create a temp file.
      SQLITE_TEMP_STORE=3
    )
endif(ANDROID)

target_link_libraries(sqlite_at
  PRIVATE
    # The -ldl library is needed to support dynamic loading, the sqlite3_load_extension() interface
    # and the load_extension() SQL function. If these features are not required, then they can be
    # omitted using SQLITE_OMIT_LOAD_EXTENSION compile-time option.
    dl
)

if(ANDROID)
  target_link_libraries(sqlite_at PRIVATE log)
endif(ANDROID)
