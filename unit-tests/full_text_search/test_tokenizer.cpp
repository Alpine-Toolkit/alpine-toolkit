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

#include "full_text_search/tokenizer.h"

/**************************************************************************************************/

class TestTokenizer: public QObject
{
  Q_OBJECT

private slots:
  void test();
};

void
TestTokenizer::test()
{
  Tokenizer tokenizer;
  tokenizer << new PreLanguageFilter();
  tokenizer << new CaseFoldingFilter();
  tokenizer << new AccentFoldingFilter(); // Must run language filter before !
  tokenizer << new LocalizedStopWordFilter("../ressources/data/stop-words.json");
  tokenizer << new LocalizedStemmerFilter();

  QString text = "Wikipédia est un projet d’encyclopédie collective en ligne, universelle, multilingue et fonctionnant sur le principe du wiki. Wikipédia a pour objectif d’offrir un contenu librement réutilisable, objectif et vérifiable, que chacun peut modifier et améliorer.";
  TextDocument document(QLocale::French, text);

  TokenizedTextDocument tokenized_document = tokenizer.process(document);
  for (const auto & token : tokenized_document)
    qInfo() << token;
}

/***************************************************************************************************/

QTEST_MAIN(TestTokenizer)
#include "test_tokenizer.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
