# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only

####################################################################################################

# cf. https://www.sqlite.org/howtocompile.html

####################################################################################################

set(SQLITE_SOURCE_PATH "sqlite-amalgamation")

####################################################################################################

# Always compile with warnings
if(CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter -std=c99 -pedantic")
  #Fixme: warning: unknown warning option '-Wno-maybe-uninitialized'; did you mean '-Wno-uninitialized'? [-Wunknown-warning-option
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter -Wno-int-to-pointer-cast -Wno-maybe-uninitialized -Wno-parentheses")
endif()

####################################################################################################

include_directories(${SQLITE_SOURCE_PATH})

add_compile_definitions(
  # -DSQLITE_THREADSAFE=0
  # -DSQLITE_OMIT_LOAD_EXTENSION
  # -DSQLITE_ENABLE_FTS4 or -DSQLITE_ENABLE_FTS5 for full-text search
  # -DSQLITE_ENABLE_RTREE for the R*Tree search engine extension
  # -DSQLITE_ENABLE_JSON1 to include JSON SQL functions
  # -DSQLITE_ENABLE_DBSTAT_VTAB for the dbstat virtual table.
  # In order to see extra commentary in EXPLAIN listings, add the -DSQLITE_ENABLE_EXPLAIN_COMMENTS option
  # On unix systems, add -DHAVE_USLEEP=1 if the host machine supports the usleep() system call.

  SQLITE_ENABLE_FTS5
  SQLITE_ENABLE_RTREE # R*Tree index extension
  SQLITE_ENABLE_JSON1 # JSON SQL functions

  # SQLITE_OMIT_COMPLETE # This option causes the sqlite3_complete() and sqlite3_complete16() interfaces to be omitted.
  # SQLITE_DISABLE_LFS # Large File System
)

if(ANDROID)
  add_compile_definitions(
    # https://www.sqlite.org/tempfiles.html
    # This is important - it causes SQLite to use memory for temp files. Since Android has no globally
    # writable temp directory, if this is not defined the application throws an exception when it
    # tries to create a temp file.
    SQLITE_TEMP_STORE=3

    # ???
    # HAVE_STRCHRNUL=0

    # ???
    # "PACKED=__attribute__ ((packed))"
    )
endif(ANDROID)

add_library(sqlite_at
  SHARED
  ${SQLITE_SOURCE_PATH}/sqlite3.c
)
target_link_libraries(sqlite_at
  # The -ldl library is needed to support dynamic loading, the sqlite3_load_extension() interface
  # and the load_extension() SQL function. If these features are not required, then they can be
  # omitted using SQLITE_OMIT_LOAD_EXTENSION compile-time option.
  dl
)

if(ANDROID)
  target_link_libraries(sqlite_at
    log
  )
endif(ANDROID)
