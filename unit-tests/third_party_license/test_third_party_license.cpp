/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
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
** $ALPINE_TOOLKIT_END_LICENSE$
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
  QString json_path("../ressources/data/third_party_licenses.json");
  ThirdPartyLicenseSchemaManager third_party_license_schema_manager(json_path);

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

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
