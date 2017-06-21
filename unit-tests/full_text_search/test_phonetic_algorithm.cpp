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

/**************************************************************************************************/

#include "full_text_search/phonetic_encoder.h"

/***************************************************************************************************/

class TestPhoneticAlgorithm: public QObject
{
  Q_OBJECT

private slots:
  void test();
};

void TestPhoneticAlgorithm::test()
{
  PhoneticEncoder phonetic_encoder;

  QStringList word_pairs = {
    "Robert", "r163",
  };

  for (int i = 0; i < word_pairs.size() / 2; ++i) {
    int j = 2*i;
    QString input = word_pairs[j];
    QString output_truth = word_pairs[j + 1];
    QString output = phonetic_encoder.soundex_us(Token(input));
    qInfo() << input << "->" << output << "/" << output_truth;
    QVERIFY(output == output_truth);
  }
}

/***************************************************************************************************/

QTEST_MAIN(TestPhoneticAlgorithm)
#include "test_phonetic_algorithm.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
