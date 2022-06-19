/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
    qWarning() << "couldn't read file";
  while (!input_file.atEnd()) {
    QByteArray line = input_file.readLine();
    qATInfo() << line;
  }
  */

  // /storage/0060-1F18/
  // /storage/0060-1F18/Android/data/org.alpine_toolkit/files
  /*
  QFile input_file("/storage/0060-1F18/Android/data/org.alpine_toolkit/files/external-sdcard-test.txt");
  if (input_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    while (!input_file.atEnd()) {
      QByteArray line = input_file.readLine();
      qATInfo() << line;
    }
    input_file.close();
  } else
    qWarning() << "couldn't read file on external sdcard";
  if (input_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    input_file.write("foo");
    input_file.close();
  } else {
    qWarning() << "couldn't write file on external sdcard";
  }
  */

  /*
  qATInfo() << "SQLite Plugin Test";
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
  qATInfo() << query.value(0).toString();

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
    qATInfo() << query.value(0).toString() << query.value(1);
  }

  query = db.exec("SELECT name, AsText(geometry) FROM places");
  qWarning() << query.size() << db.lastError();
  while (query.next()) {
    // QVariant(QByteArray,
    qATInfo() << query.value(0).toString() << query.value(1);
  }
  */
}
