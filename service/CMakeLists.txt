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
# Include directories
#

# include_directories(${CMAKE_CURRENT_BINARY_DIR})

####################################################################################################
#
# Library
#

set(alpine_toolkit_service_files
  main.cpp
  service.cpp
  service_application.cpp
  )

qt5_generate_repc(alpine_toolkit_service_files service.rep SOURCE)
# add_library(alpine_toolkit_service SHARED ${alpine_toolkit_service_files})
add_executable(alpine-toolkit-service ${alpine_toolkit_service_files})
target_link_libraries(alpine-toolkit-service Qt5::Core Qt5::RemoteObjects)

if(ANDROID)
  target_sources(alpine-toolkit-service PRIVATE native.cpp)
endif()

####################################################################################################
#
# End
#
####################################################################################################
