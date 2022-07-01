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

#ifndef __SOUNDEX_H__
#define __SOUNDEX_H__

/**************************************************************************************************/

#include "full_text_search/token.h"

#include <QString>
#include <QHash>

/**************************************************************************************************/

// Fixme: singleton ?

class PhoneticEncoder
{
public:
  static PhoneticEncoder & instance()
  {
    static PhoneticEncoder m_instance;
    return m_instance;
  }

  // delete copy and move constructors and assign operators
  PhoneticEncoder(const PhoneticEncoder &) = delete;
  PhoneticEncoder(PhoneticEncoder &&) = delete;
  PhoneticEncoder & operator=(const PhoneticEncoder &) = delete;
  PhoneticEncoder & operator=(PhoneticEncoder &&) = delete;

  Token soundex_us(const Token & token) const;
  Token soundex_fr(const Token & token) const;
  Token soundex(const LanguageCode & language, const Token & token) const;

protected:
  PhoneticEncoder();
  ~PhoneticEncoder();

private:
  static QString zero_padding(const QString & string, const int encoded_length = 4);
  static Token soundex(const Token & token, const CharTranslator & translation_map);

private:
  QHash<LanguageCode, CharTranslator> m_language_map;
};

/**************************************************************************************************/

#endif /* __SOUNDEX_H__ */
