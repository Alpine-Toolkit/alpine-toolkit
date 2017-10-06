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

#include "configuration.h"
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

/**************************************************************************************************/

QaConfig::QaConfig()
  : QObject(),
    m_initialised(false),
    m_env(QProcessEnvironment::systemEnvironment()),
    m_settings(ORGANISATION_NAME, APPLICATION_NAME) // To ensure correct values
{
  load_settings();

  m_is_mockup_enabled = get_env(QLatin1Literal("MOCKUP")) == QLatin1Literal("TRUE");

  QString generic_data_location_path = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
  // qATInfo() << "GenericDataLocation:" << generic_data_location_path;

  // Fixme: could use PlatformAbstraction::instance()
#ifdef ON_LINUX
  // GenericDataLocation = $HOME/.local/share
  m_application_user_directory = QDir(generic_data_location_path).filePath(CONFIG_DIRECTORY_NAME);
#endif

#ifdef ON_ANDROID
  // DataLocation = /data/data/org.alpine_toolkit
  // GenericDataLocation = <USER> = /storage/emulated/0 = user land root
  // /storage/emulated/0/Android/data/org.alpine_toolkit/files
  // /storage/XXXX-XXXX/Android/data/org.alpine_toolkit/files
  // Fixme: could use sdcard as well

  // This directory is destroyed when the application is uninstalled
  // m_application_user_directory = QDir(generic_data_location_path).filePath(QLatin1Literal("Android/data/") + ANDROID_PACKAGE_NAME);

  // Persistent directory, but require permission
  m_application_user_directory = QDir(generic_data_location_path).filePath(ANDROID_PACKAGE_NAME);
#endif
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
QaConfig::init()
{
  if (m_initialised)
    return;

  // Could require Android permission
  create_directory(m_application_user_directory, QLatin1Literal("application user"));
  create_directory(wmts_cache_directory(), QLatin1Literal("wmts cache"));
  create_directory(wmts_token_directory(), QLatin1Literal("wmts token"));

  m_initialised = true;
}

void
QaConfig::load_settings()
{
  qATInfo() << "Settings file path:" << m_settings.fileName() << m_settings.format();

  // Settings file path: "$HOME/.config/Apline Toolkit/Alpine Toolkit.conf" 0
  // Settings file path: "/data/data/org.alpine_toolkit/files/.config/Apline Toolkit/Alpine Toolkit.conf" 0
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
  return QDir(m_application_user_directory).absoluteFilePath(path);
}

const QString
QaConfig::wmts_cache_directory() const
{
#ifdef ON_LINUX
  return QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation);
#endif

#ifdef ON_ANDROID
  return join_application_user_directory(QLatin1Literal("wmts_cache"));
#endif
}

const QString
QaConfig::wmts_token_directory() const
{
  return join_application_user_directory(QLatin1Literal("wmts_token"));
}

const QString
QaConfig::geoportail_token_path() const
{
  // Fixme: Hide license
  return QDir(wmts_token_directory()).filePath(QLatin1Literal("geoportail-license.json"));
}

/**************************************************************************************************/

// QC_END_NAMESPACE
