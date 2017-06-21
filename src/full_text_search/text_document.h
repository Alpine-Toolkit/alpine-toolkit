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

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
