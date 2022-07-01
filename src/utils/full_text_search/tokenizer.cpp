/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "tokenizer.h"
#include "alpine_toolkit.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLocale>
#include <QRegularExpression>
#include <QTextBoundaryFinder>
#include <QtDebug>

/**************************************************************************************************/

TokenizedTextDocument::TokenizedTextDocument()
  : LocalizedDocument(),
    m_tokens()
{}

TokenizedTextDocument::TokenizedTextDocument(LanguageCode language)
  : LocalizedDocument(language),
    m_tokens()
{}

TokenizedTextDocument::TokenizedTextDocument(const TokenizedTextDocument & other)
  : LocalizedDocument(other),
    m_tokens(other.m_tokens)
{}

TokenizedTextDocument::~TokenizedTextDocument()
{}

TokenizedTextDocument &
TokenizedTextDocument::operator=(const TokenizedTextDocument & other)
{
  if (this != &other) {
    LocalizedDocument::operator=(other);
    m_tokens = other.m_tokens;
  }

  return *this;
}

bool
TokenizedTextDocument::operator==(const TokenizedTextDocument & other) const
{
  return LocalizedDocument::operator==(other) and
    m_tokens == other.m_tokens;
}

void
TokenizedTextDocument::append(const Token & token)
{
  if (token)
    m_tokens.append(token);
}

/**************************************************************************************************/

TokenizedTextDocument
WordTokenizer::process(const TextDocument & document) const
{
  // http://unicode.org/reports/tr29/ :  Unicode Standard Annex #29 — Unicode Text Segmentation

  const QString & input = document.document(); // Fixme: name
  TokenizedTextDocument output(document.language());
  QTextBoundaryFinder boundary_finder(QTextBoundaryFinder::Word, input);

  int index = 0;
  int next_index = -1;
  while ((next_index = boundary_finder.toNextBoundary()) != -1) {
    QStringRef word(&input, index, next_index - index);
    Token token(word);
    if (token.has_letter())
      output << token;
    index = next_index;
  }

  return output;
}

/**************************************************************************************************/

TokenizedTextDocument
WordFilterTraits::process(const TokenizedTextDocument & document) const
{
  TokenizedTextDocument output(document.language());

  for (const auto & token : document)
    output << process(token);

  return output;
}

/**************************************************************************************************/

StopWordFilter::StopWordFilter()
  : m_stop_words()
{}

StopWordFilter::StopWordFilter(const QStringList & words)
  : StopWordFilter()
{
  add_stop_words(words);
}

StopWordFilter::StopWordFilter(const QJsonArray & json_data)
{
  for (const auto & item : json_data)
    add_stop_word(item.toString());
}

StopWordFilter::~StopWordFilter()
{}

TokenizedTextDocument
StopWordFilter::process(const TokenizedTextDocument & document) const
{
  TokenizedTextDocument output(document.language());

  for (const auto & token : document)
    if (not is_stop_words(token))
        output << token;

  return output;
}

void
StopWordFilter::add_stop_word(const QString & word)
{
  // Fixme: ???
  QString without_accent = Token(word).ascii_folding().value();
  m_stop_words << word;
  m_stop_words << without_accent;
}

void
StopWordFilter::add_stop_words(const QStringList & words)
{
  for (const auto & word : words)
    add_stop_word(word);
}

void
StopWordFilter::set_stop_words(const QStringList & words)
{
  m_stop_words.clear();
  add_stop_words(words);
}

/**************************************************************************************************/

LanguageFilter::LanguageFilter()
  : m_filters()
{}

LanguageFilter::~LanguageFilter()
{}

LanguageFilter::FilterPtr
LanguageFilter::language_filter(const LanguageCode & language)
{
  return m_filters.contains(language) ?
    m_filters[language] : FilterPtr();
}

void
LanguageFilter::add_language_filter(const LanguageCode & language, const FilterPtr & filter)
{
  m_filters[language] = filter;
}

TokenizedTextDocument
LanguageFilter::process(const TokenizedTextDocument & document) const
{
  const LanguageCode language = document.language();
  if (m_filters.contains(language)) {
    FilterPtr filter = m_filters[language];
    // qATInfo() << "LanguageFilter for " << language;
    return filter->process(document);
  } else
    return document;
}

/**************************************************************************************************/

TokenizerPipe::TokenizerPipe()
  : m_filters()
{
}

TokenizerPipe::TokenizerPipe(const TokenizerPipe & other)
  : m_filters(other.m_filters)
{}

TokenizerPipe::~TokenizerPipe()
{}

TokenizerPipe &
TokenizerPipe::operator=(const TokenizerPipe & other)
{
  if (this != &other) {
    m_filters = other.m_filters;
  }

  return *this;
}

void
TokenizerPipe::add_filter(TokenFilterTraits * filter)
{
  m_filters << FilterPtr(filter);
}

TokenizerPipe &
TokenizerPipe::operator<<(TokenFilterTraits * filter)
{
  add_filter(filter);
  return *this;
}

TokenizedTextDocument
TokenizerPipe::process(const TokenizedTextDocument & document) const
{
  TokenizedTextDocument output;

  bool is_input = true;
  for (const auto & filter : m_filters) {
    output = filter->process(is_input ? document : output);
    is_input = false;
  }

  return output;
}

/**************************************************************************************************/

Tokenizer::Tokenizer(WordTokenizer * word_tokenizer)
  : m_word_tokenizer(nullptr),
    m_pipe()
{
  if (word_tokenizer == nullptr)
    m_word_tokenizer = WordTokenizerPtr(new WordTokenizer());
}

Tokenizer::Tokenizer(const Tokenizer & other)
  : m_word_tokenizer(other.m_word_tokenizer),
    m_pipe(other.m_pipe)
{}

Tokenizer::~Tokenizer()
{}

Tokenizer &
Tokenizer::operator=(const Tokenizer & other)
{
  if (this != &other) {
    m_word_tokenizer = other.m_word_tokenizer;
    m_pipe = other.m_pipe;
  }

  return *this;
}

void
Tokenizer::add_filter(TokenFilterTraits * filter)
{
  m_pipe.add_filter(filter);
}

Tokenizer &
Tokenizer::operator<<(TokenFilterTraits * filter)
{
  add_filter(filter);
  return *this;
}

TokenizedTextDocument
Tokenizer::process(const TextDocument & document) const
{
  TokenizedTextDocument output = m_word_tokenizer->process(document);
  return  m_pipe.process(output);
}

/**************************************************************************************************/

Token
EnglishFilter::process(const Token & token) const
{
  if (token.has_other()) {
    const QString & input = token.value();
    QString output = strip_possessive(input);
    return Token(output);
  } else
    return token;
}

QString
EnglishFilter::strip_possessive(const QString & word) const
{
  // Strip right part before the first elision sign
  QChar form1 = '\''; // John's
  QChar form2(0x2019); // John’s RIGHT SINGLE QUOTATION MARK
  int position1 = word.lastIndexOf(form1);
  int position2 = word.lastIndexOf(form2);
  int position = qMin(position1, position2);
    if (position != -1)
      return word.left(position);
    else
      return word;
}

/**************************************************************************************************/

Token
FrenchFilter::process(const Token & token) const
{
  if (token.has_other()) {
    const QString & input = token.value();
    QString output = strip_elision(input);
    return Token(output);
  } else
    return token;
}

QString
FrenchFilter::strip_elision(const QString & word) const
{
  // Fixme: add part ???

  // Fixme: can normalize ’ to '
  // Strip left part before the last elision sign
  QChar form1 = '\''; // L'élision
  QChar form2(0x2019); // L’élision RIGHT SINGLE QUOTATION MARK
  int position1 = word.lastIndexOf(form1);
  int position2 = word.lastIndexOf(form2);
  int position = qMax(position1, position2);
  // qATInfo() << "FrenchFilter elision" << word << position;
  if (position != -1)
    return word.mid(position);
  else
    return word;
}

/**************************************************************************************************/

PreLanguageFilter::PreLanguageFilter()
  : LanguageFilter()
{
  add_language_filter(LanguageCode::French, new FrenchFilter());
  add_language_filter(LanguageCode::English, new EnglishFilter());
}

/**************************************************************************************************/

LocalizedStopWordFilter::LocalizedStopWordFilter()
  : LanguageFilter()
{}

LocalizedStopWordFilter::LocalizedStopWordFilter(const QString & json_path)
  : LanguageFilter()
{
  // Fixme: singleton

  QFile json_file(json_path);

  if (json_file.open(QIODevice::ReadOnly)) {
    QByteArray json_data = json_file.readAll();
    QJsonParseError parse_error;
    QJsonDocument json_document = QJsonDocument::fromJson(json_data, &parse_error);
    if (parse_error.error == QJsonParseError::NoError) {
      // Keys are ISO 639-1 language code
      QJsonObject root = json_document.object();
      for (const auto & iso_language : root.keys()) {
        QLocale language(iso_language);
        FilterPtr filter(new StopWordFilter(root[iso_language].toArray()));
        add_language_filter(language.language(), filter);
      }
    }
    else
      qATCritical() << parse_error.errorString();
  } else {
    qATCritical() << QStringLiteral("Couldn't open file") << json_path;
    // throw std::invalid_argument("Couldn't open file."); // Fixme: ???
  }
}

/**************************************************************************************************/

StemmerFilter::StemmerFilter(const LanguageCode & language)
  : m_stemmer(language)
{}

Token
StemmerFilter::process(const Token & token) const
{
  QString output = m_stemmer.process(token.value());
  // qATInfo() << token << "->" << output;
  return Token(output);
}

/**************************************************************************************************/

LocalizedStemmerFilter::LocalizedStemmerFilter()
  : LanguageFilter()
{
  for (const auto & language : Stemmer::available_languages()) {
    // qATInfo() << "Add stemmer filter for" << language;
    add_language_filter(language, new StemmerFilter(language));
  }
}

/**************************************************************************************************/

PhoneticFilter::PhoneticFilter(const LanguageCode & language)
  : m_language(language)
{}

Token
PhoneticFilter::process(const Token & token) const
{
  PhoneticEncoder & phonetic_encoder = PhoneticEncoder::instance();
  QString output = phonetic_encoder.soundex(m_language, token);
  // qATInfo() << token << "->" << output;
  return Token(output);
}

/**************************************************************************************************/

LocalizedPhoneticFilter::LocalizedPhoneticFilter()
  : LanguageFilter()
{
  // Fixme:: better ?
  add_language_filter(QLocale::English, new PhoneticFilter(QLocale::English));
  add_language_filter(QLocale::French, new PhoneticFilter(QLocale::French));
}
