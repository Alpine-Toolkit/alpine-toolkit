####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
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
