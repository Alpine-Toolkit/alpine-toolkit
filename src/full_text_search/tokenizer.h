// -*- mode: c++ -*-
/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the QtCarto library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $QTCARTO_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

/**************************************************************************************************/

#include "full_text_search/text_document.h"
#include "full_text_search/language.h"
#include "full_text_search/stemmer.h"
#include "full_text_search/token.h"

#include <QJsonArray>
#include <QHash>
#include <QList>
#include <QSet>
#include <QSharedPointer>
#include <QString>

/**************************************************************************************************/

class TokenizedTextDocument : public LocalizedDocument
{
public:
  TokenizedTextDocument();
  TokenizedTextDocument(LanguageCode language);
  TokenizedTextDocument(const TokenizedTextDocument & other);
  ~TokenizedTextDocument();

  TokenizedTextDocument & operator=(const TokenizedTextDocument & other);

  bool operator==(const TokenizedTextDocument & other) const;

  void append(const Token & token);
  TokenizedTextDocument & operator<<(const Token & token) {
    append(token);
    return *this;
  }

  // TokenList::iterator begin() { return m_tokens.begin(); }
  // TokenList::iterator end() { return m_tokens.end(); }
  TokenList::const_iterator begin() const { return m_tokens.cbegin(); }
  TokenList::const_iterator end() const { return m_tokens.cend(); }
  // TokenList::const_iterator cbegin() const { return m_tokens.cbegin(); }
  // TokenList::const_iterator cend() const { return m_tokens.cend(); }

  int size() const { return m_tokens.size(); }

private:
  TokenList m_tokens;
};

/**************************************************************************************************/

// Morphology: paragraph, line, word tokenizer

class WordTokenizer
{
public:
  typedef QSharedPointer<WordTokenizer> WordTokenizerPtr;

public:
  WordTokenizer() {}
  ~WordTokenizer() {}

  virtual TokenizedTextDocument process(const TextDocument & document) const;
};

/**************************************************************************************************/

class TokenFilterTraits
{
public:
  typedef QSharedPointer<TokenFilterTraits> FilterPtr;
  typedef QList<FilterPtr> FilterList;

public:
  virtual TokenizedTextDocument process(const TokenizedTextDocument & document) const = 0;
};

/**************************************************************************************************/

class LanguageFilter : public TokenFilterTraits
{
public:
  typedef TokenFilterTraits::FilterPtr FilterPtr;
  typedef QHash<LanguageCode, FilterPtr> FilterMap;

public:
  LanguageFilter();
  ~LanguageFilter();

  FilterPtr language_filter(const LanguageCode & language);
  void add_language_filter(const LanguageCode & language, const FilterPtr & filter);
  void add_language_filter(const LanguageCode & language, TokenFilterTraits * filter) {
    add_language_filter(language, FilterPtr(filter));
  }

  TokenizedTextDocument process(const TokenizedTextDocument & document) const;

private:
  FilterMap m_filters;
};

/**************************************************************************************************/

class WordFilterTraits : public TokenFilterTraits
{
public:
  WordFilterTraits() {}
  ~WordFilterTraits() {}

  TokenizedTextDocument process(const TokenizedTextDocument & document) const;

  virtual Token process(const Token & token) const = 0;
};

/**************************************************************************************************/

class StopWordFilter : public TokenFilterTraits
{
private:
  typedef QSet<QString> WordSet;

public:
  StopWordFilter();
  StopWordFilter(const QJsonArray & json_data);
  StopWordFilter(const QStringList & words);
  ~StopWordFilter();

  TokenizedTextDocument process(const TokenizedTextDocument & document) const;

  const WordSet & stop_words() const { return m_stop_words; }

  void add_stop_word(const QString & word);
  void add_stop_words(const QStringList & words);
  void set_stop_words(const QStringList & words);

  bool is_stop_words(const Token & token) const {
    return m_stop_words.contains(token.value());
  }

private:
  WordSet m_stop_words;
};

/**************************************************************************************************/

class Tokenizer
{
public:
  typedef WordTokenizer::WordTokenizerPtr WordTokenizerPtr;
  typedef TokenFilterTraits::FilterPtr FilterPtr;
  typedef TokenFilterTraits::FilterList FilterList;

public:
  Tokenizer(WordTokenizer * word_tokenizer = nullptr);
  Tokenizer(const Tokenizer & other);
  ~Tokenizer();

  Tokenizer & operator=(const Tokenizer & other);

  void set_word_tokenizer(WordTokenizer * word_tokenizer) { m_word_tokenizer = WordTokenizerPtr(word_tokenizer); };

  void add_filter(TokenFilterTraits * filter);
  Tokenizer & operator<<(TokenFilterTraits * filter);

  TokenizedTextDocument process(const TextDocument & document) const;

private:
  WordTokenizerPtr m_word_tokenizer = nullptr;
  FilterList m_filters;
};

/**************************************************************************************************/

// Fixme: LowerCaseFilter ???

class CaseFoldingFilter : public WordFilterTraits
{
public:
  using WordFilterTraits::WordFilterTraits;

  Token process(const Token & token) const {
    return token.to_lower_case();
  }
};

/**************************************************************************************************/

// Fixme: AsciiFolding

class AccentFoldingFilter : public WordFilterTraits
{
public:
  using WordFilterTraits::WordFilterTraits;

  Token process(const Token & token) const {
    return token.ascii_folding();
  }
};

/**************************************************************************************************/

class EnglishFilter : public WordFilterTraits
{
public:
  using WordFilterTraits::WordFilterTraits;

  Token process(const Token & token) const;

private:
  QString strip_possessive(const QString & word) const;
};

/**************************************************************************************************/

class FrenchFilter : public WordFilterTraits
{
public:
  using WordFilterTraits::WordFilterTraits;

  Token process(const Token & token) const;

private:
  QString strip_elision(const QString & word) const;
};

/**************************************************************************************************/

class PreLanguageFilter : public LanguageFilter
{
public:
  PreLanguageFilter();
};

/**************************************************************************************************/

class LocalizedStopWordFilter : public LanguageFilter
{
public:
  LocalizedStopWordFilter();
  LocalizedStopWordFilter(const QString & json_path);
};

/**************************************************************************************************/

class StemmerFilter : public WordFilterTraits
{
public:
  StemmerFilter(const LanguageCode & language);

  Token process(const Token & token) const;

private:
  Stemmer m_stemmer;
};

/**************************************************************************************************/

class LocalizedStemmerFilter : public LanguageFilter
{
public:
  LocalizedStemmerFilter();
};

/**************************************************************************************************/

#endif /* __TOKENIZER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
