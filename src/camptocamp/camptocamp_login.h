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

#ifndef __CAMPTOCAMP_LOGIN_H__
#define __CAMPTOCAMP_LOGIN_H__

/**************************************************************************************************/

#include <QString>
#include <QtDebug>

/**************************************************************************************************/

class C2cLogin {
public:
  C2cLogin();
  C2cLogin(const QString & username, const QString & password);
  C2cLogin(const C2cLogin & other);
  ~C2cLogin();

  C2cLogin & operator=(const C2cLogin & other);

  const QString & username() const { return m_username; }
  void set_username(const QString & username) { m_username = username; }

  const QString & password() const { return m_password; }
  void set_password(const QString & password) { m_password = password; }

  explicit operator bool() const { return not m_username.isEmpty(); }

private:
  QString m_username;
  QString m_password;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const C2cLogin & login);
#endif

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_LOGIN_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
