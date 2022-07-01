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

# prepend(FILES_TO_TRANSLATE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC_FILES})
function(prepend var prefix)
  set(list_var "")
  foreach(f ${ARGN})
    list(APPEND list_var "${prefix}/${f}")
  endforeach(f)
  set(${var} "${list_var}" PARENT_SCOPE)
endfunction(prepend)
