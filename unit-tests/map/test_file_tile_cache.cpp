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

/**************************************************************************************************/

#include "cache/file_tile_cache.h"

/***************************************************************************************************/

class TestQcFileTileCache: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestQcFileTileCache::constructor()
{
  QcFileTileCache * file_tile_cache = new QcFileTileCache();
  file_tile_cache->clear_all();

  QcTileSpec tile_spec("geoportail", 1, 16, 33885, 23658);

  QFile file("../test-data/wmts.jpg");
  file.open(QIODevice::ReadOnly);
  QByteArray bytes = file.readAll();
  file_tile_cache->insert(tile_spec, bytes, QStringLiteral("jpg"));

  delete file_tile_cache;
  file_tile_cache = new QcFileTileCache();
  QSharedPointer<QcTileTexture> tile_texture = file_tile_cache->get(tile_spec);
  QVERIFY(tile_texture.isNull() == false);
  if (tile_texture)
    QVERIFY(tile_texture->tile_spec == tile_spec);
}

/***************************************************************************************************/

QTEST_MAIN(TestQcFileTileCache)
#include "test_file_tile_cache.moc"
