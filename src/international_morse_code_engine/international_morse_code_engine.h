// -*- mode: c++ -*-

/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire.
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

#ifndef __INTERNATIONAL_MORSE_CODE_ENGINE_H__
#define __INTERNATIONAL_MORSE_CODE_ENGINE_H__

/**************************************************************************************************/

#include <QString>

/**************************************************************************************************/

class MorseCodeDecoderNode
{
public:
  MorseCodeDecoderNode();
  ~MorseCodeDecoderNode();

  QChar character() const {
    return m_character;
  }

  const MorseCodeDecoderNode * dot_branch() const {
    return m_dot_branch;
  }

  const MorseCodeDecoderNode * dash_branch() const {
    return m_dash_branch;
  }

  void add(QString code, QChar character, int level = 0);
  // QChar decode(QString::const_iterator & stream) const;

public:
  MorseCodeDecoderNode * m_dot_branch;
  MorseCodeDecoderNode * m_dash_branch;
  QChar m_character;
};

/**************************************************************************************************/

class InternationalMorseCodeEngine
{
public:
  InternationalMorseCodeEngine();
  ~InternationalMorseCodeEngine();

  QString encode(const QString & message, bool use_bit = false, bool compress_bit = false) const;
  QString decode(const QString & message) const;

private:
  MorseCodeDecoderNode m_root_node;
};

/**************************************************************************************************/

#endif /* __INTERNATIONAL_MORSE_CODE_ENGINE_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
