// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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

  bool operator==(const C2cLogin & other) const;

private:
  QString m_username;
  QString m_password;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const C2cLogin & login);
#endif

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_LOGIN_H__ */
