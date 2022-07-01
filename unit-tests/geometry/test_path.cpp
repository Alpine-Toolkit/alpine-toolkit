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

#include "geometry/path.h"

/***************************************************************************************************/

class TestQcPath: public QObject
{
  Q_OBJECT

private slots:
  void length();
};

void
TestQcPath::length()
{
  double l = 10;

  {
    QcPathDouble path(QVector<double>({0, 0,   0, l,   l, l,   l, 0}), true);
    qInfo() << path.interval();
    for (const auto & vertex : path.vertexes())
      qInfo() << vertex;
    for (const auto & edge : path.edges())
      qInfo() << edge.p1() << edge.p2();
    QVERIFY(path.length() == 4*l);
  }

  {
    QcPath3DDouble path(QVector<double>({0, 0, 1,   0, l, 2,   l, l, 3,   l, 0, 4}), true);
    qInfo() << path.interval();
    for (const auto & vertex : path.vertexes())
      qInfo() << vertex;
    for (const auto & edge : path.edges())
      qInfo() << edge.p1() << edge.p2();
    QVERIFY(path.length() == 4*l);
  }
}

/***************************************************************************************************/

QTEST_MAIN(TestQcPath)
#include "test_path.moc"
