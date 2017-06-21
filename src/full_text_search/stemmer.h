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

#ifndef __STEMMER_H__
#define __STEMMER_H__

/**************************************************************************************************/

#include "full_text_search/language.h"

#include "snowball/libstemmer.h"

#include <QList>
#include <QLocale>
#include <QString>

/**************************************************************************************************/

/*
 * Snowball Wrapper
 *
 */
class Stemmer
{
public:
  typedef QList<LanguageCode> LanguageCodeList;

public:
  static LanguageCodeList available_languages();

public:
  Stemmer(const LanguageCode & language);
  ~Stemmer();

  QString process(const QString & word) const;

private:
  struct sb_stemmer * m_stemmer = nullptr;
};

/**************************************************************************************************/

#endif /* __STEMMER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
