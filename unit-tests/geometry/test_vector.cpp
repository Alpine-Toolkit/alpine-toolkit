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

#include "geometry/vector.h"

/***************************************************************************************************/

class TestQcVector: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestQcVector::constructor()
{
  QcVectorDouble vector1(1., 10.);

  QVERIFY(vector1.x() == 1.);
  QVERIFY(vector1.y() == 10.);
}

/***************************************************************************************************/

QTEST_MAIN(TestQcVector)
#include "test_vector.moc"
