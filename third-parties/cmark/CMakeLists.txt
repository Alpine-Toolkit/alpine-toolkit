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

cmake_minimum_required(VERSION 3.0)

####################################################################################################

set(CMARK_SOURCE_PATH "cmark.git")

####################################################################################################

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 29)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_GFM 2)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.gfm.${PROJECT_VERSION_GFM})

####################################################################################################

if(${CMAKE_VERSION} VERSION_GREATER "3.3")
    cmake_policy(SET CMP0063 NEW)
endif()

#! include("FindAsan.cmake")
#! include("CheckFileOffsetBits.cmake")
include(GenerateExportHeader)

####################################################################################################

# -fvisibility=hidden
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

# Always compile with warnings
# if(CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter -std=c99 -pedantic")
# endif()

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

####################################################################################################

configure_file(
  ${CMARK_SOURCE_PATH}/src/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/config.h)

configure_file(
  ${CMARK_SOURCE_PATH}/src/cmark-gfm_version.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/cmark-gfm_version.h)

####################################################################################################w

include_directories(${CMARK_SOURCE_PATH}/src)
include_directories(${CMARK_SOURCE_PATH}/extensions)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR}/extensions)

####################################################################################################

set(EXTENSIONS_HEADERS
  )

set(EXTENSIONS_SOURCES
  core-extensions.c
  table.c
  strikethrough.c
  autolink.c
  tagfilter.c
  ext_scanners.c
  ext_scanners.re
  ext_scanners.h
  tasklist.c
  ${EXTENSIONS_HEADERS}
  )

prepend(EXTENSIONS_SOURCES ${CMARK_SOURCE_PATH}/extensions ${EXTENSIONS_SOURCES})

add_library(cmark-extensions STATIC ${EXTENSIONS_SOURCES})

# https://cmake.org/cmake/help/latest/module/GenerateExportHeader.html
generate_export_header(cmark-extensions BASE_NAME cmark-gfm-extensions)

####################################################################################################

set(CORE_HEADERS
  cmark-gfm.h
  cmark-gfm-extension_api.h
  parser.h
  buffer.h
  node.h
  iterator.h
  chunk.h
  references.h
  footnotes.h
  map.h
  utf8.h
  scanners.h
  inlines.h
  houdini.h
  cmark_ctype.h
  render.h
  registry.h
  syntax_extension.h
  plugin.h
  )

set(CORE_SOURCES
  cmark.c
  node.c
  iterator.c
  blocks.c
  inlines.c
  scanners.c
  scanners.re
  utf8.c
  buffer.c
  references.c
  footnotes.c
  map.c
  render.c
  man.c
  xml.c
  html.c
  commonmark.c
  plaintext.c
  latex.c
  houdini_href_e.c
  houdini_html_e.c
  houdini_html_u.c
  cmark_ctype.c
  arena.c
  linked_list.c
  syntax_extension.c
  registry.c
  plugin.c
  ${CORE_HEADERS}
  )

prepend(CORE_SOURCES ${CMARK_SOURCE_PATH}/src ${CORE_SOURCES})

add_library(cmark SHARED ${CORE_SOURCES})
add_dependencies(cmark cmark-extensions)
target_link_libraries(cmark cmark-extensions)

generate_export_header(cmark BASE_NAME cmark-gfm)

####################################################################################################

# if(NOT ANDROID)
#   add_executable(test-cmark ${CMARK_SOURCE_PATH}/src/main.c)
#   add_dependencies(test-cmark cmark)
#   target_link_libraries(test-cmark cmark)
# endif(NOT ANDROID)
