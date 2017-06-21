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

#include "indexer.h" // for checker

#include <algorithm>

/**************************************************************************************************/

#ifndef __INDEXER_HXX__
#define __INDEXER_HXX__

/**************************************************************************************************/

template<typename T>
DocumentMatch<T>::DocumentMatch()
  : m_document(),
    m_tokens()
{}

template<typename T>
DocumentMatch<T>::DocumentMatch(const DocumentTypePtr & document)
  : m_document(document),
    m_tokens()
{}

template<typename T>
DocumentMatch<T>::DocumentMatch(const DocumentTypePtr & document, const Token & token)
  : DocumentMatch(document)
{
  m_tokens << token;
}

template<typename T>
DocumentMatch<T>::DocumentMatch(const DocumentMatch & other)
  : m_document(other.m_document),
    m_tokens(other.m_tokens)
{}

template<typename T>
DocumentMatch<T> &
DocumentMatch<T>::operator=(const DocumentMatch & other)
{
  if (this != &other) {
    m_document = other.m_document;
    m_tokens = other.m_tokens;
  }

  return *this;
}

template<typename T>
bool
DocumentMatch<T>::operator==(const DocumentMatch & other) const
{
  return m_document == other.m_document && m_tokens == other.m_tokens;
}

template<typename T>
DocumentMatch<T> &
DocumentMatch<T>::operator<<(const Token & token)
{
  m_tokens << token;

  return *this;
}

template<typename T>
DocumentMatch<T> &
DocumentMatch<T>::operator<<(const DocumentMatch & other)
{
  if (m_document == other.m_document)
    m_tokens.append(other.m_tokens);

  return *this;
}

/**************************************************************************************************/

template<typename T>
DocumentMatches<T>::DocumentMatches()
  : m_document_map(),
    m_matches(),
    m_dirty(true)
{}

template<typename T>
DocumentMatches<T>::DocumentMatches(const DocumentMatches & other)
  : m_document_map(other.m_document_map),
    m_matches(other.m_matches),
    m_dirty(other.m_dirty)

{}

template<typename T>
DocumentMatches<T> &
DocumentMatches<T>::operator=(const DocumentMatches & other)
{
  if (this != &other) {
    m_document_map = other.m_document_map;
    m_matches = other.m_matches;
    m_dirty = other.m_dirty;
  }

  return *this;
}

template<typename T>
bool
DocumentMatches<T>::operator==(const DocumentMatches & other) const
{
  return m_document_map == other.m_document_map;
}

template<typename T>
void
DocumentMatches<T>::insert(const DocumentMatchType match)
{
  const auto & document = match.document();
  if (m_document_map.contains(document)) {
    m_document_map[document] << match;
  } else {
    m_document_map.insert(document, match);
  }
  m_dirty = true;
}

template<typename T>
void
DocumentMatches<T>::sort()
{
  if (m_dirty) {
    m_matches = m_document_map.values();
    std::sort(m_matches.begin(), m_matches.end());
    m_dirty = false;
  }
}

template<typename T>
typename DocumentMatches<T>::DocumentMatchList::const_reverse_iterator
DocumentMatches<T>::begin()
{
  sort();
  return m_matches.crbegin();
}

template<typename T>
typename DocumentMatches<T>::DocumentMatchList::const_reverse_iterator
DocumentMatches<T>::end() const
{
  return m_matches.crend();
}

/**************************************************************************************************/

template<typename T>
DocumentIndexer<T>::DocumentIndexer()
  : m_tokenizer(new Tokenizer()), // Fixme: check for leak
    m_token_map(),
    m_document_map()
{}

template<typename T>
DocumentIndexer<T>::~DocumentIndexer()
{}

template<typename T>
void
DocumentIndexer<T>::index(const Token & token, const DocumentTypePtr & document)
{
  if (not m_document_map.contains(document, token)) {
    m_document_map.insert(document, token);
    m_token_map.insert(token, document);
  }
}

template<typename T>
void
DocumentIndexer<T>::index(const TokenizedTextDocument & tokenized_document,
                          const DocumentTypePtr & document)
{
  for (const auto & token : tokenized_document)
    index(token, document);
}

template<typename T>
void
DocumentIndexer<T>::index(const TextDocument & text_document, const DocumentTypePtr & document)
{
  TokenizedTextDocument tokenized_document = m_tokenizer->process(text_document);
  index(tokenized_document, document);
}

template<typename T>
void
DocumentIndexer<T>::remove(const DocumentType & document)
{
  if (not m_document_map.contains(document)) {
    for (const auto & token : m_document_map[document])
      m_token_map.remove(token, document);
    m_document_map.remove(document);
  }
}

template<typename T>
bool
DocumentIndexer<T>::contains(const Token & token) const
{
  return m_token_map.contains(token);
}

template<typename T>
typename DocumentIndexer<T>::DocumentTypePtrList
DocumentIndexer<T>::query(const Token & token) const
{
  return m_token_map.values(token);
}

template<typename T>
typename DocumentIndexer<T>::DocumentMatchesType
DocumentIndexer<T>::query(const TokenizedTextDocument & tokenized_document) const
{
  DocumentMatchesType matches;

  for (const auto & token : tokenized_document) {
    for (const auto & document : query(token)) {
      qInfo() << "Query token" << token << document;
      DocumentMatchType match(document, token);
      matches.insert(match);
    }
  }

  return matches;
}

template<typename T>
typename DocumentIndexer<T>::DocumentMatchesType
DocumentIndexer<T>::query(const TextDocument & document) const
{
  auto tokenized_document = m_tokenizer->process(document);
  return query(tokenized_document);
}

template<typename T>
typename DocumentIndexer<T>::TokenList
DocumentIndexer<T>::document_tokens(const DocumentTypePtr & document)
{
  return m_document_map.values(document);
}

/**************************************************************************************************/

#endif /* __INDEXER_HXX__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
