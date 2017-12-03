// -*- mode: c++ -*-

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

#ifndef __DATABASE_CONNECTION_H__
#define __DATABASE_CONNECTION_H__

/**************************************************************************************************/

#include <QString>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/*
struct QoDatabaseConnectionData
{
  QString host;
  int port;
  QString database;
  QString user;
  QString password;
};
*/

class QoDatabaseConnectionData
{
public:
  QoDatabaseConnectionData();
  QoDatabaseConnectionData(const QoDatabaseConnectionData & other);
  ~QoDatabaseConnectionData();

  QoDatabaseConnectionData & operator=(const QoDatabaseConnectionData & other);

  bool operator==(const QoDatabaseConnectionData & other);

  // Getter/Setter

  const QString & host() const { return m_host; }
  void set_host(const QString & value) { m_host = value; }

  int port() const { return m_port; }
  void set_port(int value) { m_port = value; }

  const QString & database() const { return m_database; }
  void set_database(const QString & value) { m_database = value; }

  const QString & user() const { return m_user; }
  void set_user(const QString & value) { m_user = value; }

  const QString & password() const { return m_password; }
  void set_password(const QString & value) { m_password = value; }

private:
  QString m_host;;
  int m_port;;
  QString m_database;;
  QString m_user;;
  QString m_password;;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const QoDatabaseConnectionData & obj);
#endif

// QC_END_NAMESPACE

#endif /* __DATABASE_CONNECTION_H__ */
