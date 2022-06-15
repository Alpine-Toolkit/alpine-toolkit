# -*- CMake -*-

####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
#
# This file is part of the QtCarto library.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# $ALPINE_TOOLKIT_END_LICENSE$
#
####################################################################################################

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

add_library(sqlite
  SHARED
  ${SQLITE_SOURCE_PATH}/sqlite3.c
)
target_link_libraries(sqlite
  # The -ldl library is needed to support dynamic loading, the sqlite3_load_extension() interface
  # and the load_extension() SQL function. If these features are not required, then they can be
  # omitted using SQLITE_OMIT_LOAD_EXTENSION compile-time option.
  dl

  # ???
  log
)
