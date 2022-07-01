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

#include "geometry/line.h"

/***************************************************************************************************/

class TestQcLine: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestQcLine::constructor()
{
  QcLineDouble line1(QcVectorDouble(1., 10.), QcVectorDouble(2., 3.));

  const QcVectorDouble & point = line1.point();
  QVERIFY(point.x() == 1.);
  QVERIFY(point.y() == 10.);
  const QcVectorDouble & vector = line1.vector();
  QVERIFY(vector.x() == 2.);
  QVERIFY(vector.y() == 3.);
}

/***************************************************************************************************/

QTEST_MAIN(TestQcLine)
#include "test_line.moc"
