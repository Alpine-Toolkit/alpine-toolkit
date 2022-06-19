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

/**************************************************************************************************/

#include "full_text_search/stemmer.h"

#include <QPair>

/**************************************************************************************************/

class TestStemmer: public QObject
{
  Q_OBJECT

private slots:
  void test();
};

void
TestStemmer::test()
{
  Stemmer stemmer(QLocale::French);

  // Fixme:
  // QPair<QString, QString> word_pairs = {
  //   { "continu",                    "continu" },
  // };

  QStringList word_pairs = {
    "continu",                    "continu",
    "continua",                   "continu",
    "continuait",                 "continu",
    "continuant",                 "continu",
    "continuation",               "continu",
    "continue",                   "continu",
    "continué",                   "continu",
    "continuel",                  "continuel",
    "continuelle",                "continuel",
    "continuellement",            "continuel",
    "continuelles",               "continuel",
    "continuels",                 "continuel",
    "continuer",                  "continu",
    "continuera",                 "continu",
    "continuerait",               "continu",
    "continueront",               "continu",
    "continuez",                  "continu",
    "continuité",                 "continu",
    "continuons",                 "continuon",
    "contorsions",                "contors",
    "contour",                    "contour",
    "contournait",                "contourn",
    "contournant",                "contourn",
    "contourne",                  "contourn",
    "contours",                   "contour",
    "contractait",                "contract",
    "contracté",                  "contract",
    "contractée",                 "contract",
    "contracter",                 "contract",
    "contractés",                 "contract",
    "contractions",               "contract",
    "contradictoirement",         "contradictoir",
    "contradictoires",            "contradictoir",
    "contraindre",                "contraindr",
    "contraint",                  "contraint",
    "contrainte",                 "contraint",
    "contraintes",                "contraint",
    "contraire",                  "contrair",
    "contraires",                 "contrair",
    "contraria",                  "contrari",
    "main",                       "main",
    "mains",                      "main",
    "maintenaient",               "mainten",
    "maintenait",                 "mainten",
    "maintenant",                 "mainten",
    "maintenir",                  "mainten",
    "maintenue",                  "maintenu",
    "maintien",                   "maintien",
    "maintint",                   "maintint",
    "maire",                      "mair",
    "maires",                     "mair",
    "mairie",                     "mair",
    "mais",                       "mais",
     // Wrong: "maïs",                       "maï",
    "maison",                     "maison",
    "maisons",                    "maison",
    "maistre",                    "maistr",
    "maitre",                     "maitr",
    "maître",                     "maîtr",
    "maîtres",                    "maîtr",
    "maîtresse",                  "maîtress",
    "maîtresses",                 "maîtress",
    "majesté",                    "majest",
    "majestueuse",                "majestu",
    "majestueusement",            "majestu",
    "majestueux",                 "majestu",
    "majeur",                     "majeur",
    "majeure",                    "majeur",
    "major",                      "major",
    "majordome",                  "majordom",
    "majordomes",                 "majordom",
    "majorité",                   "major",
    "majorités",                  "major",
    "mal",                        "mal",
    // ??? "malacca",                    "malacc",
    "malade",                     "malad",
    "malades",                    "malad",
    "maladie",                    "malad",
    "maladies",                   "malad",
    "maladive",                   "malad",
  };

  // for (const auto & pair : word_pairs) {
  //   QString input = pair.first();
  //   QString output_truth = pair.second();
  for (int i = 0; i < word_pairs.size() / 2; ++i) {
    int j = 2*i;
    QString input = word_pairs[j];
    QString output_truth = word_pairs[j + 1];
    QString output = stemmer.process(input);
    qInfo() << input << "->" << output << "/" << output_truth;
    QVERIFY(output == output_truth);
  }
}

/***************************************************************************************************/

QTEST_MAIN(TestStemmer)
#include "test_stemmer.moc"
