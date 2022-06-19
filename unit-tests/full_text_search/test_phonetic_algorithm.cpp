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
  PhoneticEncoder & phonetic_encoder = PhoneticEncoder::instance();

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
