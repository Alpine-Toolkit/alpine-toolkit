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

#include <QSignalSpy>
#include <QtTest/QtTest>

/**************************************************************************************************/

#include "document/document_database.h"

#include <QJsonDocument>
#include <QtDebug>

/***************************************************************************************************/

class TestDocument: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestDocument::constructor()
{
  QVariantMap variant_map;
  variant_map["name"] = "ffcam-refuges.json";
  variant_map["author"] = "Fabrice Salvaire";
  variant_map["version"] = 1;
  variant_map["date"] = "2017-04-21T18:28:11Z";
  variant_map["description"] = "Base de données des refuges FFCAM";
  variant_map["url"] = "filer_public/ef/c7/efc713f4-e797-458c-9844-9bc3ae8fe3eb/ffcam-refuges.json";
  variant_map["size"] = 74840;

  // QJsonParseError parse_error;
  // QJsonDocument json_document = QJsonDocument::fromJson(json_data, &parse_error);
  // if (parse_error.error != QJsonParseError::NoError)
  //   qCritical() << parse_error.errorString();

  Document document_from_variant_map(variant_map);
  qInfo() << document_from_variant_map;
  QVariantMap bootstraped_variant_map = document_from_variant_map.to_variant_map();
  // qInfo() << bootstraped_variant_map;
  // QVERIFY(bootstraped_variant_map == variant_map); // fail ???
  for (const auto & key : variant_map.keys())
    QVERIFY(variant_map[key] == bootstraped_variant_map[key]);

  QJsonDocument json_document = QJsonDocument::fromVariant(variant_map);
  qInfo() << json_document.toJson();
  Document document_from_json(json_document.object());
  QJsonObject json_object = document_from_json.to_json();
  QJsonDocument bootstraped_json_document = QJsonDocument(json_object);
  qInfo() << bootstraped_json_document.toJson();
  Document bootstraped_document(json_object);
  QVERIFY(bootstraped_document == document_from_json);

  Document document_copy(document_from_json);
  Document document_copy_2 = document_from_json;
  QVERIFY(document_copy == document_from_json);
  QVERIFY(document_copy_2 == document_from_json);

  Document document(document_from_variant_map);
  QVERIFY(document.is_name_modified() == false);
  QString name = "John Doe";
  document.set_name(name);
  QVERIFY(document.name() == name);
  QVERIFY(document.is_name_modified() == true);
  qInfo() << document.to_variant_map(true);
  qInfo() << document.to_json(true);
}

/***************************************************************************************************/

QTEST_MAIN(TestDocument)
#include "test_document.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
