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

#include "full_text_search/indexer.h"

/**************************************************************************************************/

class TestIndexer: public QObject
{
  Q_OBJECT

private slots:
  void test();
  void test_phonetic();
};

void
TestIndexer::test()
{
  // Fixme: init ok ???
  TextDocumentIndexer<TextDocument> indexer; // new Tokenizer()

  Tokenizer & tokenizer = indexer.tokenizer();
  tokenizer << new PreLanguageFilter();
  tokenizer << new CaseFoldingFilter();
  tokenizer << new AccentFoldingFilter(); // Must run language filter before !
  tokenizer << new LocalizedStopWordFilter("../ressources/data/stop-words.json");
  tokenizer << new LocalizedStemmerFilter();

  QString text1 = "Wikipédia est un projet d’encyclopédie collective en ligne, universelle, multilingue et fonctionnant sur le principe du wiki. Wikipédia a pour objectif d’offrir un contenu librement réutilisable, objectif et vérifiable, que chacun peut modifier et améliorer.";
  auto document1 = QSharedPointer<TextDocument>(new TextDocument(QLocale::French, text1));
  indexer.insert(*document1, document1);
  qInfo() << text1;
  for (const auto & token : indexer.document_tokens(document1))
    qInfo() << token;

  QString text2 = "Because QMultiMap inherits QMap, all of QMap's functionality also applies to QMultiMap. For example, you can use isEmpty() to test whether the map is empty, and you can traverse a QMultiMap using QMap's iterator classes (for example, QMapIterator). But in addition, it provides an insert() function that corresponds to QMap::insertMulti(), and a replace() function that corresponds to QMap::insert(). It also provides convenient operator+() and operator+=().";
  auto document2 = QSharedPointer<TextDocument>(new TextDocument(QLocale::English, text2));
  indexer.insert(*document2, document2);
  qInfo() << text2;
  for (const auto & token : indexer.document_tokens(document2))
    qInfo() << token;

  QString text3 = "Wikipédia est une encyclopédie.";
  auto document3 = QSharedPointer<TextDocument>(new TextDocument(QLocale::French, text3));
  indexer.insert(*document3, document3);
  qInfo() << text3;
  for (const auto & token : indexer.document_tokens(document3))
    qInfo() << token;

  QString query_text = "Wikipédia projet";
  auto matches = indexer.query(TextDocument(QLocale::French, query_text));
  for (const auto & match : matches)
    qInfo() << query_text << "Matched" << match.pertinence() << match.document()->document();
}

void
TestIndexer::test_phonetic()
{
  TextDocumentIndexer<TextDocument> indexer(true);

  Tokenizer & tokenizer = indexer.tokenizer();
  tokenizer << new PreLanguageFilter();
  tokenizer << new CaseFoldingFilter();
  tokenizer << new AccentFoldingFilter(); // Must run language filter before !
  tokenizer << new LocalizedStopWordFilter("../ressources/data/stop-words.json");
  tokenizer << new LocalizedStemmerFilter();

  QString text1 = "Wikipédia est un projet d’encyclopédie collective en ligne, universelle, multilingue et fonctionnant sur le principe du wiki. Wikipédia a pour objectif d’offrir un contenu librement réutilisable, objectif et vérifiable, que chacun peut modifier et améliorer.";
  auto document1 = QSharedPointer<TextDocument>(new TextDocument(QLocale::French, text1));
  indexer.insert(*document1, document1);
  qInfo() << text1;
  for (const auto & token : indexer.tokens())
    qInfo() << token;
  for (const auto & token : indexer.phonetic_index()->tokens())
    qInfo() << token;
}

/***************************************************************************************************/

QTEST_MAIN(TestIndexer)
#include "test_indexer.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
