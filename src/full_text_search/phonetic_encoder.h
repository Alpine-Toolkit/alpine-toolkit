// -*- mode: c++ -*-
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

#ifndef __SOUNDEX_H__
#define __SOUNDEX_H__

/**************************************************************************************************/

#include "full_text_search/token.h"

#include <QString>

/**************************************************************************************************/

class PhoneticEncoder
{
public:
  PhoneticEncoder();
  ~PhoneticEncoder();

  Token soundex(const Token & token) const;
  Token soundex_fr(const Token & token) const;

private:
  static QString zero_padding(const QString & string, const int encoded_length = 4);
  static Token soundex(const Token & token, const CharTranslator & translation_map);

private:
  CharTranslator m_soundex_translation_map;
  CharTranslator m_soundex_translation_map_fr;
};

/**************************************************************************************************/

#endif /* __SOUNDEX_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
