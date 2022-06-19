/***************************************************************************************************
 **
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 **
 ***************************************************************************************************/

/**************************************************************************************************/

#include <QSqlDatabase>
#include <QSqlError> // Fixme: ???
#include <QSqlQuery>
#include <QtDebug>
#include <QtTest/QtTest>

#include "geo_data_format/wkb.h"

/***************************************************************************************************/

class TestSpatialite: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void
TestSpatialite::constructor()
{
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE-AT");
  // QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("spatialite-test.sqlite");
  if (!db.open()) {
    qWarning() << "cannot open db";
    return;
  }
  qWarning() << "Database opened";

  QSqlQuery query;

  query = db.exec("SELECT load_extension('mod_spatialite')");
  qWarning() << query.size() << db.lastError();

  query = db.exec("SELECT spatialite_version()");
  query.first();
  qWarning() << query.size() << db.lastError();
  qInfo() << query.value(0).toString();

  query = db.exec("SELECT InitSpatialMetaData(1);");
  qWarning() << query.size() << db.lastError();

  query = db.exec("CREATE TABLE places (name TEXT NOT NULL);");
  qWarning() << query.size() << db.lastError();

  QcWkbPoint point(4.1, 3.2);
  qInfo() << "Point" << point.to_wkt() << point.to_wkb();

  query = db.exec("SELECT AddGeometryColumn('places', 'geometry', 4326, 'POINT', 'XY');");
  qWarning() << query.size() << db.lastError();

  query = db.exec("INSERT INTO places (name, geometry) values (\"place1\", MakePoint(4.1, 3.2, 4326))");
  qWarning() << db.lastError();

  // Return
  // "\x00\x01\xE6\x10\x00\x00""ffffff\x10@\x9A\x99\x99\x99\x99\x99\t@ffffff\x10@\x9A\x99\x99\x99\x99\x99\t@|\x01\x00\x00\x00""ffffff\x10@\x9A\x99\x99\x99\x99\x99\t@\xFE")
  query = db.exec("SELECT name, geometry FROM places");
  qWarning() << query.size() << db.lastError();
  while (query.next()) {
    qInfo() << query.value(0).toString() << query.value(1).toByteArray();
  }

  // OGC: ST_AsText
  // Return: POINT(4.1 3.2)
  query = db.exec("SELECT name, ST_AsText(geometry) FROM places");
  qWarning() << query.size() << db.lastError();
  while (query.next()) {
    QString wkt = query.value(1).toString();
    qInfo() << "AsText" << query.value(0).toString() << wkt;
  }

  // Return: POINT(4.1 3.2)
  query = db.exec("SELECT name, AsWKT(geometry) FROM places");
  qWarning() << query.size() << db.lastError();
  while (query.next()) {
    QString wkt = query.value(1).toString();
    qInfo() << query.value(0).toString() << wkt;
    QcWkbGeometryObject * geometry_object = QcWkbGeometryObject::init_from_wkt(wkt);
    qInfo() << "AsWKT" << geometry_object->to_wkt() << geometry_object->to_wkb();
  }

  // OGC: ST_AsBinary
  // Return: QVariant(QByteArray, "\x01\x01\x00\x00\x00""ffffff\x10@\x9A\x99\x99\x99\x99\x99\t@")
  query = db.exec("SELECT name, ST_AsBinary(geometry) FROM places");
  qWarning() << query.size() << db.lastError();
  while (query.next()) {
    QByteArray wkb = query.value(1).toByteArray();
    qInfo() << query.value(0).toString() << wkb;
    QcWkbPoint point(wkb);
    qInfo() << "AsBinary" << point.to_wkt() << point.to_wkb();
  }

  // OGC: ST_GeomFromText
  QString sql_query;
  sql_query = QString("INSERT INTO places (name, geometry) values (\"place2\", ST_GeomFromText(\"\%1\", 4326))").arg(point.to_wkt());
  query = db.exec(sql_query);
  qWarning() << db.lastError();

  // OGC: ST_GeomFromWBK
  QString wkb_string = point.to_wkb().toHex();
  sql_query = QString("INSERT INTO places (name, geometry) values ('place3', ST_GeomFromWKB(X'%1', 4326))").arg(wkb_string);
  query = db.exec(sql_query);
  qWarning() << db.lastError();

  sql_query = QString("INSERT INTO places (name, geometry) values ('place4', PointFromWKB(X'%1', 4326))").arg(wkb_string);
  query = db.exec(sql_query);
  qWarning() << db.lastError();

  // AsEWKB GeomFromEWKB
  // AsEWKT GeomFromEWKT

  query = db.exec("SELECT name, AsWKT(geometry) FROM places");
  qWarning() << query.size() << db.lastError();
  while (query.next()) {
    QString wkt = query.value(1).toString();
    qInfo() << query.value(0).toString() << wkt;
  }
}

/***************************************************************************************************/

QTEST_MAIN(TestSpatialite)
#include "test_spatialite.moc"
