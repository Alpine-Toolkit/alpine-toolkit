cp -r /home/scratch/sources/qt5/qt5-git/qtbase/src/plugins/sqldrivers/sqlite/* .
cp -r /home/scratch/sources/qt5/qt5-git/qtbase/src/plugins/sqldrivers/qsqldriverbase.pri .
cp -r /home/scratch/sources/qt5/qt5-git/qtbase/src/plugins/sqldrivers/sqldrivers.pro .
mv sqlite.json sqlite-at.json
mv sqlite.pro sqlite-at.pro
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
