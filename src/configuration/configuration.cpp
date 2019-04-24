/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
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

#include "android_configuration.h"
#include "linux_configuration.h"
#include "alpine_toolkit.h"

#include <QDir>
#include <QStandardPaths>
#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/*
 * QSettings file is
 *  - on Linux
 *     INI
 *     $HOME/.config/Alpine Toolkit/Alpine Toolkit.conf
 *
 */

/***********************************************************************************
***************/

QaConfig *
QaConfig::instance()
{
  // Thread-safe in C++11

#ifdef ON_LINUX
  static QaLinuxConfig _instance;
#endif

#ifdef ON_ANDROID
  static QaAndroidConfig _instance;
#endif

  return &_instance;
}

/**************************************************************************************************/

QaConfig::QaConfig()
  : QObject(),
    m_is_storage_enabled(false),
    m_env(QProcessEnvironment::systemEnvironment()),
    m_settings(ORGANISATION_NAME, APPLICATION_NAME), // To ensure correct values
    m_application_user_directory()
{
  load_settings();

  m_is_mockup_enabled = get_env(QLatin1Literal("MOCKUP")) == QLatin1Literal("TRUE");

  // m_is_storage_enabled = QDir(m_application_user_directory).exists();
}

QaConfig::~QaConfig()
{}

QString
QaConfig::get_env(const QString name) const
{
  QString env_name = QLatin1Literal("ALPINE_TOOLKIT_") + name;
  QString value = m_env.value(env_name);
  qATInfo() << "Environment variable: " << env_name << "=" << value;

  return value;
}

void
QaConfig::create_application_user_directory()
{
  // Could require Android permission
  create_directory(m_application_user_directory, QLatin1Literal("application user"));
  create_directory(wmts_token_directory(), QLatin1Literal("wmts token"));

  m_is_storage_enabled = true;
}

void
QaConfig::load_settings()
{
  // on Linux $HOME/.config/Apline Toolkit/Alpine Toolkit.conf
  // on Android "/data/data/org.alpine_toolkit/files/.config/Apline Toolkit/Alpine Toolkit.conf"

  qATInfo() << "Settings file path:" << m_settings.fileName() << m_settings.format();

  // qputenv("QT_LABS_CONTROLS_STYLE", settings.value("style").toByteArray());
}

void
QaConfig::create_directory(const QString path, const QString label) const
{
  QDir directory = path;
  if (not directory.exists()) {
    if (not directory.mkpath(directory.absolutePath()))
      qWarning() << QLatin1Literal("Cannot create") << label << QLatin1Literal("directory") << path;
    qATInfo() << QLatin1Literal("Created") << label << QLatin1Literal("directory") << path;
  }
}

const QString
QaConfig::join_application_user_directory(const QString & path) const
{
  // Fixme: absoluteFilePath vs filePath ???
  return QDir(m_application_user_directory).absoluteFilePath(path);
}

const QString
QaConfig::wmts_cache_directory() const
{
#ifdef ON_LINUX
  QString cache_path = QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation);
  QString path = QDir(cache_path).absoluteFilePath(QLatin1Literal("QtCarto"));
#endif

#ifdef ON_ANDROID
  QString path = join_application_user_directory(QLatin1Literal("wmts_cache"));
#endif

  qATInfo() << "wmts_cache_directory" << path;

  return path;
}

const QString
QaConfig::wmts_token_directory() const
{
  QString path = join_application_user_directory(QLatin1Literal("wmts_token"));
  qATInfo() << "wmts_token_directory" << path;
  return path;
}

const QString
QaConfig::geoportail_token_path() const
{
  // Fixme: Hide license
  QString path = QDir(wmts_token_directory()).absoluteFilePath(QLatin1Literal("geoportail-license.json"));
  qATInfo() << "geoportail_token_path";
  return path;
}

const QString
QaConfig::c2c_cache_path() const
{
  qATInfo() << "c2c_cache_path";

  // QDir c2c_cache_path = m_engine.offlineStoragePath(); // same as application_user_directory
  return m_application_user_directory;
}

const QString
QaConfig::c2c_api_cache_path() const
{
  qATInfo() << "c2c_api_cache_path";

  return QDir(c2c_cache_path()).absoluteFilePath(QLatin1String("c2c-cache.sqlite"));
}

const QString
QaConfig::c2c_media_cache_path() const
{
  qATInfo() << "c2c_media_cache_path";

  return QDir(c2c_cache_path()).absoluteFilePath(QLatin1String("media"));
}

/**************************************************************************************************/

// QC_END_NAMESPACE
