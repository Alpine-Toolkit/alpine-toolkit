####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

foreach(name
    gpx
    wkb
    )
  add_executable(test_${name} test_${name}.cpp)
  target_link_libraries(test_${name} Qt6::Test qtcarto) # Qt6::Xml
  add_test(NAME ${name} COMMAND test_${name})
endforeach(name)
