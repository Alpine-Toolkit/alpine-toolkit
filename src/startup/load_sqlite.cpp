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

#include <QFileInfo>
#include <QSqlDatabase>
#include <QtDebug>

#include "startup.h"
#include "sql_model/SqlQueryModel.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/* Load FFCAM Refuges SQlite Database
 *
 */
void
load_sqlite(const QDir & application_user_directory)
{
  // Fixme: use database api ?
  QString sqlite_path_src_relative("assets:/data/ffcam-refuges.sqlite");
  QFileInfo sqlite_file_info(sqlite_path_src_relative);
  QString sqlite_path_src = sqlite_file_info.absoluteFilePath();
  if (!sqlite_file_info.exists())
    qInfo() << sqlite_path_src << "not found";
  QString sqlite_path_dst = application_user_directory.filePath("ffcam-refuges.sqlite");
  qInfo() << sqlite_path_src << sqlite_path_dst;
  bool copy_success = QFile::copy(sqlite_path_src, sqlite_path_dst);
  qInfo() << "copy:" << copy_success;
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(sqlite_path_dst);
  if (!db.open())
    qInfo() << "database not open"; // db.lastError();
  SqlQueryModel * sql_model = new SqlQueryModel();
  sql_model->set_query("SELECT * FROM refuges", db);

  // root_context->setContextProperty("sql_model", sql_model);
}

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
