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

#include "token.h"

#include <QtDebug>

/**************************************************************************************************/

CharTranslator::CharTranslator()
  : m_map()
{
}

CharTranslator::CharTranslator(const QString & input_chars, const QString & output_chars)
{
  if (input_chars.size() == output_chars.size()) {
    for (int i = 0; i < input_chars.size(); i++)
      m_map[input_chars[i]] = output_chars[i];
  } else
    qCritical() << "Translation map mismatch" << input_chars << output_chars;
}

CharTranslator::CharTranslator(const QStringList & string_list)
{
  char c = '1';
  for (const auto & string : string_list) {
    for (const auto & qchar : string)
      m_map[qchar] = c;
    c++;
  }
}

CharTranslator::CharTranslator(const CharTranslator & other)
  : m_map(other.m_map)
{}

CharTranslator::~CharTranslator()
{
}

CharTranslator &
CharTranslator::operator=(const CharTranslator & other)
{
  if (this != &other) {
    m_map = other.m_map;
  }

  return *this;
}

QString
CharTranslator::translate(const QString & input) const
{
  QString output;

  for (const auto & qchar : input)
    output += m_map.value(qchar, qchar);

  return output;
}

/**************************************************************************************************/

QString
Token::remove_consecutive_char(const QString & input)
{
  if (input.size()) {
    QChar previous_c = input[0];
    QString output(previous_c);

    for (int i = 1; i < input.size(); i++) {
      QChar qchar = input[i];
      if (qchar != previous_c) {
        output += qchar;
        previous_c = qchar;
      }
    }

    return output;
  } else
    return QString();
}

Token::Token()
  : m_string(),
    m_flags(0)
{}

Token::Token(const Token & other)
  : m_string(other.m_string),
    m_flags(other.m_flags)
{}

Token::Token(const QString & string, int force_flags)
  : Token()
{
  set(string, force_flags);
}

Token::Token(const QStringRef & string, int force_flags)
  : Token()
{
  set(string, force_flags);
}

Token::~Token()
{}

Token &
Token::operator=(const Token & other)
{
  if (this != &other) {
    m_string = other.m_string;
    m_flags = other.m_flags;
  }

  return *this;
}

Token &
Token::operator=(const QString & string)
{
  set(string);

  return *this;
}

Token &
Token::operator=(const QStringRef & string)
{
  set(string);

  return *this;
}

bool
Token::operator==(const Token & other) const
{
  return m_string == other.m_string;
}

bool
Token::operator<(const Token & other) const
{
  return m_string < other.m_string;
}

void
Token::update_flags(const QChar & c)
{
  if (c.isLetter())
    m_flags |= Letter;
  else if (c.isNumber())
    m_flags |= Number;
  else {
    auto category = c.category();
    if (category == QChar::Punctuation_Dash)
      m_flags |= Hyphen;
    else
      m_flags |= Other;
  }
}

void
Token::update_flags(int force_flags)
{
  // fast path
  if (force_flags)
    m_flags = force_flags;
  else {
    m_flags = 0;
    for (const auto & c : m_string)
      update_flags(c);
  }
}

void
Token::operator+=(const QChar & c)
{
  m_string += c;
  update_flags(c);
}

Token &
Token::operator<<(const QChar & c)
{
  *this += c;
  return *this;
}

void
Token::clear()
{
  m_string.clear();
  m_flags = 0;
}

void
Token::set(const QString & string, int force_flags)
{
  m_string = string;
  update_flags(force_flags);
}

void
Token::set(const QStringRef & string, int force_flags)
{
  m_string = string.toString();
  update_flags(force_flags);
}

Token
Token::to_lower_case() const
{
  // Fixme: toCaseFolded
  return Token(m_string.toLower(), m_flags);
}

Token
Token::to_upper_case() const
{
  return Token(m_string.toUpper(), m_flags);
}

Token
Token::ascii_folding() const
{
  QString decomposed_string = m_string.normalized(QString::NormalizationForm_D);
  Token output;
  for (const auto & c : decomposed_string)
    if (c.isLetterOrNumber())
      output += c;

  return output;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const Token & token)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug << token.value();

  return debug;
}
#endif

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
