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

set(PROJ_BASE_URL "https://download.osgeo.org/proj")
set(PROJ_VERSION "9.0.0")
set(PROJ_SOURCE_URL "${PROJ_BASE_URL}/proj-{PROJ_VERSION}.tar.gz")
unset(PROJ_BASE_URL)

set(PROJ_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/local")

# CMake is run by ninja
ExternalProject_Add(proj_build
  DEPENDS sqlite_at

  # URL ${PROJ_SOURCE_URL}
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/proj-source

  PATCH_COMMAND
  # see make-patch.sh
  # Fixme: cannot be run twice
  # patch -p1 -N -i ${CMAKE_CURRENT_SOURCE_DIR}/patch.diff

  CMAKE_ARGS
  # -S${CMAKE_CURRENT_SOURCE_DIR}/proj-source
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
  -DBUILD_APPS=OFF
  -DBUILD_SHARED_LIBS=ON
  -DBUILD_TESTING=OFF
  -DENABLE_CURL=OFF
  -DENABLE_TIFF=OFF
  -DENABLE_IPO=OFF
  -DUSE_CCACHE=OFF
  -DSQLITE3_INCLUDE_DIR=${CMAKE_SOURCE_DIR}/third-parties/sqlite/sqlite-amalgamation/
  -DSQLITE3_LIBRARY=${CMAKE_BINARY_DIR}/third-parties/sqlite/libsqlite_at.so

  -DCMAKE_INSTALL_PREFIX=${PROJ_PREFIX}

  #? -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
  # /!\ output is only dumped when everything is done
  BUILD_COMMAND ninja -v

  # https://stackoverflow.com/questions/37838786/how-to-not-make-install-step-when-building-external-project-with-cmake
  # INSTALL_COMMAND cmake -E echo "Skipping install step."
  # STEP_TARGETS build
  # EXCLUDE_FROM_ALL TRUE
)

# https://cmake.org/cmake/help/latest/module/ExternalProject.html#obtaining-project-properties
# ExternalProject_Get_Property(proj_build INSTALL_DIR)

# see also ${PROJ_PREFIX}/lib64/cmake/proj-targets.cmake
add_library(proj_lib SHARED IMPORTED)
add_dependencies(proj_lib proj_build)
# cf. https://gitlab.kitware.com/cmake/cmake/-/issues/15052
set(PROJ_INCLUDE_DIRECTORY "${PROJ_PREFIX}/include")
set(PROJ_LIB "${PROJ_PREFIX}/${CMAKE_INSTALL_LIBDIR}/libproj.so")
file(MAKE_DIRECTORY ${PROJ_INCLUDE_DIRECTORY}) # else INTERFACE_INCLUDE_DIRECTORIES complain...
if(NOT EXISTS ${PROJ_LIB}) # else overwrite symlink target
  file(WRITE ${PROJ_LIB} "") # else target_link_libraries complain...
endif()
set_target_properties(proj_lib PROPERTIES
  IMPORTED_LOCATION ${PROJ_LIB}
  INTERFACE_INCLUDE_DIRECTORIES ${PROJ_INCLUDE_DIRECTORY}
)
target_link_libraries(proj_lib INTERFACE sqlite_at)

####################################################################################################

if(NOT ANDROID)
  add_executable(test_proj test.c)
  target_link_libraries(test_proj proj_lib)
endif(NOT ANDROID)
