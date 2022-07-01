/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
