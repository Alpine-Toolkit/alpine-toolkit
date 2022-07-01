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

/**************************************************************************************************/

#include "geo_data_format/gpx.h"

/***************************************************************************************************/

class TestQcGpx: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestQcGpx::constructor()
{
  QcGpxReader gpx_reader;
  QString gpx_path = "/home/fabrice/qtcarto-application/resources/gpx/garmin-track1.gpx";
   // QString gpx_path = "/home/fabrice/qtcarto-application/resources/gpx/route2.gpx";
  QcGpx gpx = gpx_reader.read(gpx_path);

  QcGpxWriter gpx_writer;
  QString gpx_output_path = "out.gpx";
  gpx_writer.write(gpx, gpx_output_path);

  // QVERIFY();
}

/***************************************************************************************************/

QTEST_MAIN(TestQcGpx)
#include "test_gpx.moc"
