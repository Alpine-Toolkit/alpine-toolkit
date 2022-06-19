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

#include "third_party_license/third_party_license_schema_manager.h"

/**************************************************************************************************/

class TestThirdPartyLicenseSchemaManager: public QObject
{
  Q_OBJECT

private slots:
  void test();
};

void
TestThirdPartyLicenseSchemaManager::test()
{
  QString json_path("../resources/data/third_party_licenses.json");
  ThirdPartyLicenseSchemaManager third_party_license_schema_manager(json_path, true);

  third_party_license_schema_manager.load_json();

  third_party_license_schema_manager.to_json("third_party_licenses.json");

  for (const auto & third_party_license : third_party_license_schema_manager.third_party_licenses()) {
    qInfo() << third_party_license;
  }

  // third_party_license_schema_manager.to_sql("third_party_license.sqlite");
  // third_party_license_schema_manager.from_sql("third_party_license.sqlite");
}

/***************************************************************************************************/

QTEST_MAIN(TestThirdPartyLicenseSchemaManager)
#include "test_third_party_license.moc"
