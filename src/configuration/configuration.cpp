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

#include "config.h"

#include <QDir>
#include <QStandardPaths>
#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QcConfig::QcConfig()
  : m_initialised(false)
{
  QString generic_data_location_path = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
  // qInfo() << "GenericDataLocation:" << generic_data_location_path;

  // Fixme: could use PlatformAbstraction::instance()
#ifdef ON_LINUX
  // GenericDataLocation = /home/fabrice/.local/share
  m_application_user_directory = QDir(generic_data_location_path).filePath(CONFIG_DIRECTORY_NAME);
#endif

#ifdef ON_ANDROID
  // DataLocation = /data/data/org.alpine_toolkit
  // GenericDataLocation = <USER> = /storage/emulated/0 = user land root
  // /storage/emulated/0/Android/data/org.alpine_toolkit/files
  // /storage/0060-1F18/Android/data/org.alpine_toolkit/files
  // Fixme: could use sdcard as well

  // This directory is destroyed when the application is uninstalled
  // m_application_user_directory = QDir(generic_data_location_path).filePath(QLatin1Literal("Android/data/") + ANDROID_PACKAGE_NAME);

  // Persistent directory, but require permission
  m_application_user_directory = QDir(generic_data_location_path).filePath(ANDROID_PACKAGE_NAME);
#endif
}

QcConfig::~QcConfig()
{}

void
QcConfig::init()
{
  if (m_initialised)
    return;

  create_directory(m_application_user_directory, QLatin1Literal("application user"));
  create_directory(wmts_cache_directory(), QLatin1Literal("wmts cache"));
  create_directory(wmts_token_directory(), QLatin1Literal("wmts token"));

  m_initialised = true;
}

void
QcConfig::create_directory(const QString path, const QString label) const
{
  QDir directory = path;
  if (not directory.exists()) {
    if (not directory.mkpath(directory.absolutePath()))
      qWarning() << QLatin1Literal("Cannot create") << label << QLatin1Literal("directory") << path;
    qInfo() << QLatin1Literal("Created") << label << QLatin1Literal("directory") << path;
  }
}

const QString
QcConfig::join_application_user_directory(const QString & path) const
{
  return QDir(m_application_user_directory).absoluteFilePath(path);
}

const QString
QcConfig::wmts_cache_directory() const
{
#ifdef ON_LINUX
  return QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation);
#endif

#ifdef ON_ANDROID
  return join_application_user_directory(QLatin1Literal("wmts_cache"));
#endif
}

const QString
QcConfig::wmts_token_directory() const
{
  return join_application_user_directory(QLatin1Literal("wmts_token"));
}

const QString
QcConfig::geoportail_token_path() const
{
  // Fixme: Hide license
  return QDir(wmts_token_directory()).filePath(QLatin1Literal("geoportail-license.json"));
}

/**************************************************************************************************/

// QC_END_NAMESPACE
