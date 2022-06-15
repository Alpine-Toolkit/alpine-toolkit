QT_SOURCE='/home/scratch/sources/qt-sources/qt6'

# .../qtbase/src/plugins/sqldrivers/sqlite/
#   CMakeLists.txt
#   README
#   configure.cmake
#   qt_cmdline.cmake
#
# .../qtbase/src/plugins/sqldrivers/sqlite/
#   CMakeLists.txt
#   README
#   qsql_sqlite.cpp
#   qsql_sqlite_p.h
#   smain.cpp
#   sqlite.json

cp -r ${QT_SOURCE}/qtbase/src/plugins/sqldrivers/sqlite/* .

mv sqlite.json sqlite-at.json
mv qsql_sqlite_p.h qsql_sqlite_at_p.h
mv qsql_sqlite.cpp qsql_sqlite_at.cpp

sed -e 's/sqlite.json/sqlite-at.json/' -i smain.cpp
sed -e 's/SQLITE/SQLITE-AT/' -i sqlite-at.json
sed -e 's/SQLITE/SQLITE-AT/' -i smain.cpp
sed -e 's/QSQLite/QSQLiteAT/g' -i smain.cpp
sed -e 's/QSQLite/QSQLiteAT/g' -i qsql_sqlite_at.cpp
sed -e 's/QSQLite/QSQLiteAT/g' -i qsql_sqlite_at_p.h
sed -e 's/QSQL_SQLITE_H/QSQL_SQLITE_AT_H/g' -i qsql_sqlite_at_p.h
sed -e 's/qsql_sqlite_p/qsql_sqlite_at_p/g' -i qsql_sqlite_at.cpp
sed -e 's/qsql_sqlite_p/qsql_sqlite_at_p/g' -i smain.cpp
