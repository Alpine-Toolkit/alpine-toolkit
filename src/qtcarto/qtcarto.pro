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
TARGET = qtcarto
# TARGET = $$qtLibraryTarget($$TARGET) # for windows ?

####################################################################################################

!include(../../common.pri) {
  error( "Couldn't find the common.pri file!" )
}

defined(BUILD_AS_SHARED, var) {
CONFIG += shared
}
defined(BUILD_AS_STATIC, var) {
CONFIG += static
}

QT += core
QT += gui
QT += network
QT += positioning
QT += qml quick
QT += sql

####################################################################################################

DEFINES += QTCARTO_LIBRARY

####################################################################################################

include(qtcarto.pri)

####################################################################################################

include(../../imports/QtCarto/qt-private.pri)

VPATH = ../../imports/QtCarto
HEADERS += \
  declarative_map_item.h \
  geo_coordinate_animation.h \
  map_gesture_area.h \
  plugin_data.h

SOURCES += \
  declarative_map_item.cpp \
  geo_coordinate_animation.cpp \
  map_gesture_area.cpp \
  plugin_data.cpp

####################################################################################################

defined(BUILD_AS_SHARED, var) {
# Link to alpine_toolkit_common for configuration/configuration.h
INCLUDEPATH += $$PWD/..
LIBS += -L$$OUT_PWD/.. -lalpine_toolkit_common
}

# Link to PROJ4
# DEFINES += WITH_PROJ4
linux:!android {
LIBS += -lproj
}
android {
INCLUDEPATH += $$PWD/../../third-parties/proj4/proj.4.git/src
LIBS += -L$$PWD/../../build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/proj4 -lqtcarto_proj4
}
