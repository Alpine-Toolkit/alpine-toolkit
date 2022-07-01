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

#ifndef __TEXT_DOCUMENT_H__
#define __TEXT_DOCUMENT_H__

/**************************************************************************************************/

#include "full_text_search/language.h"

#include <QString>

/**************************************************************************************************/

class LocalizedDocument
{
public:
  LocalizedDocument();
  LocalizedDocument(LanguageCode language);
  LocalizedDocument(const LocalizedDocument & other);
  ~LocalizedDocument();

  LocalizedDocument & operator=(const LocalizedDocument & other);

  bool operator==(const LocalizedDocument & other) const;

  LanguageCode language() const { return m_language; }
  void set_language(LanguageCode value) { m_language = value; }

private:
  LanguageCode m_language;
};

/**************************************************************************************************/

class TextDocument : public LocalizedDocument
{
public:
  TextDocument();
  TextDocument(LanguageCode language, const QString & document);
  TextDocument(const TextDocument & other);
  ~TextDocument();

  TextDocument & operator=(const TextDocument & other);

  bool operator==(const TextDocument & other) const;
  bool operator<(const TextDocument & other) const; // QMap total order

  const QString & document() const { return m_document; }
  void set_document(const QString & value) { m_document = value; }

private:
  QString m_document;
};

/**************************************************************************************************/

#endif /* __TEXT_DOCUMENT_H__ */
