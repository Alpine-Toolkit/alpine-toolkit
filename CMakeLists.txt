# -*- CMake -*-

####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################
#
# Customizable settings
#

# -D <var>:<type>=<value>: Create a cmake cache entry.

# Install path prefix, prepended onto install directories.
# -D CMAKE_INSTALL_PREFIX:PATH=/usr/local/stow/bar

# Choose the type of build, options are: None(CMAKE_CXX_FLAGS or
# CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.
# -D CMAKE_BUILD_TYPE:STRING=Debug

# If this value is on, makefiles will be generated without the
# .SILENT directive, and all commands will be echoed to the console
# during the make.  This is useful for debugging only.
# -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON

####################################################################################################
#
# Platform Notes
#
#   ANDROID is set to 1 when the target system CMAKE_SYSTEM_NAME is Android
#   see also https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html#cross-compiling-for-android
#
####################################################################################################

####################################################################################################

# check cmake version
cmake_minimum_required(VERSION 3.23.0 FATAL_ERROR)

# To manage policies without increasing the minimum required CMake version
#   https://cmake.org/cmake/help/latest/manual/cmake-policies.7.html
if(POLICY CMP0990)
  cmake_policy(SET CMP0990 NEW)
endif()

# for project VERSION
cmake_policy(SET CMP0048 NEW)

####################################################################################################

# https://cmake.org/cmake/help/latest/command/project.html
project(
  ALPINE_TOOLKIT
  VERSION 0.1.0
  DESCRIPTION "Apline Toolkit Application"
  HOMEPAGE_URL "https://github.com/Alpine-Toolkit/alpine-toolkit"
  LANGUAGES CXX C
  )

# Set
#   PROJECT_SOURCE_DIR      ALPINE_TOOLKIT_SOURCE_DIR
#   PROJECT_BINARY_DIR      ALPINE_TOOLKIT_BINARY_DIR
#   PROJECT_IS_TOP_LEVEL    ALPINE_TOOLKIT_IS_TOP_LEVEL
#
#   PROJECT_VERSION         ALPINE_TOOLKIT_VERSION
#   PROJECT_VERSION_MAJOR   ALPINE_TOOLKIT_VERSION_MAJOR
#   PROJECT_VERSION_MINOR   ALPINE_TOOLKIT_VERSION_MINOR
#   PROJECT_VERSION_PATCH   ALPINE_TOOLKIT_VERSION_PATCH
#   PROJECT_VERSION_TWEAK   ALPINE_TOOLKIT_VERSION_TWEAK
#   CMAKE_PROJECT_VERSION

####################################################################################################

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/third-parties/cmake" ${CMAKE_MODULE_PATH})

# Load ExternalProject_Add function
include(ExternalProject)

# Load functions
#  prepend(FILES_TO_TRANSLATE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC_FILES})
include(alpine_toolkit_functions)

####################################################################################################
#
# Options
#

# Provide an option that the user can optionally select
option(SANITIZE "Compile using sanitize options" OFF)
option(INSTRUMENT_FUNTIONS "Compile using -finstrument-functions" OFF)

####################################################################################################
#
# Target Platform
#

if(ANDROID)
  message("Build for Android")
  add_compile_definitions(ON_ANDROID)
endif(ANDROID)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  message("Build for Linux")
  set(LINUX true)
  add_compile_definitions(ON_LINUX)
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  message("Build for Windows")
  add_compile_definitions(ON_WINDOWS)
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")

####################################################################################################

# https://github.com/ninja-build/ninja/issues/900 — How to make build verbose by default
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)

# https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#property-origin-debugging
# set(CMAKE_DEBUG_TARGET_PROPERTIES
#   INCLUDE_DIRECTORIES
#   COMPILE_DEFINITIONS
#   POSITION_INDEPENDENT_CODE
#   CONTAINER_SIZE_REQUIRED
#   LIB_VERSION
# )

if(NOT ANDROID)
  # Enable testing for current directory and below
  #   https://cmake.org/cmake/help/latest/command/enable_testing.html
  enable_testing()
endif(NOT ANDROID)

####################################################################################################
#
# Global Compiler Options
#
#   https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_FLAGS.html
#
#   https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
#
#   https://clang.llvm.org/docs/CommandGuide/clang.html
#   https://clang.llvm.org/docs/DiagnosticsReference.html

# Qt 6 requires a compiler supporting C++ version 17 or newer.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# https://gcc.gnu.org/projects/cxx-status.html
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++17" COMPILER_SUPPORTS_CXX17)
# check_cxx_compiler_flag("-std=c++20" COMPILER_SUPPORTS_CXX20)
# check_cxx_compiler_flag("-std=c++23" COMPILER_SUPPORTS_CXX23)
# if(COMPILER_SUPPORTS_CXX23)
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
# elseif(COMPILER_SUPPORTS_CXX17)
if(COMPILER_SUPPORTS_CXX17)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support.")
endif()


# For Linux using GCC
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  set(CMAKE_CXX_FLAGS_COMMON  "-Wall -fdiagnostics-color=auto")
  # https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html#Instrumentation-Options
  # -O0
  # -fstack-protector          Add stack protection to functions that have “alloca” or have a (signed or unsigned) char array with size > 8 (SSP_BUFFER_SIZE)
  # -fstack-protector-strong   To more functions
  # -fstack-protector-all      To all functions
  set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_COMMON} -ggdb -O0")
  # https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#Optimize-Options
  # $ENV{GCC_OPTIMISATION}
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_COMMON} -O3 -march=native")
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")

# For Android using Clang
if(CMAKE_SYSTEM_NAME MATCHES "Android")
  set(CMAKE_CXX_FLAGS_COMMON  "-Wall -fcolor-diagnostics")
  set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_COMMON} -g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_COMMON} -O3")
endif(CMAKE_SYSTEM_NAME MATCHES "Android")


# For Windows
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")


# For DEBUG build
if(CMAKE_BUILD_TYPE MATCHES "DEBUG")
  # Fixme: could clash
  add_compile_definitions(AT_DEBUG)

  if(SANITIZE MATCHES "ON")
    # -fsanitize=thread
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fsanitize=leak -fsanitize=undefined -fstack-protector-all")
    message(STATUS "GCC Sanitize: ${CMAKE_CXX_FLAGS_DEBUG}")
  endif(SANITIZE MATCHES "ON")

  if(INSTRUMENT_FUNTIONS MATCHES "ON")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -finstrument-functions")
    # Fixme: -Wl,-Map=alpine-tookit.map => same name for all targets
    message(STATUS "GCC Profiling: -finstrument-funtions enabled")
  endif(INSTRUMENT_FUNTIONS MATCHES "ON")
endif(CMAKE_BUILD_TYPE MATCHES "DEBUG")

####################################################################################################
#
# Find Qt
#

# https://doc.qt.io/qt-6/cmake-get-started.html

# Find includes in corresponding build directories
#! set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS
  Core
  Core5Compat
  Gui
  LinguistTools
  Network
  Positioning
  Qml
  Quick
  QuickWidgets
  RemoteObjects
  Sensors
  ShaderTools
  Sql
  Svg
  Test
  Widgets
)

# only available for Android build
# find_package(Qt6AndroidExtras REQUIRED)

# include_directories(${Qt6Core_INCLUDES})
# add_definitions(${Qt6Core_DEFINITIONS})
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt6Core_EXECUTABLE_COMPILE_FLAGS}")

####################################################################################################
#
# Find Proj4
#

# if(NOT ANDROID)
#   include(FindProj4)
#   if(PROJ4_FOUND)
#     # add_compile_definitions(WITH_PROJ4)
#     include_directories(PROJ4_INCLUDE_DIR)
#   endif(PROJ4_FOUND)
# endif(NOT ANDROID)

####################################################################################################
#
# Find Protobuf
#

if(NOT ANDROID)
  include(FindProtobuf)
  find_package(Protobuf REQUIRED)
  #! include_directories(${PROTOBUF_INCLUDE_DIR})
endif()

####################################################################################################
#
# Find Zlib
#

if(NOT ANDROID)
  find_package(ZLIB REQUIRED)
  #! include_directories(${ZLIB_INCLUDE_DIR})
endif()

####################################################################################################

configure_file(config.h.in config.h @ONLY)
#! include_directories(${CMAKE_CURRENT_BINARY_DIR})

####################################################################################################
#
# Sub directories
#

add_subdirectory(third-parties)
add_subdirectory(sqlite-driver)

add_subdirectory(src)

if(NOT ANDROID)
  add_subdirectory(unit-tests)

  add_subdirectory(map-tools)
  #! add_subdirectory(mapviewer)
endif()

# add_subdirectory(cpp-test)
