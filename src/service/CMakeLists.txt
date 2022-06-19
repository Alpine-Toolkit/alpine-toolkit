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
# Include directories
#

include_directories(${CMAKE_SOURCE_DIR}/src)

# include_directories(${CMAKE_CURRENT_BINARY_DIR})

####################################################################################################
#
# Library
#

set(alpine_toolkit_service_files
  main.cpp
  service.cpp
  service_application.cpp
  ${CMAKE_SOURCE_DIR}/src/base/logging/logger.cpp
  )

# add_library(alpine_toolkit_service SHARED ${alpine_toolkit_service_files})
add_executable(alpine-toolkit-service ${alpine_toolkit_service_files})
qt_add_repc_sources(alpine-toolkit-service service.rep)
target_link_libraries(alpine-toolkit-service Qt6::Core  Qt6::Core5Compat Qt6::RemoteObjects)
