/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the QtCarto library.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include <QtTest/QtTest>
#include <QtDebug>

/**************************************************************************************************/

#include "refuge.h"

/***************************************************************************************************/

class TestRefuge: public QObject
{
  Q_OBJECT

private slots:
  void test_refuge_ctor();
  void test_load_refuge_json();
};


void
TestRefuge::test_refuge_ctor()
{
  Refuge refuge;
  refuge.set_name("Écrin");
  refuge.set_coordinate(QGeoCoordinate(48.87, 2.67));
  qInfo() << refuge.name() << refuge.coordinate();
}

void
TestRefuge::test_load_refuge_json()
{
  QList<Refuge *> refuges;
  load_refuge_json("ffcam-refuges.json", refuges);
  for (const Refuge * refuge : refuges) {
    qInfo() << refuge->name();
  }
}

/***************************************************************************************************/

QTEST_MAIN(TestRefuge)
#include "test_refuge.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
