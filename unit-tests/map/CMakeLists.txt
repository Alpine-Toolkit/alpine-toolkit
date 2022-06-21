####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

# tile_loader

foreach(name
    file_tile_cache
    geoportail_license
    # geoportail_wmts_tile_fetcher
    cache3q
    tile_matrix_set
    # viewport
    # wmts_manager
    # wmts_request_manager
    )
  add_executable(test_${name} test_${name}.cpp)
  target_link_libraries(test_${name} Qt6::Test qtcarto)
  add_test(NAME ${name} COMMAND test_${name})
endforeach(name)
