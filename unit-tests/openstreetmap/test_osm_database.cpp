/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include <QtTest/QtTest>
#include <QtDebug>

#include <QSqlError>

/**************************************************************************************************/

#include "openstreetmap/osm_database.h"

#include "geo_data_format/wkb.h"

/***************************************************************************************************/

class TestQcOsmDatabase: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void
TestQcOsmDatabase::constructor()
{
  QcDatabaseConnectionData connection_data = {
    .host = "localhost",
    .port = 5432,
    .database = "gis-dev",
    .user = "gis-dev",
    .password = "gis-dev",
  };

  QcOsmDatabase osm_database(connection_data);

  // Fixme: query visitor

  // const QString sql_query = "SELECT osm_id, ST_AsBinary(way) from planet_osm_point;";
  const QString sql_query = "SELECT osm_id, way from planet_osm_point;";
  //               01 01000020 31BF0D00 2D9ED55D34AF0140B45FD27366764840
  // ST_AsEWKB   \x01 01000020 31bf0d00 2d9ed55d34af0140b45fd27366764840
  // ST_AsBinary \x01 01000000          2d9ed55d34af0140b45fd27366764840
  // ST_AsEWKT   SRID=900913;POINT(2.2105491 48.9250016)
  // 900913 = 0x000dbf31 -> 31bf0d00
  QSqlQuery query = osm_database.new_query();
  if (!query.exec(sql_query))
    qWarning() << query.lastError().text();

  while (query.next()) {
    QSqlRecord record = query.record();
    int i = 0;
    int osm_id = record.value(i++).toInt();
    QByteArray wkb =  record.value(i++).toByteArray();
    qInfo() << "Node" << osm_id << wkb;
    QcWkbPoint geometry_object = QcWkbPoint(QByteArray::fromHex(wkb)); // fromHex only if raw
    qInfo() << geometry_object.to_wkt();
  }

  QString pbf_path("/home/scratch/sources/cartographie/osm-extract/bezons.osm.pbf");
  // QString pbf_path("/home/scratch/sources/cartographie/osm-extract/ile-de-france-latest.osm.pbf");
  // QcOsmPbfDatabaseImporter importer(pbf_path, osm_database);
  // importer.read_file(true, true, true, false);
}

/***************************************************************************************************/

QTEST_MAIN(TestQcOsmDatabase)
#include "test_osm_database.moc"
