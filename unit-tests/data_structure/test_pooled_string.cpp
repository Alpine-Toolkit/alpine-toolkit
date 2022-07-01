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

#include "data_structure/pooled_string.h"

/***************************************************************************************************/

class TestQcPooledString: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void
TestQcPooledString::constructor()
{
  QcPooledString undefined_pooled_string;
  QVERIFY(undefined_pooled_string.reference_counter() == 0);

  QString string1("foo");
  QcPooledString pooled_string1(string1);
  QVERIFY(pooled_string1.reference_counter() == 1);
  QVERIFY(pooled_string1.id() == 1);
  QVERIFY(*pooled_string1 == string1);

  QcPooledString * pooled_string2 = new QcPooledString(string1);
  QVERIFY(pooled_string1.reference_counter() == 2);
  QVERIFY(pooled_string2->reference_counter() == 2);
  QVERIFY(pooled_string2->id() == 1);
  QVERIFY(pooled_string2->string() == string1);

  QString string3("bar");
  QcPooledString * pooled_string3 = new QcPooledString(string3);
  QVERIFY(pooled_string3->reference_counter() == 1);
  QVERIFY(pooled_string3->id() == 2);
  QVERIFY(pooled_string3->string() == string3);

  delete pooled_string2;
  QVERIFY(pooled_string1.reference_counter() == 1);

  delete pooled_string3;
  QVERIFY(QcPooledString::has_string(string3) == false);
}

/***************************************************************************************************/

QTEST_MAIN(TestQcPooledString)
#include "test_pooled_string.moc"
