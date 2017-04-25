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

/**************************************************************************************************/

#include "settings/settings_database.h"

/***************************************************************************************************/

class TestSettingsDatabase: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestSettingsDatabase::constructor()
{
  QString sqlite_path("settings_database.sqlite"); // Fixme:
  SqliteSettingsDatabase settings_database(sqlite_path);

  QVERIFY(settings_database.contains("foo") == false);
  QStringList keys;
  QString key1 = "key1";
  QString key2 = "d1/key2";
  QString key3 = "d1/key3";
  QString key4 = "d1/d2/key4";
  keys << key1 << key2 << key3 << key4;
  int i = 0;
  for (const auto & key : keys)
    settings_database.set_value(key, ++i * 10);
  i = 0;
  for (const auto & key : keys) {
    QVERIFY(settings_database.contains(key) == true);
    QVERIFY(settings_database.value(key) == ++i * 10);
  }
  settings_database.set_value(key4, 100);
  QVERIFY(settings_database.value(key4) == 100);

  qInfo() << settings_database.keys("d1");
  SettingsDatabase::KeyValueMap key_values = settings_database.to_map();
  for (const auto & key : key_values.keys())
    qInfo() << key << key_values[key];
}

/***************************************************************************************************/

QTEST_MAIN(TestSettingsDatabase)
#include "test_settings_database.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
