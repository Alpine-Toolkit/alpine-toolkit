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

#include <QFile>
#include <QSet>
#include <QtDebug>

/**************************************************************************************************/

#include "settings/settings_database.h"

/***************************************************************************************************/

class TestSettingsDatabase: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
  void verify_string_list(const QStringList & list1, const QStringList & list2);
};

void TestSettingsDatabase::constructor()
{
  QString sqlite_path("settings_database.sqlite"); // Fixme:
  QFile file(sqlite_path);
  if (file.exists())
    file.remove();
  SqliteSettingsDatabase settings_database(sqlite_path);

  // Check non existing key
  QVERIFY(settings_database.contains("foo") == false);
  QVERIFY(settings_database.value("foo").isValid() == false);

  // Insert keys and check
  QStringList keys;
  QString key1 = "key1"; // p = 0
  QString key2 = "d1/key2"; // p = 1
  QString key3 = "d1/key3"; // p = 1
  QString key4 = "d1/d2/key4"; // p = 2
  QString key5 = "d1/d2/key5"; // p = 2
  QString key6 = "d1/d2/d3/key6"; // p = 3
  QString key1bis = "d1/key1"; // p = 1
  keys << key1 << key2 << key3 << key4 << key5 << key6 << key1bis;
  int i = 0;
  for (const auto & key : keys)
    settings_database.set_value(key, ++i * 10);
  i = 0;
  for (const auto & key : keys) {
    QVERIFY(settings_database.contains(key) == true);
    QVERIFY(settings_database.value(key) == ++i * 10);
  }

  // Update a key
  settings_database.set_value(key4, 100);
  QVERIFY(settings_database.value(key4) == 100);

  // Keys in directory
  QStringList directory_keys;
  directory_keys << "key1";
  verify_string_list(settings_database.keys("/"), directory_keys);
  directory_keys.clear();
  directory_keys << "key2" << "key3" << "key1";
  verify_string_list(settings_database.keys("/d1"), directory_keys);
  directory_keys.clear();
  directory_keys << "key4" << "key5";
  verify_string_list(settings_database.keys("/d1/d2"), directory_keys);
  directory_keys.clear();
  directory_keys << "key6";
  verify_string_list(settings_database.keys("/d1/d2/d3"), directory_keys);

  QVERIFY(settings_database.keys("/foo").isEmpty());

  settings_database.load();
  SettingsDatabase::KeyValueMap key_values = settings_database.cache();
  for (const auto & key : key_values.keys())
    qInfo() << key << key_values[key];

  settings_database.remove(key1bis);
  QVERIFY(settings_database.contains(key1bis) == false);

  qInfo() << "To JSON";
  qInfo() << settings_database.to_json_document();

  // Check counts
  QVERIFY(settings_database.number_of_directories() == 3);
  QVERIFY(settings_database.number_of_keys() == keys.size() - 1);
}

void
TestSettingsDatabase::verify_string_list(const QStringList & list1, const QStringList & list2)
{
  QSet<QString> set1 = QSet<QString>::fromList(list1);
  QSet<QString> set2 = QSet<QString>::fromList(list2);
  QVERIFY(set1 == set2);
}

/***************************************************************************************************/

QTEST_MAIN(TestSettingsDatabase)
#include "test_settings_database.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
