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

#include "document/document_manager.h"

/***************************************************************************************************/

class TestDocumentManager: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestDocumentManager::constructor()
{
  QString api_url("http://127.0.0.1/api");
  DocumentManager document_manager(api_url, 8000);
  document_manager.get_document_list();
  QSignalSpy spy(&document_manager, &DocumentManager::received_document_list);
  QVERIFY(spy.wait(5000)); // ms
}

/***************************************************************************************************/

QTEST_MAIN(TestDocumentManager)
#include "test_document_manager.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
