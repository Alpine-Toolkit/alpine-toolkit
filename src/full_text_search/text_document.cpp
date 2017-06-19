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

#include "text_document.h"

/**************************************************************************************************/

LocalizedDocument::LocalizedDocument()
  : m_language()
{}

LocalizedDocument::LocalizedDocument(LanguageCode language)
  : m_language(language)
{}

LocalizedDocument::LocalizedDocument(const LocalizedDocument & other)
  : m_language(other.m_language)
{}

LocalizedDocument::~LocalizedDocument()
{}

LocalizedDocument &
LocalizedDocument::operator=(const LocalizedDocument & other)
{
  if (this != &other) {
    m_language = other.m_language;
  }

  return *this;
}

bool
LocalizedDocument::operator==(const LocalizedDocument & other) const
{
  return m_language == other.m_language;
}

/**************************************************************************************************/

TextDocument::TextDocument()
  : LocalizedDocument(),
    m_document()
{}

TextDocument::TextDocument(LanguageCode language, const QString & document)
  : LocalizedDocument(language),
    m_document(document)
{}

TextDocument::TextDocument(const TextDocument & other)
  : LocalizedDocument(other),
    m_document(other.m_document)
{}

TextDocument::~TextDocument()
{}

TextDocument &
TextDocument::operator=(const TextDocument & other)
{
  if (this != &other) {
    LocalizedDocument::operator=(other);
    m_document = other.m_document;
  }

  return *this;
}

bool
TextDocument::operator==(const TextDocument & other) const
{
  if (not LocalizedDocument::operator==(other))
    return false;
  else
    return m_document == other.m_document;
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
