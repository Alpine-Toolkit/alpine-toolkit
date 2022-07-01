/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include <QtDebug>
#include <QtTest/QtTest>

/**************************************************************************************************/

#include "geometry/polygon_seidler_triangulation.h"

/***************************************************************************************************/

class TestQcTriangulation: public QObject
{
  Q_OBJECT

private slots:
  void triangulation();
};

void
TestQcTriangulation::triangulation()
{
  int number_of_vertexes = 7;
  int number_of_segments = 100;

  double vertices[number_of_vertexes][2] = {
     0.0,  0.0,
    10.0,  0.0,
    20.0,  0.0,
    20.0,  5.0,
    20.0, 20.0,
     0.0, 20.0,
    5.0,  10.0
  };

  int triangles[number_of_segments][3];
  for (int i = 0; i < number_of_segments; i++) {
    for (int j = 0; j < 3; j++)
      triangles[i][j] = 0;
  }

  QcSeidlerPolygonTriangulation triangulation(number_of_vertexes, vertices, triangles);
  // for (int i = 0; i < number_of_segments; i++)
  //   qInfo() << i << triangles[i][0] << triangles[i][1] << triangles[i][2];
}

/***************************************************************************************************/

QTEST_MAIN(TestQcTriangulation)
#include "test_triangulation.moc"
