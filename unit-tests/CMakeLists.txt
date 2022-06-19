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

include_directories(${CMAKE_SOURCE_DIR}/src/base)
include_directories(${CMAKE_SOURCE_DIR}/src/data_sources)
include_directories(${CMAKE_SOURCE_DIR}/src/utils)

####################################################################################################
#
# Sub directories
#

add_subdirectory(bleaudb)
add_subdirectory(cache)
add_subdirectory(camptocamp)
add_subdirectory(checksum)
add_subdirectory(coordinate)
add_subdirectory(data_structure)
add_subdirectory(documents)
add_subdirectory(ephemeride)
add_subdirectory(full_text_search)
add_subdirectory(geo_data_format)
add_subdirectory(geometry)
add_subdirectory(imports)
add_subdirectory(international_morse_code_engine)
add_subdirectory(map)
add_subdirectory(math)
add_subdirectory(network)
add_subdirectory(openstreetmap)
add_subdirectory(orm)
add_subdirectory(refuge)
add_subdirectory(rrd)
add_subdirectory(settings)
add_subdirectory(sqlite)
add_subdirectory(third_party_license)
