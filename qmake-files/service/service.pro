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

INCLUDEPATH += ../src # alpine-toolkit.h
INCLUDEPATH += .. # for config.h

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

defined(BUILD_AS_SHARED, var) {
LIBS += -L$$OUT_PWD/../src -lalpine_toolkit_common_armeabi-v7a
}
