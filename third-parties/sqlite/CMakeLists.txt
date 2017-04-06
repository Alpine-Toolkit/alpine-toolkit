# -*- CMake -*-

####################################################################################################

# cf. https://www.sqlite.org/compile.html

# Qt sqlite.pri
#
# CONFIG(release, debug|release):DEFINES *= NDEBUG
# # DEFINES += SQLITE_OMIT_LOAD_EXTENSION SQLITE_OMIT_COMPLETE SQLITE_ENABLE_FTS3 SQLITE_ENABLE_FTS3_PARENTHESIS SQLITE_ENABLE_RTREE
# DEFINES += SQLITE_OMIT_COMPLETE SQLITE_ENABLE_FTS3 SQLITE_ENABLE_FTS3_PARENTHESIS SQLITE_ENABLE_RTREE
# !contains(CONFIG, largefile):DEFINES += SQLITE_DISABLE_LFS
# contains(QT_CONFIG, posix_fallocate):DEFINES += HAVE_POSIX_FALLOCATE=1
# winrt: DEFINES += SQLITE_OS_WINRT
# winphone: DEFINES += SQLITE_WIN32_FILEMAPPING_API=1
# qnx: DEFINES += _QNX_SOURCE
# integrity: QMAKE_CFLAGS += -include qplatformdefs.h
# INCLUDEPATH +=  $$PWD/sqlite
# SOURCES +=      $$PWD/sqlite/sqlite3.c
# LIBS += -ldl
#
# TR_EXCLUDE += $$PWD/*

# Geopaparazzi
#
# # SQLite flags copied from ASOP
# common_sqlite_flags := \
#  -DHAVE_USLEEP=1 \
#  -DSQLITE_DEFAULT_JOURNAL_SIZE_LIMIT=1048576 \
#  -DSQLITE_THREADSAFE=1 \
#  -DNDEBUG=1 \
#  -DSQLITE_ENABLE_MEMORY_MANAGEMENT=1 \
#  -DSQLITE_DEFAULT_AUTOVACUUM=1 \
#  -DSQLITE_TEMP_STORE=3 \
#  -DSQLITE_ENABLE_FTS3 \
#  -DSQLITE_ENABLE_FTS3_BACKWARDS \
#  -DSQLITE_ENABLE_RTREE=1 \
#  -DSQLITE_DEFAULT_FILE_FORMAT=4

####################################################################################################

set(SQLITE_SOURCE_PATH "sqlite-amalgamation")

####################################################################################################

# Always compile with warnings
if(CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter -std=c99 -pedantic")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter -Wno-int-to-pointer-cast -Wno-maybe-uninitialized -Wno-parentheses")
endif()

####################################################################################################

include_directories(${SQLITE_SOURCE_PATH})

ADD_DEFINITIONS(
  # -DSQLITE_OMIT_LOAD_EXTENSION
  # -DSQLITE_OMIT_COMPLETE # This option causes the sqlite3_complete() and sqlite3_complete16() interfaces to be omitted.
  # -DSQLITE_DISABLE_LFS # Large File System

  # If using SEE, uncomment the following:
  # -DSQLITE_HAS_CODEC

  -DSQLITE_ENABLE_FTS3 # version 3 of the full-text search engine
  -DSQLITE_ENABLE_FTS3_PARENTHESIS
  -DSQLITE_ENABLE_FTS5
  -DSQLITE_ENABLE_JSON1 # JSON SQL functions
  -DSQLITE_ENABLE_RTREE # R*Tree index extension

  # SQLITE_SOUNDEX
  )

if(ANDROID)
  ADD_DEFINITIONS(
    # This is important - it causes SQLite to use memory for temp files. Since Android has no globally
    # writable temp directory, if this is not defined the application throws an exception when it
    # tries to create a temp file.
    -DSQLITE_TEMP_STORE=3

    -DHAVE_STRCHRNUL=0

    "-DPACKED=__attribute__ ((packed))"
    )
endif(ANDROID)

add_library(sqlite
  SHARED
  ${SQLITE_SOURCE_PATH}/sqlite3.c
  )
target_link_libraries(sqlite dl) # log

####################################################################################################
#
# End
#
####################################################################################################
