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
  QString json_path("../resources/data/ffcam-refuges.json");
  RefugeSchemaManager refuge_schema_manager(json_path);

  refuge_schema_manager.to_json("ffcam-refuges.json");

  for (const auto & refuge : refuge_schema_manager.refuges()) {
    qInfo() << refuge << refuge->first_letter();
  }

  // refuge_schema_manager.to_sql("ffcam-refuge.sqlite");
  refuge_schema_manager.from_sql("ffcam-refuge.sqlite");
}

/***************************************************************************************************/

QTEST_MAIN(TestRefugeSchemaManager)
#include "test_refuge.moc"
