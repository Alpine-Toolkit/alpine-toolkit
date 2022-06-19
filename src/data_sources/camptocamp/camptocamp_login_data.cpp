/***************************************************************************************************
 **
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 **
 ***************************************************************************************************/

/**************************************************************************************************/

#include "camptocamp/camptocamp_login_data.h"
#include "alpine_toolkit.h"

#include <QJsonObject>
#include <QtDebug>

/**************************************************************************************************/

C2cLoginData::C2cLoginData()
  : m_language(),
    m_expire(),
    m_id(),
    m_token(),
    m_forum_username(),
    m_name(),
    m_roles(),
    m_redirect_internal(),
    m_username()
{}

C2cLoginData::C2cLoginData(const C2cLoginData & other)
  : m_language(other.m_language),
    m_expire(other.m_expire),
    m_id(other.m_id),
    m_token(other.m_token),
    m_forum_username(other.m_forum_username),
    m_name(other.m_name),
    m_roles(other.m_roles),
    m_redirect_internal(other.m_redirect_internal),
    m_username(other.m_username)
{}

C2cLoginData::~C2cLoginData()
{}

void
C2cLoginData::from_json(const QJsonDocumentPtr & json_document)
{
  QJsonObject root = json_document->object();
  m_language = root[QStringLiteral("lang")].toString();
  m_expire = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(root[QStringLiteral("expire")].toInt()) * 1000);
  // set_expire(QDateTime::fromSecsSinceEpoch(root[QStringLiteral("expire")].toInt()));
  m_id = root[QStringLiteral("id")].toInt();
  m_token = root[QStringLiteral("token")].toString();
  m_forum_username = root[QStringLiteral("forum_username")].toString();
  m_name = root[QStringLiteral("name")].toString();
  m_roles = root[QStringLiteral("roles")].toString();
  m_redirect_internal = root[QStringLiteral("redirect_internal")].toString();
  m_username = root[QStringLiteral("username")].toString();
}

void
C2cLoginData::reset()
{
  m_id = 0;
  m_expire = QDateTime();

  m_language.clear();
  m_token.clear();
  m_forum_username.clear();
  m_name.clear();
  m_roles.clear();
  m_redirect_internal.clear();
  m_username.clear();
}

C2cLoginData &
C2cLoginData::operator=(const C2cLoginData & other)
{
  if (this != &other) {
    m_language = other.m_language;
    m_expire = other.m_expire;
    m_id = other.m_id;
    m_token = other.m_token;
    m_forum_username = other.m_forum_username;
    m_name = other.m_name;
    m_roles = other.m_roles;
    m_redirect_internal = other.m_redirect_internal;
    m_username = other.m_username;
  }

  return *this;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const C2cLoginData & login_data)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace() << QStringLiteral("C2cLoginData(") << '\n'; // std::endl
  debug << "  id: " << login_data.id() << '\n';
  debug << "  username: " << login_data.username() << '\n';
  debug << "  expire: " << login_data.expire() << '\n';
  debug << "  token: " << login_data.token() << '\n';
  debug << "  forum username: " << login_data.forum_username() << '\n';
  debug << "  name: " << login_data.name() << '\n';
  debug << "  language: " << login_data.language() << '\n';
  debug << "  redirect interval: " << login_data.redirect_internal() << '\n';
  debug << "  roles: " << login_data.roles() << '\n';
  debug << ')';

  return debug;
}
#endif
