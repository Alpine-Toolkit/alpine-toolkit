/***************************************************************************************************
 **
 ** $QTCARTO_BEGIN_LICENSE:GPL3$
 **
 ** Copyright (C) 2016 Fabrice Salvaire
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

#include "camptocamp/camptocamp_qml.h"

/**************************************************************************************************/

C2cQmlClient::C2cQmlClient(const QString & sqlite_path)
  : QObject(),
    m_client(),
    m_cache(sqlite_path),
    m_login()
{
  m_login = m_cache.login();

  connect(&m_client, SIGNAL(logged()),
          this, SLOT(on_logged()));
  connect(&m_client, SIGNAL(login_failed()),
          this, SLOT(on_loggin_failed()));

  // connect(&m_client, SIGNAL(logged),
  //         this, SLOT(logged));
  // connect(&m_client, SIGNAL(login_failed),
  //         this, SLOT(loggin_failed));
}

const QString &
C2cQmlClient::username() const
{
  return m_login.username();
}

void
C2cQmlClient::set_username(const QString & username)
{
  if (username != m_login.username()) {
    m_login.set_username(username);
    // save_login();
    emit usernameChanged(); // username
  }
}

const QString &
C2cQmlClient::password() const
{
  return m_login.password();
}

void
C2cQmlClient::set_password(const QString & password)
{
  if (password != m_login.password()) {
    m_login.set_password(password);
    // save_login();
    emit passwordChanged(); // password
  }
}

void
C2cQmlClient::save_login()
{
  m_cache.save_login(m_login);
}

void
C2cQmlClient::login()
{
  m_client.login(m_login);
}

void
C2cQmlClient::logout()
{
  // Fixme
}

void
C2cQmlClient::on_logged()
{
  emit loginStatusChanged();
  // emit logged();
}

void
C2cQmlClient::on_loggin_failed()
{
  emit loginStatusChanged();
  // emit on_loggin_failed();
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
