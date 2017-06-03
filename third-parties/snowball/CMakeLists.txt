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
# Comment unwanted modules in libstemmer/modules.txt
# Run make in snowball.git
#
####################################################################################################

####################################################################################################

set(SNOWBALL_SOURCE_PATH "snowball.git")

####################################################################################################

include_directories(${SNOWBALL_SOURCE_PATH}/src_c)
include_directories(${SNOWBALL_SOURCE_PATH}/libstemmer)
include_directories(${SNOWBALL_SOURCE_PATH}/runtime)

set(runtime_sources
  api.c
  utilities.c
  )
prepend(runtime_sources ${SNOWBALL_SOURCE_PATH}/runtime ${runtime_sources})

set (module_sources
  stem_UTF_8_english.c
  stem_UTF_8_french.c
  stem_UTF_8_german2.c
  stem_UTF_8_german.c
  stem_UTF_8_italian.c
  stem_UTF_8_portuguese.c
  stem_UTF_8_spanish.c
  )
prepend(module_sources ${SNOWBALL_SOURCE_PATH}/src_c ${module_sources})

add_library(snowball SHARED
  ${SNOWBALL_SOURCE_PATH}/libstemmer/libstemmer.c
  ${runtime_sources}
  ${module_sources})

####################################################################################################
#
# End
#
####################################################################################################
