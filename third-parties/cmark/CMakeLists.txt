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

set(CMARK_SOURCE_PATH "cmark.git")

####################################################################################################

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 27)
set(PROJECT_VERSION_PATCH 1)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} )

configure_file(${CMARK_SOURCE_PATH}/src/cmark_version.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/cmark_version.h)

####################################################################################################

if (${CMAKE_VERSION} VERSION_GREATER "1.8")
  set(CMAKE_C_VISIBILITY_PRESET hidden)
  set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
elseif(CMAKE_COMPILER_IS_GNUCC OR ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
endif ()

include(GenerateExportHeader)

####################################################################################################

# Always compile with warnings
if(CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter -std=c99 -pedantic")
endif()

# Check integrity of node structure when compiled as debug:
# set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCMARK_DEBUG_NODES -DDEBUG")
# set(CMAKE_LINKER_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG}")

####################################################################################################

# Feature tests
include(CheckIncludeFile)
include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckSymbolExists)
CHECK_INCLUDE_FILE(stdbool.h HAVE_STDBOOL_H)
CHECK_C_SOURCE_COMPILES(
  "int main() { __builtin_expect(0,0); return 0; }"
  HAVE___BUILTIN_EXPECT)
CHECK_C_SOURCE_COMPILES("
  int f(void) __attribute__ (());
  int main() { return 0; }
" HAVE___ATTRIBUTE__)

CONFIGURE_FILE(
  ${CMARK_SOURCE_PATH}/src/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/config.h)

####################################################################################################

include_directories(${CMARK_SOURCE_PATH}/src)
include_directories(${CMARK_SOURCE_PATH}/extensions)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(EXTENSIONS_HEADERS
  autolink.h
  core-extensions.h
  ext_scanners.h
  ext_scanners.re
  strikethrough.h
  table.h
  tagfilter.h
  )

set(EXTENSIONS_SOURCES
    autolink.c
    core-extensions.c
    ext_scanners.c
    ext_scanners.re
    strikethrough.c
    table.c
    tagfilter.c
    ${EXTENSIONS_HEADERS}
   )

PREPEND(EXTENSIONS_SOURCES ${CMARK_SOURCE_PATH}/extensions ${EXTENSIONS_SOURCES})

add_library(cmark-extensions
  STATIC
  ${EXTENSIONS_SOURCES}
  )

generate_export_header(cmark-extensions BASE_NAME cmarkextensions)

set(CORE_HEADERS
  buffer.h
  chunk.h
  cmark.h
  cmark_ctype.h
  cmark_extension_api.h
  houdini.h
  inlines.h
  iterator.h
  node.h
  parser.h
  plugin.h
  references.h
  registry.h
  render.h
  scanners.h
  syntax_extension.h
  utf8.h
  )

set(CORE_SOURCES
  arena.c
  blocks.c
  buffer.c
  cmark.c
  cmark_ctype.c
  commonmark.c
  houdini_href_e.c
  houdini_html_e.c
  houdini_html_u.c
  html.c
  inlines.c
  iterator.c
  latex.c
  linked_list.c
  man.c
  node.c
  plugin.c
  references.c
  registry.c
  render.c
  scanners.c
  scanners.re
  syntax_extension.c
  utf8.c
  xml.c
  ${CORE_HEADERS}
  )

PREPEND(CORE_SOURCES ${CMARK_SOURCE_PATH}/src ${CORE_SOURCES})

add_library(cmark
  SHARED
  ${CORE_SOURCES}
  )
add_dependencies(cmark cmark-extensions)
target_link_libraries(cmark cmark-extensions)

generate_export_header(cmark
  BASE_NAME cmark)

if(NOT ANDROID)
  add_executable(test-cmark ${CMARK_SOURCE_PATH}/src/main.c)
  add_dependencies(test-cmark cmark)
  target_link_libraries(test-cmark cmark)
endif(NOT ANDROID)

####################################################################################################

# install(FILES
# cmark.h
# cmark_extension_api.h
# ${CMAKE_CURRENT_BINARY_DIR}/cmark_export.h
# ${CMAKE_CURRENT_BINARY_DIR}/cmark_version.h
# DESTINATION include
# )

####################################################################################################
#
# End
#
####################################################################################################
