# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only

####################################################################################################
#
# QSQLiteATDriverPlugin Plugin
#

# Qt is compiled on Linux using system SQLite
# It crashes if we compile SQLite source in the plugin.

set(CMAKE_AUTOMOC ON)

qt_add_plugin(qsqlite-at
  SHARED
  CLASS_NAME QSQLiteATDriverPlugin
)

target_sources(qsqlite-at
  PRIVATE
    qsql_sqlite_at.cpp
    qsql_sqlite_at_p.h
    smain.cpp
)

target_link_libraries(qsqlite-at
  PRIVATE
    Qt6::Core
    Qt6::CorePrivate
    Qt6::SqlPrivate
    sqlite_at
)

# android
# DESTDIR = $$OUT_PWD/../plugins/sqldrivers
