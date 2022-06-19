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

#include "rrd/rrd.h"

#include <QString>
#include <QDataStream>
#include <QtDebug>

/**************************************************************************************************/

struct MyRoundRobinDatabaseSlot
{
  quint64 index;
  double x;
  double y;
};
typedef struct MyRoundRobinDatabaseSlot  MyRoundRobinDatabaseSlot;

class MyRoundRobinDatabase : public QcRoundRobinDatabase
{
public:
  MyRoundRobinDatabase(const QString & path)
    : QcRoundRobinDatabase(path)
  {}
  MyRoundRobinDatabase(const QString & path, size_t number_of_slots)
    : QcRoundRobinDatabase(path, QStringLiteral("qdd"), number_of_slots)
  {}

  void write (const MyRoundRobinDatabaseSlot & data) {
    QByteArray buffer;
    buffer.reserve(slot_size()); // Fixme: required?
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream << data.index << data.x << data.y;
    QcRoundRobinDatabase::write(buffer);
  }

  void read (size_t position, MyRoundRobinDatabaseSlot & data) {
    QByteArray buffer;
    buffer.resize(slot_size());
    QcRoundRobinDatabase::read(position, buffer);
    QDataStream stream(&buffer, QIODevice::ReadOnly);
    stream >> data.index >> data.x >> data.y;
  }
};

/***************************************************************************************************/

class TestQcRrd: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestQcRrd::constructor()
{
  QString path("test.rrd");

  size_t number_of_slots = 10;
  MyRoundRobinDatabase output_rrd(path, number_of_slots);
  size_t number_of_iterations = 15; // number_of_slots + 10;
  for (size_t i = 0; i < number_of_iterations; i++) {
    MyRoundRobinDatabaseSlot slot = { .index = i, .x = 1.1 * i, .y = 2.2 * i};
    output_rrd.write(slot);
  }
  output_rrd.flush();

  MyRoundRobinDatabase input_rrd(path);
  for (size_t i = 0; i < number_of_iterations; i++) {
    MyRoundRobinDatabaseSlot slot;
    output_rrd.read(i, slot);
    qInfo() << "@" << i << slot.index << slot.x << slot.y;
  }

  qInfo() << "Oldest to latest:" << input_rrd.oldest_position() << input_rrd.latest_position();
  for (size_t position : input_rrd)
    qInfo() << position;
}

/***************************************************************************************************/

QTEST_MAIN(TestQcRrd)
#include "test_rrd.moc"
