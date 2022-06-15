# Qt SQLite Driver

This directory contains a clone of the Qt SQLite driver so as to be linked with our own SQLite build.

## Build

**See QMake file**

```
# QtCreator: only build the project

# export ANDROID_NDK_ROOT=/opt/android-ndk-r10e
# /opt/Qt/5.9/android_armv7/bin/qmake -o Makefile ../sqlite/sqlite.pro -spec android-g++ CONFIG+=debug CONFIG+=qml_debug

TARGET = qsqlite-at

linux:!android {
# Qt is compiled on Linux using system SQLite
# It crashes if we compile SQLite source in the plugin.
LIBS += -lsqlite3
}

android {
# SOURCES += $$PWD/sqlite3.c
LIBS += $$PWD/../build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/sqlite/libsqlite.so
}

android {
DESTDIR = $$OUT_PWD/../plugins/sqldrivers
}
```

## References

* https://doc.qt.io/qt-6/sql-driver.html#qsqlite
* https://doc.qt.io/qt-6/sql-driver.html#development
* https://doc.qt.io/qt-6/qsqldatabase.html#addDatabase-1

```
QSqlDatabase QSqlDatabase::addDatabase(const QString &type, const QString &connectionName = QLatin1String(defaultConnection))

QSqlDatabase QSqlDatabase::addDatabase(QSqlDriver *driver, const QString &connectionName = QLatin1String(defaultConnection))
```

## Usage in code

```
map-tools/spatialite-test.cpp:  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "db1");
src/qtcarto/database/database.cpp:  m_database = QSqlDatabase::addDatabase(driver_name());
src/qtcarto/database/database.cpp:  m_database = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), sqlite_path);
src/base/orm/sqlite_database.cpp:  m_database = QSqlDatabase::addDatabase(plugin, m_sqlite_path);
src/base/orm/network_database.cpp:  m_database = QSqlDatabase::addDatabase(driver_name());

src/application/test.cpp:  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE-AT");
src/application/test.cpp:  // QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

unit-tests/sqlite/test_spatialite.cpp:  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE-AT");
unit-tests/sqlite/test_spatialite.cpp:  // QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
```

## SQLite Distributed Driver

**How is compiled the SQLite driver for each platform ???**

```
../Qt/6.3.1/gcc_64            /plugins/sqldrivers/libqsqlite.so

../Qt/6.3.1/android_x86       /plugins/sqldrivers/libplugins_sqldrivers_qsqlite_x86.so
../Qt/6.3.1/android_x86_64    /plugins/sqldrivers/libplugins_sqldrivers_qsqlite_x86_64.so
../Qt/6.3.1/android_armv7     /plugins/sqldrivers/libplugins_sqldrivers_qsqlite_armeabi-v7a.so
../Qt/6.3.1/android_arm64_v8a /plugins/sqldrivers/libplugins_sqldrivers_qsqlite_arm64-v8a.so
```
