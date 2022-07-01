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

# set(OPENSSL_BASE_URL "")
set(OPENSSL_VERSION "1.1.1")
# set(OPENSSL_SOURCE_URL "${OPENSSL_BASE_URL}/")
# unset(OPENSSL_BASE_URL)

# set(OPENSSL_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/openssl-${OPENSSL_VERSION}-source")
set(OPENSSL_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/openssl-source")

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
