/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
