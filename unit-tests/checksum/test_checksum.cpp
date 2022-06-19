/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include <QtTest/QtTest>

/**************************************************************************************************/

#include "checksum/checksum.h"

/***************************************************************************************************/

class TestQcChecksum: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestQcChecksum::constructor()
{
  // http://www.truetto.com

  {
    QVector<unsigned int> input = {5, 7, 2};
    QVERIFY(Checksum(input).damm() == 4);
  }
  {
    QVector<unsigned int> input = {6, 2, 9, 5};
    QVERIFY(Checksum(input).damm() == 2);
  }
}

/***************************************************************************************************/

QTEST_MAIN(TestQcChecksum)
#include "test_checksum.moc"
