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
  QString message_back = morse_code_engine.decode(encoded_message);
  qInfo() << message_back;
  qInfo() << morse_code_engine.decode(" // ");
  qInfo() << morse_code_engine.decode(" // /");
}

/***************************************************************************************************/

QTEST_MAIN(TestInternationalMorseCodeEngine)
#include "test_international_morse_code_engine.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
