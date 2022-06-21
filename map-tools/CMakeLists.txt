####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

set(CMAKE_AUTOMOC ON)

add_executable(tile-loader tile-loader.cpp)
target_link_libraries(tile-loader
  Qt6::Core
  # alpine-toolkit-common
  qtcarto
)

add_executable(spatialite-test spatialite-test.cpp)
target_link_libraries(spatialite-test Qt6::Sql)
