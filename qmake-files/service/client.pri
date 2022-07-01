# -*- mode: qmake -*-

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
# Service Replica
#

# INCLUDEPATH += service

HEADERS += \
  service/definitions.h \
  service/client.h

SOURCES += \
  service/client.cpp

REPC_REPLICA += service/service.rep
