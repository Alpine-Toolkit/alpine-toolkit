/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
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
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "network_database.h"

#include <QSqlError>
#include <QtDebug>

/**************************************************************************************************/

QcNetworkDatabase::QcNetworkDatabase()
{}

QcNetworkDatabase::~QcNetworkDatabase()
{}

void
QcNetworkDatabase::open(const QcDatabaseConnectionData & connection_data)
{
  m_database = QSqlDatabase::addDatabase(driver_name());
  m_database.setHostName(connection_data.host());
  m_database.setPort(connection_data.port());
  m_database.setDatabaseName(connection_data.database());
  m_database.setUserName(connection_data.user());
  m_database.setPassword(connection_data.password());
  if (!m_database.open())
    qWarning() << m_database.lastError().text();
}

bool
QcNetworkDatabase::create_extension(const QString & extension)
{
  // Fixme: PostresSQL
  QString sql_query = "CREATE EXTENSION IF NOT EXISTS " + extension + " WITH SCHEMA public;";
  return execute_query(sql_query);
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
