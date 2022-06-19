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
  tokenizer << new LocalizedStopWordFilter("../resources/data/stop-words.json");
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
