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

#ifndef __CAMPTOCAMP_LOGIN_DATA_H__
#define __CAMPTOCAMP_LOGIN_DATA_H__

/**************************************************************************************************/

#include <QDateTime>
#include <QJsonDocument>
#include <QSharedPointer>
#include <QString>

/**************************************************************************************************/

typedef QSharedPointer<QJsonDocument> QJsonDocumentPtr;

/**************************************************************************************************/

class C2cLoginData
{
public:
  C2cLoginData();
  C2cLoginData(const C2cLoginData & other);
  ~C2cLoginData();

  C2cLoginData & operator=(const C2cLoginData & other);

  void from_json(const QJsonDocumentPtr & json_document);
  void reset();

  bool is_valid() const { return m_id > 0; }
  explicit operator bool() const { return is_valid(); }
  bool is_expired() const { return QDateTime::currentDateTime() >= m_expire; }

  const QString & language() const { return m_language; }
  void set_language(const QString & language) { m_language = language; }

  const QDateTime & expire() const { return m_expire; }
  void set_expire(const QDateTime & expire) { m_expire = expire; }

  unsigned int id() const { return m_id; }
  void set_id(unsigned int id) { m_id = id; }

  const QString & token() const { return m_token; }
  void set_token(const QString & token) { m_token = token; }

  const QString & forum_username() const { return m_forum_username; }
  void set_forum_username(const QString & forum_username) { m_forum_username = forum_username; }

  const QString & name() const { return m_name; }
  void set_name(const QString & name) { m_name = name; }

  const QString & roles() const { return m_roles; }
  void set_roles(const QString & roles) { m_roles = roles; }

  const QString & redirect_internal() const { return m_redirect_internal; }
  void set_redirect_internal(const QString & redirect_internal) { m_redirect_internal = redirect_internal; }

  const QString & username() const { return m_username; }
  void set_username(const QString & username) { m_username = username; }

private:
  QString m_language;
  QDateTime m_expire;
  unsigned int m_id;
  QString m_token;
  QString m_forum_username;
  QString m_name;
  QString m_roles;
  QString m_redirect_internal;
  QString m_username;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const C2cLoginData & login_data);
#endif

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_LOGIN_DATA_H__ */
