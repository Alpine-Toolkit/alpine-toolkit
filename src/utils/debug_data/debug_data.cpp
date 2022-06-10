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

#include "debug_data.h"
#include "alpine_toolkit.h"

#include "configuration/configuration.h"
#include "platform/platform.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLibraryInfo>
#include <QSysInfo>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QcDebugData::QcDebugData()
{}

QcDebugData::~QcDebugData()
{}

QByteArray
QcDebugData::to_json() const
{
  QJsonObject root_object;

  QcPlatform & platform = QcPlatform::instance();
  root_object[QStringLiteral("platform")] = platform.to_json();

  QJsonObject version_object;
  // Fixme: config.h
  version_object[QStringLiteral("alpine_toolkit_version")] = ALPINE_TOOLKIT_VERSION.toString();
  QJsonObject qt_object;
  qt_object[QStringLiteral("qt_version")] = qVersion();
  qt_object[QStringLiteral("prefix_path")] = QLibraryInfo::path(QLibraryInfo::PrefixPath);
  qt_object[QStringLiteral("is_debug_build")] = QLibraryInfo::isDebugBuild();
  version_object[QStringLiteral("qt")] = qt_object;
  root_object[QStringLiteral("version")] = version_object;

  QaConfig * config = QaConfig::instance();
  QJsonObject config_object;
  config_object[QStringLiteral("application_user_directory")] = config->application_user_directory();
  root_object[QStringLiteral("config")] = config_object;

  // To add:
  //   locale / translation
  //   error message
  //   Android
  //     ram
  //     available disk space
  //     number of installs

  QJsonDocument document(root_object);

  return document.toJson(QJsonDocument::Indented); // QJsonDocument::Compact
}

bool
QcDebugData::write_json(const QString & json_path) const
{
  QFile json_file(json_path);
  if (!json_file.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open json file.");
    return false;
  }
  json_file.write(to_json());
  return true;
}

/**************************************************************************************************/

// QC_END_NAMESPACE
