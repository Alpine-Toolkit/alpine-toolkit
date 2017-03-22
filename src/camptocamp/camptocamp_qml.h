// -*- mode: c++ -*-

/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the QtCarto library.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __CAMPTOCAMP_QML_H__
#define __CAMPTOCAMP_QML_H__

/**************************************************************************************************/

#include "camptocamp/camptocamp_client.h"
#include "camptocamp/camptocamp_cache.h"

/**************************************************************************************************/

class C2cQmlClient :public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool logged READ is_logged NOTIFY loginStatusChanged)
  Q_PROPERTY(QString username READ username WRITE set_username NOTIFY usernameChanged)
  Q_PROPERTY(QString password READ password WRITE set_password NOTIFY passwordChanged)

public:
  C2cQmlClient(const QString & sqlite_path);

  Q_INVOKABLE void save_login();
  Q_INVOKABLE void login();
  Q_INVOKABLE void logout();

private:
  const QString & username() const;
  void set_username(const QString & username);

  const QString & password() const;
  void set_password(const QString & password);

  bool is_logged() const {
    return m_client.is_logged();
  }

signals:
  void usernameChanged(); // const QString & username
  void passwordChanged(); // const QString & password
  void loginStatusChanged();
  // void logged();
  // void login_failed();

private slots:
  void on_logged();
  void on_loggin_failed();

private:
  C2cClient m_client;
  C2cCache m_cache;
  C2cLogin m_login;
};

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_QML_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
