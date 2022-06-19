/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include <QSignalSpy>
#include <QtTest/QtTest>

/**************************************************************************************************/

#include "document/document.h"

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
  QVariantHash variant_hash;
  variant_hash["id"] = "1"; // Should be read-only !
  variant_hash["name"] = "ffcam-refuges.json";
  variant_hash["author"] = "Fabrice Salvaire";
  variant_hash["version"] = 1;
  variant_hash["date"] = "2017-04-21T18:28:11Z";
  variant_hash["description"] = "Base de données des refuges FFCAM";
  variant_hash["url"] = "filer_public/ef/c7/efc713f4-e797-458c-9844-9bc3ae8fe3eb/ffcam-refuges.json";
  variant_hash["size"] = 74840;

  // QJsonParseError parse_error;
  // QJsonDocument json_document = QJsonDocument::fromJson(json_data, &parse_error);
  // if (parse_error.error != QJsonParseError::NoError)
  //   qCritical() << parse_error.errorString();

  Document document_from_variant_hash(variant_hash);
  qInfo() << document_from_variant_hash;
  QVariantHash bootstraped_variant_hash = document_from_variant_hash.to_variant_hash();
  // qInfo() << bootstraped_variant_hash;
  // QVERIFY(bootstraped_variant_hash == variant_hash); // fail ???
  for (const auto & key : variant_hash.keys())
    QVERIFY(variant_hash[key] == bootstraped_variant_hash[key]);

  QJsonDocument json_document = QJsonDocument::fromVariant(variant_hash);
  qInfo() << json_document.toJson();
  Document document_from_json(json_document.object());
  QJsonObject json_object = document_from_json.to_json();
  QJsonDocument bootstraped_json_document = QJsonDocument(json_object);
  qInfo() << bootstraped_json_document.toJson();
  Document bootstraped_document(json_object);
  QVERIFY(bootstraped_document == document_from_json);

  Document document_from_list(document_from_json.to_variant_list());
  QVERIFY(document_from_list == document_from_json);

  Document document_copy(document_from_json);
  Document document_copy_2 = document_from_json;
  QVERIFY(document_copy == document_from_json);
  QVERIFY(document_copy_2 == document_from_json);

  Document document(document_from_variant_hash);
  QVERIFY(document.is_name_modified() == false);
  QString name = "John Doe";
  document.set_name(name);
  QVERIFY(document.name() == name);
  QVERIFY(document.is_name_modified() == true);
  qInfo() << document.to_variant_hash(true);
  qInfo() << document.to_json(true);
}

/***************************************************************************************************/

QTEST_MAIN(TestDocument)
#include "test_document.moc"
