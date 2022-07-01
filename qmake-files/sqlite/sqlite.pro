####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

# QtCreator: only build the project

# export ANDROID_NDK_ROOT=/opt/android-ndk-r10e
# /opt/Qt/5.9/android_armv7/bin/qmake -o Makefile ../sqlite/sqlite.pro -spec android-g++ CONFIG+=debug CONFIG+=qml_debug

TARGET = qsqlite-at
TEMPLATE = lib

####################################################################################################

CONFIG += plugin
PLUGIN_CLASS_NAME = QSQLiteDriverPlugin
PLUGIN_TYPE = sqldrivers

CONFIG += c++11
# CONFIG += debug

QT -= gui
QT += core-private
QT += sql-private

####################################################################################################

# CONFIG(release, debug|release):DEFINES *= NDEBUG
# See sqlite CMakelist.txt
DEFINES += SQLITE_OMIT_COMPLETE SQLITE_ENABLE_FTS3 SQLITE_ENABLE_FTS3_PARENTHESIS SQLITE_ENABLE_RTREE
linux:!android {
DEFINES += HAVE_POSIX_FALLOCATE=1
}
DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

####################################################################################################

HEADERS += $$PWD/qsql_sqlite_at_p.h
SOURCES += $$PWD/qsql_sqlite_at.cpp $$PWD/smain.cpp

####################################################################################################

linux:!android {
# Qt is compiled on Linux using system SQLite
# It crashes if we compile SQLite source in the plugin.
LIBS += -lsqlite3
}

android {
# SOURCES += $$PWD/sqlite3.c
LIBS += $$PWD/../build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/sqlite/libsqlite.so
}

####################################################################################################

OTHER_FILES += sqlite.json

linux:!android {
# qsqlite-at.path += $$[QT_INSTALL_PLUGINS]/sqldrivers
# INSTALLS += qsqlite-at
}

android {
DESTDIR = $$OUT_PWD/../plugins/sqldrivers
# qsqlite-at.path = $$PWD/plugins-foo/sqldrivers
# INSTALLS += qsqlite-at
}
