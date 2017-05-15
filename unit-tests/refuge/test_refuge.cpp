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

#include "refuge/refuge_schema_manager.h"

/**************************************************************************************************/

class TestRefugeSchemaManager: public QObject
{
  Q_OBJECT

private slots:
  void test();
};

void
TestRefugeSchemaManager::test()
{
  QString json_path("../ressources/data/ffcam-refuges.json");
  RefugeSchemaManager refuge_schema_manager(json_path);

  refuge_schema_manager.to_json("ffcam-refuges.json");

  for (const auto & refuge : refuge_schema_manager.refuges()) {
    qInfo() << refuge << refuge->first_letter();
  }
}

/***************************************************************************************************/

QTEST_MAIN(TestRefugeSchemaManager)
#include "test_refuge.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
