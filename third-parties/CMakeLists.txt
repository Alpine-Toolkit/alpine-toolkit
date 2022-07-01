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
