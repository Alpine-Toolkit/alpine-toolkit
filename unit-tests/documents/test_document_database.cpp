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

#include <QFile>
#include <QJsonDocument>
#include <QtDebug>

/***************************************************************************************************/

class TestDocumentDatabase: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestDocumentDatabase::constructor()
{
  QString sqlite_path("document.sqlite"); // Fixme:
  QFile file(sqlite_path);
  if (file.exists())
    file.remove();
  DocumentDatabase document_database(sqlite_path);
  QcDatabaseTable * table = document_database.table();

  QVariantHash variant_hash;
  variant_hash["id"] = "1"; // Should be read-only !
  variant_hash["name"] = "ffcam-refuges.json";
  variant_hash["author"] = "Fabrice Salvaire";
  variant_hash["version"] = 1;
  variant_hash["date"] = "2017-04-21T18:28:11Z";
  variant_hash["description"] = "Base de données des refuges FFCAM";
  variant_hash["url"] = "filer_public/ef/c7/efc713f4-e797-458c-9844-9bc3ae8fe3eb/ffcam-refuges.json";
  variant_hash["size"] = 74840;

  Document document(variant_hash);
  table->insert(document.to_variant_hash(), true);
  QString name = "John Doe";
  document.set_name(name);
  QVariantHash where_kwargs;
  where_kwargs["id"] = document.id();
  // DocumentSchema::instance()[DocumentSchema::FieldPosition::ID].sql_name();
  table->update(document.to_variant_hash(true), where_kwargs);
}

/***************************************************************************************************/

QTEST_MAIN(TestDocumentDatabase)
#include "test_document_database.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
