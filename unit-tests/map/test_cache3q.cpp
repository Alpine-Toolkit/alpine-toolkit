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

#include "cache/cache3q.h"

/***************************************************************************************************/

class TestQcCache3Q: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

class MyObject: public QObject
{
  Q_OBJECT

public:
  MyObject(int value) : QObject(), value(value) {}

  int value;
};

void TestQcCache3Q::constructor()
{
  size_t number_of_items = 10;
  QcCache3Q<int, MyObject> cache(number_of_items, -1, -1);
  QVector<QSharedPointer<MyObject> > data_ptr(number_of_items);

  for (size_t i = 0; i < number_of_items; i++ ) {
    QSharedPointer<MyObject> shared_ptr(new MyObject(i));
    data_ptr[i] = shared_ptr;
    cache.insert(i, shared_ptr);
  }

  cache.print_stats();

  for (size_t i = 0; i < number_of_items; i++ ) {
    qInfo() << cache[i].data()->value;
    QVERIFY(cache[i].data()->value == data_ptr[i]->value);
  }

  QVERIFY(cache.total_cost() == number_of_items); // -Wsign-compare
  cache.remove(0);
  QVERIFY(cache.total_cost() == number_of_items - 1); // -Wsign-compare
  cache.clear();
  QVERIFY(cache.total_cost() == 0);
}

/***************************************************************************************************/

QTEST_MAIN(TestQcCache3Q)
#include "test_cache3q.moc"
