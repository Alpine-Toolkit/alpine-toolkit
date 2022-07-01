// -*- mode: c++ -*-
/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
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
