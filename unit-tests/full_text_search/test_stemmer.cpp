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

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
