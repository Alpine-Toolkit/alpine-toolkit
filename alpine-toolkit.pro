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

TEMPLATE = app
TARGET = alpine-toolkit

####################################################################################################

!include(common.pri) {
error( "Couldn't find the common.pri file!" )
}

debug {
CONFIG += qml_debug
}

CONFIG += qtquickcompiler

QT += core network
QT += gui
QT += qml quick quickcontrols2
QT += sensors
QT += positioning
QT += sql
QT += svg widgets gui # to support SVG
QT += remoteobjects
# QT += charts

####################################################################################################
#
# Sources
#

# Fixme: config.h # symlink to cmake build ...

INCLUDEPATH += $$PWD
INCLUDEPATH += $$OUT_PWD

INCLUDEPATH += src
INCLUDEPATH += src/qtcarto
INCLUDEPATH += imports/QtCarto

include(imports/QtCarto/qt-private.pri)


include(src/alpine-toolkit.pri)
include(service/client.pri)
include(src/main.pri)

####################################################################################################
#
# Linux
#

linux:!android {
HEADERS += \
  src/platform_abstraction/linux_platform.h

SOURCES += \
  src/platform_abstraction/linux_platform.cpp
}

####################################################################################################
#
# Android
#

android {
QT += androidextras

# for rep_service_source.h
INCLUDEPATH += $$OUT_PWD/service

HEADERS += \
  src/platform_abstraction/android_platform.h \
  src/platform_abstraction/android_permission_manager.h

SOURCES += \
  src/platform_abstraction/android_platform.cpp \
  src/platform_abstraction/android_permission_manager.cpp

#  src/platform_abstraction/android_native.cpp \

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

####################################################################################################
#
# Dependencies
#

INCLUDEPATH += $$PWD/third-parties/include # local/cmark/include

defined(BUILD_AS_SHARED, var) {
LIBS += -L$$OUT_PWD/src -lalpine_toolkit_common_armeabi-v7a
LIBS += -L$$OUT_PWD/src/qtcarto -lqtcarto_armeabi-v7a
}

linux:!android {
LIBS += -L$$PWD/third-parties/local/cmark/lib -lcmark
LIBS += -L$$PWD/build-cmake/third-parties/snowball -lsnowball
LIBS += -lproj
}

android {
ANDROID_EXTRA_PLUGINS += $$OUT_PWD/plugins

LIBS += -L$$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/cmark -lcmark
LIBS += -L$$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/snowball -lsnowball

INCLUDEPATH += $$PWD/third-parties/proj4/proj.4.git/src
LIBS += -L$$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/proj4 -lqtcarto_proj4

ANDROID_EXTRA_LIBS += $$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/cmark/libcmark.so
ANDROID_EXTRA_LIBS += $$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/snowball/libsnowball.so
ANDROID_EXTRA_LIBS += $$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/sqlite/libsqlite.so
ANDROID_EXTRA_LIBS += $$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/proj4/libqtcarto_proj4.so

contains(ANDROID_TARGET_ARCH, armeabi-v7a) {
ANDROID_EXTRA_LIBS += $$PWD/third-parties/openssl-1.0.2h/libcrypto.so
ANDROID_EXTRA_LIBS += $$PWD/third-parties/openssl-1.0.2h/libssl.so
}

#! ANDROID_EXTRA_LIBS += $$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/geos/libgeos.so
#! ANDROID_EXTRA_LIBS += $$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/spatialite/libspatialite.so

# $$PWD/build-cmake-android/third-parties/libiconv/libiconv.so
# /opt/Qt-dev-5.7.0-android/lib/libqtcarto.o
}

####################################################################################################
#
# Resources
#

RESOURCES += ressources/alpine-toolkit.qrc

####################################################################################################
#
# Translations
#

lupdate_only{
SOURCES += \
  pages/*.qml
}

TRANSLATIONS = ressources/translations/alpine-toolkit.fr_FR.ts
# \ alpine-toolkit-en.ts

####################################################################################################
#
# Dist Target
#

# Fixme: Complete
DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/src/org/alpine_toolkit/AlpineToolkitActivity.java \
    android/src/org/alpine_toolkit/AlpineToolkitService.java
