####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
#
# This file is part of the Alpine Toolkit software.
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
TARGET = alpine_toolkit_common

####################################################################################################

!include(../common.pri) {
error( "Couldn't find the common.pri file!" )
}

defined(BUILD_AS_SHARED, var) {
CONFIG += shared
}
defined(BUILD_AS_STATIC, var) {
CONFIG += static
}

QT += core
QT += network
QT += widgets

####################################################################################################

# Fixme: config.h # symlink to cmake build ...
INCLUDEPATH += $$PWD/..

include(alpine_toolkit_common.pri)
