/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine Toolkit software.
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

#include "database_connection.h"
#include "alpine_toolkit.h"

#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

QoDatabaseConnectionData::QoDatabaseConnectionData()
  : m_host(),
    m_port(),
    m_database(),
    m_user(),
    m_password()
{}

QoDatabaseConnectionData::QoDatabaseConnectionData(const QoDatabaseConnectionData & other)
  : m_host(other.m_host),
    m_port(other.m_port),
    m_database(other.m_database),
    m_user(other.m_user),
    m_password(other.m_password)
{}

QoDatabaseConnectionData::~QoDatabaseConnectionData()
{}

QoDatabaseConnectionData &
QoDatabaseConnectionData::operator=(const QoDatabaseConnectionData & other)
{
  if (this != &other) {
    m_host = other.m_host;
    m_port = other.m_port;
    m_database = other.m_database;
    m_user = other.m_user;
    m_password = other.m_password;
  }

  return *this;
}

bool
QoDatabaseConnectionData::operator==(const QoDatabaseConnectionData & other)
{
  if (m_host != other.m_host)
    return false;
  if (m_port != other.m_port)
    return false;
  if (m_database != other.m_database)
    return false;
  if (m_user != other.m_user)
    return false;
  if (m_password != other.m_password)
    return false;

  return true;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const QoDatabaseConnectionData & obj)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace() << QStringLiteral("QoDatabaseConnectionData(");
  debug << obj.host();
  debug << QStringLiteral(", ");
  debug << obj.port();
  debug << QStringLiteral(", ");
  debug << obj.database();
  debug << QStringLiteral(", ");
  debug << obj.user();
  debug << QStringLiteral(", ");
  debug << obj.password();
  debug << ')';

  return debug;
}
#endif

// QC_END_NAMESPACE
