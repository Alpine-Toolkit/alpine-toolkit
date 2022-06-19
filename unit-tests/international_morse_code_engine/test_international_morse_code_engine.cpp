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

#include <QDateTime>

/**************************************************************************************************/

#include "international_morse_code_engine/international_morse_code_engine.h"

/***************************************************************************************************/

class TestInternationalMorseCodeEngine: public QObject
{
  Q_OBJECT

private slots:
  void test_morse_code_engine();
};

void
TestInternationalMorseCodeEngine::test_morse_code_engine()
{
  InternationalMorseCodeEngine morse_code_engine;
  QString message("hello morse");
  QString encoded_message = morse_code_engine.encode(message);
  qInfo() << message << encoded_message;
  qInfo() << morse_code_engine.encode(message, true);
  qInfo() << morse_code_engine.encode(message, true, true);
  bool succeed = false;
  QString message_back = morse_code_engine.decode(encoded_message, succeed);
  qInfo() << message_back;
  qInfo() << morse_code_engine.decode(" // ", succeed);
  qInfo() << morse_code_engine.decode(" // /", succeed);
}

/***************************************************************************************************/

QTEST_MAIN(TestInternationalMorseCodeEngine)
#include "test_international_morse_code_engine.moc"
