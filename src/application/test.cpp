/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the QtCarto library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $QTCARTO_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "application.h"

#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QtDebug>

#include <QSqlDatabase>
#include <QSqlError> // Fixme: ???
#include <QSqlQuery>

/**************************************************************************************************/

void
Application::run_before_event_loop()
{
  /*
  QFile output_file(application_user_directory.filePath("out.txt"));
  if (!output_file.open(QIODevice::WriteOnly | QIODevice::Text))
    qWarning() << "couldn't write to file";
  QTextStream out(&output_file);
  out << "The magic number is: " << 49 << "\n";
  */

  /*
  QFile input_file("assets:/file1.txt");
  if (!input_file.open(QIODevice::ReadOnly | QIODevice::Text))
    qWarning() << "couldn't read to file";
  while (!input_file.atEnd()) {
    QByteArray line = input_file.readLine();
    qInfo() << line;
  }
  */

  /*
  qInfo() << "SQLite Plugin Test";
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE-AT");
  // QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  QString sqlite_path = application_user_directory.filePath("spatialite-test.sqlite");
  db.setDatabaseName(sqlite_path);
  if (!db.open()) {
    qWarning() << "cannot open db";
    return;
  }
  qWarning() << "Database opened";

  QSqlQuery query;

  query = db.exec("SELECT load_extension('libspatialite', 'sqlite3_modspatialite_init')");
  qWarning() << query.size() << db.lastError();

  query = db.exec("SELECT spatialite_version()");
  query.first();
  qWarning() << query.size() << db.lastError();
  qInfo() << query.value(0).toString();

  query = db.exec("SELECT InitSpatialMetaData(1);");
  qWarning() << query.size() << db.lastError();

  query = db.exec("CREATE TABLE places (name TEXT NOT NULL);");
  qWarning() << query.size() << db.lastError();

  query = db.exec("SELECT AddGeometryColumn('places', 'geometry', 4326, 'POINT', 'XY');");
  qWarning() << query.size() << db.lastError();

  query = db.exec("INSERT INTO places (name, geometry) values (\"place3\", MakePoint(4.1, 3.2, 4326))");
  qWarning() << db.lastError();

  query = db.exec("SELECT name, geometry FROM places");
  qWarning() << query.size() << db.lastError();
  while (query.next()) {
    // QVariant(QByteArray,
    qInfo() << query.value(0).toString() << query.value(1);
  }

  query = db.exec("SELECT name, AsText(geometry) FROM places");
  qWarning() << query.size() << db.lastError();
  while (query.next()) {
    // QVariant(QByteArray,
    qInfo() << query.value(0).toString() << query.value(1);
  }
  */
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
