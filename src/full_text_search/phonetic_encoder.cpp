/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
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
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "phonetic_encoder.h"

#include <QtDebug>

/**************************************************************************************************/

QString
PhoneticEncoder::zero_padding(const QString & string, const int encoded_length)
{
  // qInfo() << "zero_padding" << string;

  QString output(string);
  int length = output.size();

  if (length > encoded_length)
    return output.left(4);
  else {
    int padding_length = encoded_length - length;
    if (padding_length)
      for (int i = 0; i < padding_length; i++)
        output += '0';
    return output;
  }
}

/**************************************************************************************************/

PhoneticEncoder::PhoneticEncoder()
{
  m_language_map[QLocale::English] = CharTranslator({"bfpv", "cgjkqsxz", "dt", "l", "mn", "r"});
  m_language_map[QLocale::French] = CharTranslator({"bp", "ckq", "dt", "l", "mn", "r", "gj", "xzs", "fv"});
}

PhoneticEncoder::~PhoneticEncoder()
{}

Token
PhoneticEncoder::soundex(const Token & input_token, const CharTranslator & translation_map)
{
  Token token = input_token.ascii_folding();

  if (token.is_empty() or not token.is_letter())
    return Token(QLatin1String("0000"), Token::Number); // Fixme: func ???

  QString encoded = token.to_lower_case().value();

  // 1) Retain the first letter of the name and drop all other occurrences of a, e, i, o, u, y, h, w.

  // 2) Replace consonants with digits as follows (after the first letter):
  //   b, f, p, v → 1
  //   c, g, j, k, q, s, x, z → 2
  //   d, t → 3
  //   l → 4
  //   m, n → 5
  //   r → 6

  // 3) If two or more letters with the same number are adjacent in the
  // original name (before step 1), only retain the first letter; also
  // two letters with the same number separated by 'h' or 'w' are
  // coded as a single number, whereas such letters separated by a
  // vowel are coded twice. This rule also applies to the first
  // letter.

  // 4) If you have too few letters in your word that you can't assign
  // three numbers, append with zeros until there are three
  // numbers. If you have more than 3 letters, just retain the first 3
  // numbers.

  // Save the first letter. Remove all occurrences of 'h' and 'w' except first letter.
  QChar first_letter = encoded[0];
  encoded.remove('h');
  encoded.remove('w');

  // Replace all consonants (include the first letter) with digits as in [2] above.
  encoded = translation_map.translate(encoded);

  // Replace all adjacent same digits with one digit.
  encoded = Token::remove_consecutive_char(encoded);

  // * Remove all occurrences of a, e, i, o, u, y except first letter.
  QString right = encoded.mid(1);
  QChar vowel[] = {'a', 'e', 'i', 'o', 'u', 'y'};
  for (auto c : vowel)
    right.remove(c);

  // * If first symbol is a digit replace it with letter saved on step 1.
  if (encoded[0].isDigit())
    encoded = first_letter + right;
  else
    encoded = encoded[0] + right;

  // * Append 3 zeros if result contains less than 3 digits. Remove
  // * all except first letter and 3 digits after it (This step same
  // * as [4] in explanation above).

  encoded = zero_padding(encoded);

  return Token(encoded, Token::Letter | Token::Number);
}

/**************************************************************************************************/

Token
PhoneticEncoder::soundex(const LanguageCode & language, const Token & token) const
{
  if (m_language_map.contains(language))
    return soundex(token, m_language_map[language]);
  else
    return Token();
}

Token
PhoneticEncoder::soundex_us(const Token & token) const
{
  return soundex(token, m_language_map[QLocale::English]);
}

Token
PhoneticEncoder::soundex_fr(const Token & token) const
{
  return soundex(token, m_language_map[QLocale::French]);
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
