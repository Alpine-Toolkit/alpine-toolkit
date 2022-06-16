# -*- CMake -*-

####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2022 Fabrice Salvaire
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

# set(OPENSSL_BASE_URL "")
set(OPENSSL_VERSION "1.1.1")
# set(OPENSSL_SOURCE_URL "${OPENSSL_BASE_URL}/")
# unset(OPENSSL_BASE_URL)

set(OPENSSL_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/openssl-${OPENSSL_VERSION}.git")

set(PATH1 "${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin")
set(PATH2 "${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin")
set(ENV_PATH "${PATH1}:${PATH2}:$ENV{PATH}")

if (${ANDROID_ABI} STREQUAL "armeabi-v7a")
  set(ARCH "android-arm")
elseif (${ANDROID_ABI} STREQUAL "x86")
  set(ARCH "android-x86")
endif()

# Sets environment variables
#   it affects only the current CMake process
#   https://cmake.org/cmake/help/latest/command/set.html
# Note: don't work, workaround use cmake -E env variable=value command
#  set(ENV{PATH} ${ENV_PATH})
#  set(ENV{ANDROID_NDK_HOME} ${ANDROID_NDK})

# CMake is run by ninja
ExternalProject_Add(openssl
  # URL ${OPENSSL_SOURCE_URL}
  SOURCE_DIR ${OPENSSL_SOURCE_DIR}

  CONFIGURE_COMMAND
  ${CMAKE_COMMAND} -E
  env PATH=${ENV_PATH} ANDROID_NDK_HOME=${ANDROID_NDK}
  ${OPENSSL_SOURCE_DIR}/Configure shared ${ARCH} -D__ANDROID_API__=${ANDROID_NATIVE_API_LEVEL} --prefix=${CMAKE_CURRENT_BINARY_DIR}/local/

  BUILD_COMMAND
  ${CMAKE_COMMAND} -E
  env PATH=${ENV_PATH} ANDROID_NDK_HOME=${ANDROID_NDK}
  make SHLIB_VERSION_NUMBER= SHLIB_EXT=_1_1.so

  INSTALL_COMMAND
  ${CMAKE_COMMAND} -E
  env PATH=${ENV_PATH} ANDROID_NDK_HOME=${ANDROID_NDK}
  make install SHLIB_VERSION_NUMBER= SHLIB_EXT=_1_1.so

  # https://stackoverflow.com/questions/37838786/how-to-not-make-install-step-when-building-external-project-with-cmake
  # INSTALL_COMMAND cmake -E echo "Skipping install step."
  # STEP_TARGETS build
  # EXCLUDE_FROM_ALL TRUE
)

# add_dependencies(... openssl-build)
