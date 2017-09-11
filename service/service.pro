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

TEMPLATE = lib
TARGET = service

####################################################################################################

!include(../common.pri) {
error( "Couldn't find the common.pri file!" )
}

CONFIG += shared # static

QT += core
QT += remoteobjects
QT += sensors
# QT += positioning
# QT += sql

android {
QT += androidextras
}

####################################################################################################

# INCLUDEPATH +=

# Place before sources
REPC_SOURCE += service.rep

HEADERS += \
  definitions.h \
  service.h \
  service_application.h

SOURCES += \
  main.cpp \
  service.cpp \
  service_application.cpp \

android {
SOURCES += native.cpp
}
