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

add_subdirectory(snowball)

if(ANDROID)
  # build as external project
  add_subdirectory(openssl)
endif(ANDROID)

# build libsqlite-at.so
add_subdirectory(sqlite)

# build as external project
# require sqlite
add_subdirectory(proj)

####################################################################################################

add_subdirectory(geos)

add_subdirectory(libiconv)

# require geos and libiconv
# used by
#  src/base/orm/sqlite_database.cpp:
#  src/application/test.cpp
#  unit-tests/sqlite/test_spatialite.cpp
#add_subdirectory(spatialite) # x86: dependencies

####################################################################################################

# add_subdirectory(cmark) # is available in Qt6

# libspatialindex is unused / last commit in 2019
# cf. third-parties/libspatialindex/test.cpp:
# add_subdirectory(libspatialindex)
