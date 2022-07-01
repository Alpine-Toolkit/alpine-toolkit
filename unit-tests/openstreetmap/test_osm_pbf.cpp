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

#include "openstreetmap/osm_pbf.h"

/***************************************************************************************************/

class TestQcOsmPbf: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void
TestQcOsmPbf::constructor()
{
  // QString pbf_path("/home/scratch/sources/cartographie/osm-extract/bezons.osm.pbf");
  QString pbf_path("/home/scratch/sources/cartographie/osm-extract/ile-de-france-latest.osm.pbf");
  QcOsmPbfReader osm_pbf_reader(pbf_path);
  osm_pbf_reader.read_file(true, true, true, false);
}

/***************************************************************************************************/

QTEST_MAIN(TestQcOsmPbf)
#include "test_osm_pbf.moc"
