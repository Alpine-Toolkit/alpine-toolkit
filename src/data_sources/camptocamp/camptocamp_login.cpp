/***************************************************************************************************
 **
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 **
 ***************************************************************************************************/

/**************************************************************************************************/

#include "camptocamp/camptocamp_login.h"
#include "alpine_toolkit.h"

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

  debug.nospace() << QStringLiteral("C2cLogin(");
  debug << login.username();
  debug << QStringLiteral(", ");
  debug << login.password();
  debug << ')';

  return debug;
}
#endif
