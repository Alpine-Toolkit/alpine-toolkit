// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#ifndef __INTERNATIONAL_MORSE_CODE_ENGINE_H__
#define __INTERNATIONAL_MORSE_CODE_ENGINE_H__

/**************************************************************************************************/

#include <QString>

/**************************************************************************************************/

/* Node of the Morse Code Decoder tree
 *
 */
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
  QString decode(const QString & message, bool & succeed) const;

private:
  MorseCodeDecoderNode m_root_node; // root of the tree
};

/**************************************************************************************************/

#endif /* __INTERNATIONAL_MORSE_CODE_ENGINE_H__ */
