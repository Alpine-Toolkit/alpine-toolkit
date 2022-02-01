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
