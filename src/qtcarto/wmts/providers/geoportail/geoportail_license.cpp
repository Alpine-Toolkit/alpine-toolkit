/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "geoportail_license.h"
#include "qtcarto.h"

#include <stdexcept>

#include <QByteArray>
#include <QFile>
#include <QJsonDocument>
#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QcGeoportailWmtsLicense::QcGeoportailWmtsLicense(const QString & json_path)
  : m_user()
  , m_password()
  , m_api_key()
  , m_offline_cache_limit()
{
  load_json(json_path);
}

QcGeoportailWmtsLicense::QcGeoportailWmtsLicense(const QString & user,
                                                 const QString & password,
                                                 const QString & api_key,
						 unsigned int offline_cache_limit)
  : m_user(user)
  , m_password(password)
  , m_api_key(api_key)
  , m_offline_cache_limit(offline_cache_limit)
{}

QcGeoportailWmtsLicense::QcGeoportailWmtsLicense(const QcGeoportailWmtsLicense & other)
  : m_user(other.m_user)
  , m_password(other.m_password)
  , m_api_key(other.m_api_key)
  , m_offline_cache_limit(other.m_offline_cache_limit)
{}

QcGeoportailWmtsLicense &
QcGeoportailWmtsLicense::operator=(const QcGeoportailWmtsLicense & other)
{
  if (this != &other) {
    m_user = other.m_user;
    m_password = other.m_password;
    m_api_key = other.m_api_key;
    m_offline_cache_limit = other.m_offline_cache_limit;
  }

  return *this;
}

bool
QcGeoportailWmtsLicense::operator==(const QcGeoportailWmtsLicense & rhs) const
{
  return (m_user == rhs.m_user
	  && m_password == rhs.m_password
	  && m_api_key == rhs.m_api_key
          && m_offline_cache_limit == rhs.m_offline_cache_limit
          );
}

void
QcGeoportailWmtsLicense::read_json(const QJsonObject &json)
{
  m_user = json["user"].toString();
  m_password = json["password"].toString();
  m_api_key = json["api_key"].toString();
  m_offline_cache_limit = json["offline_cache_limit"].toInt();
}

void
QcGeoportailWmtsLicense::load_json(const QString & json_path)
{
  QFile json_file(json_path);

  if (!json_file.open(QIODevice::ReadOnly)) {
    QString message =  QLatin1String("Couldn't open file ") + json_path;
    // throw std::invalid_argument(message.toStdString().c_str());
    qWarning() << message;
  }

  QByteArray json_data = json_file.readAll();
  QJsonDocument json_document(QJsonDocument::fromJson(json_data));
  read_json(json_document.object());

  QString message =  QLatin1String("Loaded Geoportail License ") + json_path;
  qInfo() << message;
  message =  QLatin1String("API key ") + m_api_key;
  qInfo() << message;
}
