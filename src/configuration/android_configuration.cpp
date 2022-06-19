/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "android_configuration.h"
#include "alpine_toolkit.h"

#include <QDir>
#include <QStandardPaths>
#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QaAndroidConfig::QaAndroidConfig()
  : QaConfig()
{
  QString path = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
  qATInfo() << "GenericDataLocation:" << path;
  // I Alpine Toolkit: alpine-toolkit: GenericDataLocation: "/storage/emulated/0"

  application_user_directory("/sdcard/org.alpine_toolkit");
}

QaAndroidConfig::~QaAndroidConfig()
{}

/*
 * DataLocation = /data/data/org.alpine_toolkit
 * GenericDataLocation = <USER> = /storage/emulated/0 = user land root
 * /storage/emulated/0/Android/data/org.alpine_toolkit/files
 * /storage/XXXX-XXXX/Android/data/org.alpine_toolkit/files
 */

QString
QaAndroidConfig::generic_data_location() const
{
  QString path = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
  // qATInfo() << "GenericDataLocation:" << path;
  return path;
}

// UNUSED
QString
QaAndroidConfig::make_application_user_directory_path(const QString & root_path, bool public_path) const
{
  QString path;
  if (public_path)
    // This directory is destroyed when the application is uninstalled
    path += QStringLiteral("Android/data/");
  // else persistent directory require permission
  path += ANDROID_PACKAGE_NAME;

  return QDir(root_path).filePath(path);
}

/**************************************************************************************************/

// QC_END_NAMESPACE
