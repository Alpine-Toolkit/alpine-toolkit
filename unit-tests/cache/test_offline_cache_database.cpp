/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include <QFile>
#include <QtDebug>
#include <QtTest/QtTest>

/**************************************************************************************************/

#include "cache/offline_cache_database.h"

/***************************************************************************************************/

class TestQcOfflineCacheDatabase: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestQcOfflineCacheDatabase::constructor()
{
  QString sqlite_path = "offline_cache.sqlite";
  QFile(sqlite_path).remove();
  QcOfflineCacheDatabase database(sqlite_path);

  QcTileSpec tile_spec("foo", 1, 1, 0, 0);
  QVERIFY(database.has_tile(tile_spec) == 0);
  database.insert_tile(tile_spec);
  QVERIFY(database.has_tile(tile_spec) == 1);
  database.insert_tile(tile_spec);
  QVERIFY(database.has_tile(tile_spec) == 2);
}

/***************************************************************************************************/

QTEST_MAIN(TestQcOfflineCacheDatabase)
#include "test_offline_cache_database.moc"
