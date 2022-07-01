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

#ifndef __STEMMER_H__
#define __STEMMER_H__

/**************************************************************************************************/

#include "full_text_search/language.h"

// third-parties/snowball/snowball-source/include
// #include "snowball/libstemmer.h"
#include "libstemmer.h"

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
