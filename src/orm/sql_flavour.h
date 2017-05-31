// -*- mode: c++ -*-
/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the QtCarto library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $QTCARTO_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef __SQL_FLAVOUR_H__
#define __SQL_FLAVOUR_H__

/**************************************************************************************************/

/* Qt Supported Databases http://doc.qt.io/qt-5/sql-driver.html#supported-databases
 * QDB2	IBM DB2 (version 7.1 and above)
 * QIBASE	Borland InterBase
 * QMYSQL	MySQL
 * QOCI	Oracle Call Interface Driver
 * QODBC	Open Database Connectivity (ODBC) - Microsoft SQL Server and other ODBC-compliant databases
 * QPSQL	PostgreSQL (versions 7.3 and above)
 * QSQLITE2	SQLite version 2
 * QSQLITE    SQLite version 3
 */

enum class SqlFlavour {
  ANSI,
  SQLite,
  MySQL,
  MariaDB,
  PostgreSQL,
  SQL_Server,
  Oracle,
  DB2
};

/**************************************************************************************************/

#endif /* __SQL_FLAVOUR_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
