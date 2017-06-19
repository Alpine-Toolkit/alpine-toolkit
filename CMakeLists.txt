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

project(AlpineToolkit)

####################################################################################################

# check cmake version
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

if(POLICY CMP0990)
  cmake_policy(SET CMP0990 NEW)
endif()

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
# Version
#

set(ALPINE_TOOLKIT_VERSION_MAJOR 1)
set(ALPINE_TOOLKIT_VERSION_MINOR 0)
set(ALPINE_TOOLKIT_VERSION_PATCH 0)

set(ALPINE_TOOLKIT_VERSION ${ALPINE_TOOLKIT_VERSION_MAJOR}.${ALPINE_TOOLKIT_VERSION_MINOR}.${ALPINE_TOOLKIT_VERSION_PATCH})

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

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  set(CMAKE_CXX_FLAGS_COMMON  "-Wall -DSystemLinux -fdiagnostics-color=auto")
  # https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html#Instrumentation-Options
  # -O0
  set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_COMMON} -g -Og  -DDEBUG")
  # https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#Optimize-Options
  # $ENV{GCC_OPTIMISATION}
  set(CMAKE_CXX_FLAGS_RELEASE   "${CMAKE_CXX_FLAGS_COMMON} -O3 -march=native")
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")

if(CMAKE_BUILD_TYPE MATCHES "DEBUG")
  if(SANITIZE MATCHES "ON")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fsanitize=leak -fsanitize=undefined")
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

if(NOT ANDROID)
    # Find includes in corresponding build directories
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    # Instruct CMake to run moc automatically when needed.
    set(CMAKE_AUTOMOC ON)
    # Instruct CMake to run rcc automatically when needed.
    set(CMAKE_AUTORCC ON) # https://public.kitware.com/Bug/view.php?id=15074

    find_package(Qt5Core REQUIRED)
    find_package(Qt5Gui REQUIRED)
    find_package(Qt5Network REQUIRED)
    find_package(Qt5Positioning REQUIRED)
    find_package(Qt5Qml REQUIRED)
    find_package(Qt5Quick REQUIRED) # QtQuickWidgets
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5Sensors REQUIRED)
    find_package(Qt5Sql REQUIRED)
    find_package(Qt5Test REQUIRED)
    find_package(Qt5RemoteObjects REQUIRED)

    # Not available
    # find_package(Qt5QuickCompiler)

    # only available for Android build
    # find_package(Qt5AndroidExtras REQUIRED)

    # find_package(Qt5Xml REQUIRED)
    # find_package(Qt5WebView REQUIRED)

    # charts
    # quickcontrols
    # svg

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG") # Fixme: right way to do?

    # INCLUDE_DIRECTORIES(${Qt5Core_INCLUDES})
    # ADD_DEFINITIONS(${Qt5Core_DEFINITIONS})
    # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
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
  include_directories(third-parties/include)

  # add_subdirectory(cpp-test)
  add_subdirectory(service)
  add_subdirectory(src)
  add_subdirectory(unit-tests)
  # add_subdirectory(imports)
endif(NOT ANDROID)

####################################################################################################
#
# End
#
####################################################################################################
