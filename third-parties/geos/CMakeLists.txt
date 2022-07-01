# -*- CMake -*-

####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

set(GEOS_BASE_URL "http://download.osgeo.org/geos")
set(GEOS_VERSION "3.10.301486")
set(GEOS_SOURCE_URL "${GEOS_BASE_URL}/geos-{GEOS_VERSION}.tar.bz2")
unset(GEOS_BASE_URL)

set(GEOS_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/local")

# CMake is run by ninja
ExternalProject_Add(geos_project
  DEPENDS sqlite_at

  # URL ${GEOS_SOURCE_URL}
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/geos-source

  CMAKE_ARGS
  # -S${CMAKE_CURRENT_SOURCE_DIR}/geos-source
  # -B${CMAKE_CURRENT_SOURCE_DIR}/build
  # -GNinja
  -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
  -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
  -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
  -DCMAKE_TOOLCHAIN_FILE:FILEPATH=${CMAKE_TOOLCHAIN_FILE}
  -DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
  -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
  -DANDROID_NDK:PATH=${ANDROID_NDK}
  -DANDROID_SDK_ROOT:PATH=${ANDROID_SDK}
  -DANDROID_ABI:STRING=${ANDROID_ABI}
  -DANDROID_NATIVE_API_LEVEL:STRING=${ANDROID_NATIVE_API_LEVEL}
  -DANDROID_STL:STRING=${ANDROID_STL}

  -DCMAKE_INSTALL_PREFIX=${GEOS_PREFIX}

  #? -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
  # /!\ output is only dumped when everything is done
  BUILD_COMMAND ninja -v

  # https://stackoverflow.com/questions/37838786/how-to-not-make-install-step-when-building-external-project-with-cmake
  # INSTALL_COMMAND cmake -E echo "Skipping install step."
  # STEP_TARGETS build
  # EXCLUDE_FROM_ALL TRUE
)

# add_dependencies(... geos-build)

# https://cmake.org/cmake/help/latest/module/ExternalProject.html#obtaining-project-properties
# ExternalProject_Get_property(geos_project SOURCE_DIR)

# see also ${GEOS_PREFIX}/lib64/cmake/geos-targets.cmake
add_library(geos_lib SHARED IMPORTED)
set_target_properties(geos_lib PROPERTIES
  IMPORTED_LOCATION "${GEOS_PREFIX}/${CMAKE_INSTALL_LIBDIR}/libgeos.so"
  INTERFACE_INCLUDE_DIRECTORIES "${GEOS_PREFIX}/include"
)
