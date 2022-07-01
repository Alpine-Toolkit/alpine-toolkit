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

#include "math/interval.h"

/***************************************************************************************************/

class TestQcInterval: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestQcInterval::constructor()
{
  QcIntervalInt interval1(1, 10);
  QcIntervalInt interval2(2, 20);

  QVERIFY(interval1.inf() == 1);
  QVERIFY(interval1.sup() == 10);
}

/***************************************************************************************************/

QTEST_MAIN(TestQcInterval)
#include "test_interval.moc"
