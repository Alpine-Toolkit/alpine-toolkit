/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#include "network_database.h"
#include "alpine_toolkit.h"

#include <QSqlError>
#include <QtDebug>

/**************************************************************************************************/

QoNetworkDatabase::QoNetworkDatabase()
{}

QoNetworkDatabase::~QoNetworkDatabase()
{}

void
QoNetworkDatabase::open(const QoDatabaseConnectionData & connection_data)
{
  m_database = QSqlDatabase::addDatabase(driver_name());
  m_database.setHostName(connection_data.host());
  m_database.setPort(connection_data.port());
  m_database.setDatabaseName(connection_data.database());
  m_database.setUserName(connection_data.user());
  m_database.setPassword(connection_data.password());
  if (!m_database.open())
    qWarning() << m_database.lastError().text();

  set_sql_flavour();
}

bool
QoNetworkDatabase::create_extension(const QString & extension)
{
  // Fixme: PostresSQL
  QString sql_query = "CREATE EXTENSION IF NOT EXISTS " + extension + " WITH SCHEMA public;";
  return execute_query(sql_query);
}
