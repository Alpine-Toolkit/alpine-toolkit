# -*- CMake -*-

####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
#
# This file is part of the Alpine Toolkit software.
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
#
# Customizable settings
#

# -D <var>:<type>=<value>: Create a cmake cache entry.

# Ipl path
# -D IPL_PATH:PATH=

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

# check cmake version
cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

# To manage policies without increasing the minimum required CMake version
# https://cmake.org/cmake/help/v3.4/manual/cmake-policies.7.html
if(POLICY CMP0990)
  cmake_policy(SET CMP0990 NEW)
endif()

####################################################################################################

# https://cmake.org/cmake/help/latest/command/project.html
project(AlpineToolkit VERSION 0.1.0 LANGUAGES CXX C)
# Set
#   PROJECT_SOURCE_DIR, AlpineToolkit_SOURCE_DIR
#   PROJECT_BINARY_DIR, AlpineToolkit_BINARY_DIR
#   3.21 PROJECT_IS_TOP_LEVEL, AlpineToolkit_IS_TOP_LEVEL
#
#   PROJECT_VERSION, AlpineToolkit_VERSION
#   CMAKE_PROJECT_VERSION
#   PROJECT_VERSION_MAJOR, AlpineToolkit_VERSION_MAJOR
#   PROJECT_VERSION_MINOR, AlpineToolkit_VERSION_MINOR
#   PROJECT_VERSION_PATCH, AlpineToolkit_VERSION_PATCH
#   PROJECT_VERSION_TWEAK, AlpineToolkit_VERSION_TWEAK

####################################################################################################

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/third-parties/cmake" ${CMAKE_MODULE_PATH})

include(alpine_toolkit_functions)

####################################################################################################

option(SANITIZE "Compile using sanitize options" OFF)
option(INSTRUMENT_FUNTIONS "Compile using -finstrument-functions" OFF)

####################################################################################################
#
# Test
#

if(NOT ANDROID)
  enable_testing()
endif(NOT ANDROID)

####################################################################################################
#
# Target Platform
#

if(ANDROID)
 ADD_DEFINITIONS(-DON_ANDROID)
 # ADD_DEFINITIONS(-DON_ANDROID -DANDROID)
endif(ANDROID)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  ADD_DEFINITIONS(-DON_LINUX)
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  ADD_DEFINITIONS(-DON_WINDOWS)
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")

####################################################################################################
#
# Compiler Options
#

if(NOT ANDROID)
  # SET(CMAKE_BUILD_TYPE RELEASE)
  SET(CMAKE_BUILD_TYPE DEBUG)
endif(NOT ANDROID)

set(CMAKE_VERBOSE_MAKEFILE ON)

# Qt 6 requires a compiler supporting C++ version 17 or newer.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# https://gcc.gnu.org/projects/cxx-status.html
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++20" COMPILER_SUPPORTS_CXX20)
CHECK_CXX_COMPILER_FLAG("-std=c++23" COMPILER_SUPPORTS_CXX23)
if(COMPILER_SUPPORTS_CXX23)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
elseif(COMPILER_SUPPORTS_CXX17)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support.")
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  set(CMAKE_CXX_FLAGS_COMMON  "-Wall -DSystemLinux -fdiagnostics-color=auto")
  # https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html#Instrumentation-Options
  # -O0
  # -fstack-protector          Add stack protection to functions that have “alloca” or have a (signed or unsigned) char array with size > 8 (SSP_BUFFER_SIZE)
  # -fstack-protector-strong   To more functions
  # -fstack-protector-all      To all functions
  set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_COMMON} -ggdb -Og -DDEBUG")
  # https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#Optimize-Options
  # $ENV{GCC_OPTIMISATION}
  set(CMAKE_CXX_FLAGS_RELEASE   "${CMAKE_CXX_FLAGS_COMMON} -O3 -march=native")
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")

if(CMAKE_BUILD_TYPE MATCHES "DEBUG")
  if(SANITIZE MATCHES "ON")
    # -fsanitize=thread
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fsanitize=leak -fsanitize=undefined -fstack-protector-all")
    message(STATUS "GCC Sanitize: ${CMAKE_CXX_FLAGS_DEBUG}")
  endif(SANITIZE MATCHES "ON")

  if(INSTRUMENT_FUNTIONS MATCHES "ON")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -finstrument-functions")
    # Fixme: -Wl,-Map=alpine-tookit.map => same name for all targets
    message(STATUS "GCC Profiling: -finstrument-funtions enabled")
  endif(INSTRUMENT_FUNTIONS MATCHES "ON")
endif(CMAKE_BUILD_TYPE MATCHES "DEBUG")

####################################################################################################
#
# Find Qt
#

# https://doc.qt.io/qt-6/cmake-get-started.html

if(NOT ANDROID)
    # Find includes in corresponding build directories
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    # Instruct CMake to run moc automatically when needed.
    set(CMAKE_AUTOMOC ON)
    # Instruct CMake to run rcc automatically when needed.
    set(CMAKE_AUTORCC ON) # https://public.kitware.com/Bug/view.php?id=15074

    find_package(Qt6 REQUIRED COMPONENTS
      Core
      Gui
      Network
      Positioning
      Qml
      Quick
      QuickWidgets
      Widgets
      Sensors
      Sql
      Svg
      Test
      RemoteObjects
      )

    # Not available
    # find_package(Qt6QuickCompiler)

    # only available for Android build
    # find_package(Qt6AndroidExtras REQUIRED)

    # find_package(Qt6Xml REQUIRED)
    # find_package(Qt6WebView REQUIRED)

    # charts
    # quickcontrols
    # svg

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG") # Fixme: right way to do?

    # INCLUDE_DIRECTORIES(${Qt6Core_INCLUDES})
    # ADD_DEFINITIONS(${Qt6Core_DEFINITIONS})
    # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt6Core_EXECUTABLE_COMPILE_FLAGS}")

    # https://doc.qt.io/qt-6/portingguide.html
    # Disable use of C++ API deprecated in Qt 5.15
    #! add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x050F00)
endif(NOT ANDROID)

####################################################################################################
#
# Find Proj4
#

if(NOT ANDROID)
  include(FindProj4)
  if(PROJ4_FOUND)
    # add_definitions(-DWITH_PROJ4)
    INCLUDE_DIRECTORIES(PROJ4_INCLUDE_DIR)
  endif(PROJ4_FOUND)
endif(NOT ANDROID)

####################################################################################################
#
# Find Protobuf
#

if(NOT ANDROID)
  include(FindProtobuf)
  find_package(Protobuf REQUIRED)
  include_directories(${PROTOBUF_INCLUDE_DIR})
endif(NOT ANDROID)

####################################################################################################
#
# Find Zlib
#

if(NOT ANDROID)
  find_package(ZLIB REQUIRED)
  include_directories(${ZLIB_INCLUDE_DIR})
endif(NOT ANDROID)

####################################################################################################

# Fixme: clash with third parties
if(NOT ANDROID)
configure_file(config.h.in config.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
endif(NOT ANDROID)

####################################################################################################
#
# Sub directories
#

# if(ANDROID)
add_subdirectory(third-parties)
# endif(ANDROID)

if(NOT ANDROID)
  include_directories(src)
  include_directories(src/qtcarto)
  include_directories(third-parties/include)

  # add_subdirectory(cpp-test)
  add_subdirectory(service)
  add_subdirectory(src)
  add_subdirectory(unit-tests)
  # add_subdirectory(imports)

  add_subdirectory(map-tools)
  add_subdirectory(imports)
  add_subdirectory(mapviewer)
endif(NOT ANDROID)
