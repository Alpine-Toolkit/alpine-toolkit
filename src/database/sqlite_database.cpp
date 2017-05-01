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

#include "sqlite_database.h"

#include <QFile>
#include <QSqlError>
#include <QtDebug>

/**************************************************************************************************/

QcSqliteDatabase::QcSqliteDatabase()
{}

QcSqliteDatabase::~QcSqliteDatabase()
{}

bool
QcSqliteDatabase::open(const QString & sqlite_path)
{
  bool created = not QFile(sqlite_path).exists();

  // Set the connection name to sqlite_path
  m_database = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"), sqlite_path);
  m_database.setDatabaseName(sqlite_path);
  if (not m_database.open())
    qWarning() << m_database.lastError().text();

  return created;
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
