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

add_subdirectory(cmark)
add_subdirectory(snowball)

# Unused / last commit in 2019
# cf. third-parties/libspatialindex/test.cpp:
# add_subdirectory(libspatialindex)

if(ANDROID)
add_subdirectory(sqlite)
add_subdirectory(proj4) # x86: android log
add_subdirectory(geos) # x86: compilation errors ???
add_subdirectory(libiconv)
add_subdirectory(spatialite) # x86: dependencies
endif(ANDROID)
