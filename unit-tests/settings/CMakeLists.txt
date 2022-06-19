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

# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

####################################################################################################
#
# Executable
#

foreach(name
    settings_database
    )
  add_executable(test_${name} test_${name}.cpp)
  target_link_libraries(test_${name} Qt6::Test alpine_toolkit)
  add_test(NAME ${name} COMMAND test_${name})
endforeach(name)
