/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
