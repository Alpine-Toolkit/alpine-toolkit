/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "text_document.h"
#include "alpine_toolkit.h"

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

bool
TextDocument::operator<(const TextDocument & other) const
{
  // Don't take into account language
  return m_document < other.m_document;
}
