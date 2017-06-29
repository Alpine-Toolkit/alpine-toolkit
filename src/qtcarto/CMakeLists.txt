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

include_directories(${CMAKE_SOURCE_DIR})

####################################################################################################
#
# Library
#

set(qtcarto_library_files
  coordinate/mercator.cpp
  coordinate/projection.cpp
  coordinate/sexagesimal_angle.cpp
  coordinate/wgs84.cpp
  coordinate/debug_tools.cpp

  # data_structure/pooled_string.cpp
  data_structure/simd.cpp

  geo_data_format/gpx.cpp
  geo_data_format/route.cpp
  geo_data_format/waypoint.cpp
  geo_data_format/xml_reader.cpp
  geo_data_format/wkb.cpp

  # geometry/line.cpp
  # geometry/path.cpp
  # geometry/polygon.cpp
  # geometry/polygon_seidler_triangulation.cpp
  geometry/vector.cpp

  math/interval.cpp
  math/qc_math.cpp
  # math/rational.cpp
  )
add_library(qtcarto SHARED ${qtcarto_library_files})
target_link_libraries(qtcarto
  Qt5::Core
  Qt5::Positioning
  Qt5::Gui
  ${PROJ4_LIBRARIES}
  )

####################################################################################################
#
# End
#
####################################################################################################
