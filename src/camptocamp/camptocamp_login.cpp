/***************************************************************************************************
 **
 ** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
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
 ** $ALPINE_TOOLKIT_END_LICENSE$
 **
 ***************************************************************************************************/

/**************************************************************************************************/

#include "camptocamp/camptocamp_login.h"

#include <QtDebug>

/**************************************************************************************************/

C2cLogin::C2cLogin()
  : m_username(),
    m_password()
{}

C2cLogin::C2cLogin(const QString & username, const QString & password)
  : m_username(username),
    m_password(password)
{}

C2cLogin::C2cLogin(const C2cLogin & other)
  : m_username(other.m_username),
    m_password(other.m_password)
{}

C2cLogin::~C2cLogin()
{}

C2cLogin &
C2cLogin::operator=(const C2cLogin & other)
{
  if (this != &other) {
    m_username = other.m_username;
    m_password = other.m_password;
  }

  return *this;
}

bool
C2cLogin::operator==(const C2cLogin & other) const
{
  return m_username == other.m_username and m_password == other.m_password;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const C2cLogin & login)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace() << QLatin1Literal("C2cLogin(");
  debug << login.username();
  debug << QLatin1Literal(", ");
  debug << login.password();
  debug << ')';

  return debug;
}
#endif
