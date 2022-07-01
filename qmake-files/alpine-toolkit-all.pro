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
# Alpine Toolkit Top Qmake
#
####################################################################################################

####################################################################################################

TEMPLATE = subdirs

!include(common.pri) {
  error( "Couldn't find the common.pri file!" )
}

SUBDIRS = \
  sqlite \
  src/alpine_toolkit_common.pro \
  service \
  src/qtcarto/qtcarto.pro \
  alpine-toolkit.pro

qtcarto.depends = alpine_toolkit_common
service.depends = alpine_toolkit_common

alpine-toolkit.depends = sqlite
alpine-toolkit.depends = service
alpine-toolkit.depends = alpine_toolkit_common
alpine-toolkit.depends = qtcarto
