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

#include "phonetic_algorithm.h"

#include <QChar>
#include <QHash>
#include <QStringList>
#include <QtDebug>

/**************************************************************************************************/

bool
is_alpha_string(const QString & string)
{
  for (const auto & qchar : string) {
    char c = qchar.toLatin1();
    if (c == 0 or not (c >= 'a' and c <= 'z'))
      return false;
  }

  return true;
}

/**************************************************************************************************/

typedef QHash<QChar, QChar> TranslationMap;

TranslationMap
make_translation_map(const QString & input_chars, const QString & output_chars)
{
  TranslationMap map;

  if (input_chars.size() != output_chars.size()) {
    qCritical() << "Translation map mismatch" << input_chars << output_chars;
    return map;
  }

  for (int i = 0; i < input_chars.size(); i++)
    map[input_chars[i]] = output_chars[i];

  return map;
}

TranslationMap
make_translation_map(const QStringList & string_list)
{
  TranslationMap map;

  char c = '1';
  for (const auto & string : string_list) {
    for (const auto & qchar : string)
    map[qchar] = c;
    c++;
  }

  return map;
}

/**************************************************************************************************/

QString
translate(const QString & input, const TranslationMap & translation_map)
{
  QString output;

  for (const auto & qchar : input)
    output += translation_map.value(qchar, qchar);

  return output;
}

/**************************************************************************************************/

QString
remove_consecutive_char(const QString & input)
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

/**************************************************************************************************/

QString
zero_padding(const QString & string, const int encoded_length = 4)
{
  qInfo() << "zero_padding" << string;

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

static bool soundex_translation_map_done = false;
static TranslationMap soundex_translation_map;
static TranslationMap soundex_fr_translation_map;

void
init_translation_map()
{
  if (not soundex_translation_map_done) {
    {
      QStringList groups = {"bfpv", "cgjkqsxz", "dt", "l", "mn", "r"};
      soundex_translation_map = make_translation_map(groups);
    }

    {
      QStringList groups = {"bp", "ckq", "dt", "l", "mn", "r", "gj", "xzs", "fv"};
      soundex_fr_translation_map = make_translation_map(groups);
    }

    soundex_translation_map_done = true;
  }
}

/**************************************************************************************************/

QString
soundex(const QString & string, const TranslationMap & translation_map)
{
  QString encoded = string;

  // String must be at least 1 character
  if (encoded.isEmpty())
    return QLatin1String("0000");

  encoded = encoded.toLower();

  qInfo() << "soundex" << string;

  // Must consist entirely of letters
  if (not is_alpha_string(encoded))
    return QLatin1String("0000");

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
  encoded = translate(encoded, translation_map);

  // Replace all adjacent same digits with one digit.
  encoded = remove_consecutive_char(encoded);

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

  return zero_padding(encoded);
}

/**************************************************************************************************/

QString
soundex_cleanup(const QString & string)
{
  QString encoded = string;

  encoded.remove('-');
  encoded.remove(' ');

  return encoded;
}

/**************************************************************************************************/

QString
soundex(const QString & string)
{
  init_translation_map();

  return soundex(soundex_cleanup(string), soundex_translation_map);
}

/**************************************************************************************************/

// French Soundex variant
QString
soundex_fr(const QString & string)
{
  init_translation_map();

  QString encoded = soundex_cleanup(string);

  // Convert French diacritic
  encoded = encoded.toLower();
  // encoded = encoded.replace(QLatin1String("é"), QLatin1String("e"));
  // encoded = encoded.replace(QLatin1String("è"), QLatin1String("e"));
  // encoded = encoded.replace(QLatin1String("ë"), QLatin1String("e"));
  // encoded = encoded.replace(QLatin1String("ê"), QLatin1String("e"));
  // encoded = encoded.replace(QLatin1String("à"), QLatin1String("a"));
  // encoded = encoded.replace(QLatin1String("ä"), QLatin1String("a"));
  // encoded = encoded.replace(QLatin1String("ç"), QLatin1String("c"));
  // encoded = encoded.replace(QLatin1String("î"), QLatin1String("i"));
  // encoded = encoded.replace(QLatin1String("ï"), QLatin1String("i"));
  // encoded = encoded.replace(QLatin1String("ô"), QLatin1String("o"));
  // encoded = encoded.replace(QLatin1String("ö"), QLatin1String("o"));
  // encoded = encoded.replace(QLatin1String("ù"), QLatin1String("u"));
  // encoded = encoded.replace(QLatin1String("ü"), QLatin1String("u"));
  // encoded = encoded.replace(QLatin1String("û"), QLatin1String("u"));

  QString normalized_name = encoded.normalized(QString::NormalizationForm_D);
  QString alpha_name;
  for (const auto & c : normalized_name)
    if (c.isLetterOrNumber() or c.isSpace())
      alpha_name += c;

  return soundex(alpha_name, soundex_fr_translation_map); // encoded
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
