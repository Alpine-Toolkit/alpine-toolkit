// -*- mode: c++ -*-
/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#ifndef __TOKEN_H__
#define __TOKEN_H__

/**************************************************************************************************/

#include "full_text_search/language.h"

#include <QChar>
#include <QHash>
#include <QString>
#include <QStringRef>

/**************************************************************************************************/

class CharTranslator
{
public:
  typedef QHash<QChar, QChar> TranslationMap;

public:
  CharTranslator();
  CharTranslator(const QString & input_chars, const QString & output_chars);
  CharTranslator(const QStringList & string_list); // used by soundex algorithm
  CharTranslator(const CharTranslator & other);
  ~CharTranslator();

  CharTranslator & operator=(const CharTranslator & other);

  QString translate(const QString & input) const;

private:
  TranslationMap m_map;
};

/**************************************************************************************************/

/* QString wrapper with an API for FTS
 *
 */
class Token
{
public:
  static QString remove_consecutive_char(const QString & input);

public:
  enum Category {
    Letter = 1,
    Number = 2,
    Hyphen = 4,
    Other  = 8,
  };

public:
  Token();
  Token(const Token & token);
  Token(const QString & string, int force_flags = 0);
  Token(const QStringRef & string, int force_flags = 0);
  ~Token();

  Token & operator=(const Token & other);
  Token & operator=(const QString & string);
  Token & operator=(const QStringRef & string);

  Token & operator<<(const QChar & c);
  void operator+=(const QChar & c);

  bool operator==(const Token & other) const;
  bool operator<(const Token & other) const; // QMap total order

  const QString & value() const { return m_string; }
  operator QString() const { return m_string; }
  QChar operator[](int i) const { return m_string[i]; }

  bool is_empty() const { return m_string.isEmpty(); }
  bool is_not_empty() const { return not is_empty(); }
  operator bool() const { return is_not_empty(); }

  int size() const { return m_string.size(); }

  bool has_letter() const { return m_flags & Letter; }
  bool has_number() const { return m_flags & Number; }
  bool has_hyphen() const { return m_flags & Hyphen; }
  bool has_other() const  { return m_flags & Other; }
  bool is_letter() const  { return m_flags == Letter; }
  bool is_number() const  { return m_flags == Number; }

  void clear();

  Token to_lower_case() const;
  Token to_upper_case() const;
  Token ascii_folding() const; // remove_ accent diacritic

  // Token remove(const QChar c) const { return Token(m_string.remove(c)); }
  // Token translate(const CharTranslator & translation_map);

  bool contains(const Token & other) const { return m_string.contains(other.m_string); }

private:
  void set(const QString & string, int force_flags = 0);
  void set(const QStringRef & string, int force_flags = 0);
  void update_flags(const QChar & c);
  void update_flags(int force_flags);

public:
  QString m_string;
  int m_flags = 0;
};

typedef QList<Token> TokenList;

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const Token & token);
#endif

/**************************************************************************************************/

#endif /* __TOKEN_H__ */
