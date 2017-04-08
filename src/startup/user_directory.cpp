/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
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
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include <QDir>
#include <QStandardPaths>
#include <QString>
#include <QtDebug>

/**************************************************************************************************/

#include "startup.h"

/**************************************************************************************************/

QDir
create_user_application_directory()
{
  // on Android
  //   DataLocation = /data/data/org.alpine_toolkit
  //   GenericDataLocation = <USER> = /storage/emulated/0 = user land root
  // on Linux
  //   GenericDataLocation = /home/fabrice/.local/share
  QString generic_data_location_path = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
  qInfo() << "GenericDataLocation:" << generic_data_location_path;
  // /storage/emulated/0/Android/data/org.xxx/files Alarms Download Notifications cache

  QString application_user_directory_path = QDir(generic_data_location_path).filePath("alpine-toolkit");
  QDir application_user_directory(application_user_directory_path);
  if (! application_user_directory.exists()) {
    if (!application_user_directory.mkpath(application_user_directory.absolutePath())) {
      qWarning() << "Cannot create application user directory";
    }
  }

  return application_user_directory;
}

QString
copy_file_from_asset(const QDir & destination, const QString & filename)
{
  QString relative_source_path(QLatin1String("assets:/data/") + filename);
  QFileInfo file_info(relative_source_path);
  QString source_path = file_info.absoluteFilePath();
  if (!file_info.exists())
    qCritical() << "File" << filename << "not found in asset";
  QString destination_path = destination.filePath(filename);
  bool copy_success = QFile::copy(source_path, destination_path);
  if (copy_success) {
    qInfo() << "Copy" << source_path << "to" << destination_path;
    return destination_path;
  } else {
    qCritical() << "Failed to copy" << source_path << "to" << destination_path;
    return QString();
  }
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
