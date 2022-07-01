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

#include "geometry/polygon.h"

/***************************************************************************************************/

class TestQcPolygon: public QObject
{
  Q_OBJECT

private slots:
  void contains();
  void intersec_with_grid();
};

void
TestQcPolygon::contains()
{
  QcPolygon polygon(QVector<double>({1, 3, 6, 14, 9, 1, 17, 3, 12, 10, 5, 7, 12, 5}));

  QVERIFY(polygon.contains(QcVectorDouble(0, 0)) == false);
  QVERIFY(polygon.contains(QcVectorDouble(100, 100)) == false);
  QVERIFY(polygon.contains(QcVectorDouble(1, 3)) == true);
  QVERIFY(polygon.contains(QcVectorDouble(4, 5)) == true);
  QVERIFY(polygon.contains(QcVectorDouble(5, 7)) == true);
  QVERIFY(polygon.contains(QcVectorDouble(6, 7)) == false);
  QVERIFY(polygon.contains(QcVectorDouble(7, 7)) == false);
  QVERIFY(polygon.contains(QcVectorDouble(8, 7)) == true);
  QVERIFY(polygon.contains(QcVectorDouble(9, 5)) == false);
  QVERIFY(polygon.contains(QcVectorDouble(10, 5)) == false);
  QVERIFY(polygon.contains(QcVectorDouble(11, 5)) == false);
  QVERIFY(polygon.contains(QcVectorDouble(12, 5)) == true);
  QVERIFY(polygon.contains(QcVectorDouble(12, 10)) == true);
  QVERIFY(polygon.contains(QcVectorDouble(13, 10)) == false);
  QVERIFY(polygon.contains(QcVectorDouble(12, 11)) == false);
  QVERIFY(polygon.contains(QcVectorDouble(17, 3)) == true);
}

void
TestQcPolygon::intersec_with_grid()
{
  QVector<double> vertexes = {
    1.2, 1.2,
    0.2, 5.2,
    2.2, 7.2,
    5.2, 2.2,
    7.2, 8.2,
    10.2, 8.2,
    13.2, 10.2,
    15.2, 7.2,
    18.2, 6.2,
    18.2, 4.2,
    15.2, 3.2,
  };
  QcPolygon polygon(vertexes);
  double grid_step = 1.;
  QcTiledPolygon tiled_polygon = polygon.intersec_with_grid(grid_step);

  QVector<int> run_data({
      1, 1, 6,
      2, 0, 13,
      3, 0, 17,
      4, 0, 18,
      5, 0, 3,
      5, 6, 18,
      6, 0, 2,
      6, 6, 18,
      7, 1, 2,
      7, 6, 15,
      8, 7, 14,
      9, 11, 13,
      10, 12, 13
      });
  size_t i = 0;
  for (const QcTiledPolygonRun & run: tiled_polygon.runs()) {
    size_t j = 3*i;
    int y = run_data[j];
    QcIntervalInt interval(run_data[j+1], run_data[j+2]);
    QVERIFY(run == QcTiledPolygonRun(y, interval));
    i++;
  }
}

/***************************************************************************************************/

QTEST_MAIN(TestQcPolygon)
#include "test_polygon.moc"
