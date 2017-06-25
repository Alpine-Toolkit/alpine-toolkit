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
DocumentMatches<T> &
DocumentMatches<T>::operator<<(const DocumentMatchType & match)
{
  insert(match);

  return *this;
}

template<typename T>
DocumentMatches<T> &
DocumentMatches<T>::operator<<(const DocumentMatches & other)
{
  for (const auto & match : other.m_document_map.values())
    insert(match);

  return *this;
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

/*
template<typename T>
typename DocumentMatches<T>::DocumentPtrList
DocumentMatches<T>::values() const
{
  sort();

  DocumentPtrList documents;
  for (const auto & match : m_matches)
    documents << match.document();

  return documents;
}
*/

/**************************************************************************************************/

template<typename T>
DocumentIndexer<T>::DocumentIndexer()
  : m_token_map(),
    m_document_map()
{}

template<typename T>
DocumentIndexer<T>::~DocumentIndexer()
{}

template<typename T>
void
DocumentIndexer<T>::insert(const Token & token, const DocumentTypePtr & document)
{
  if (not m_document_map.contains(document, token)) {
    m_document_map.insert(document, token);
    m_token_map.insert(token, document);
  }
}

template<typename T>
void
DocumentIndexer<T>::insert(const TokenizedTextDocument & tokenized_document,
                           const DocumentTypePtr & document)
{
  for (const auto & token : tokenized_document)
    insert(token, document);
}

template<typename T>
void
DocumentIndexer<T>::remove(const DocumentTypePtr & document)
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
      // qInfo() << "Query token" << token << document;
      DocumentMatchType match(document, token);
      matches << match;
    }
  }

  return matches;
}

template<typename T>
typename DocumentIndexer<T>::DocumentMatchesType
DocumentIndexer<T>::like(const Token & query_token) const
{
  DocumentMatchesType matches;

  for (const auto & token : m_token_map.keys())
    if (token.contains(query_token)) {
      DocumentTypePtrList documents = m_token_map.values(token);
      for (const auto & document : query(token)) {
        DocumentMatchType match(document, token);
        matches << match;
      }
    }

  return matches;
}

template<typename T>
typename DocumentIndexer<T>::DocumentMatchesType
DocumentIndexer<T>::like(const TokenizedTextDocument & tokenized_document) const
{
  DocumentMatchesType matches;

  for (const auto & token : tokenized_document)
    matches << like(token);

  return matches;
}

template<typename T>
typename DocumentIndexer<T>::TokenList
DocumentIndexer<T>::document_tokens(const DocumentTypePtr & document) const
{
  return m_document_map.values(document);
}

template<typename T>
typename DocumentIndexer<T>::TokenList
DocumentIndexer<T>::tokens() const
{
  return m_document_map.values();
}

/**************************************************************************************************/

template<typename T>
PhoneticDocumentIndexer<T>::PhoneticDocumentIndexer()
  : DocumentIndexer<T>(),
    m_tokenizer_pipe()
{
  m_tokenizer_pipe << new LocalizedPhoneticFilter();
}

template<typename T>
PhoneticDocumentIndexer<T>::~PhoneticDocumentIndexer()
{}

template<typename T>
void
PhoneticDocumentIndexer<T>::insert(const TokenizedTextDocument & tokenized_document, const DocumentTypePtr & document)
{
  TokenizedTextDocument output = m_tokenizer_pipe.process(tokenized_document);
  DocumentIndexer<T>::insert(output, document);
}

template<typename T>
typename DocumentIndexer<T>::DocumentMatchesType
PhoneticDocumentIndexer<T>::query(const TokenizedTextDocument & tokenized_document) const
{
  TokenizedTextDocument output = m_tokenizer_pipe.process(tokenized_document);
  return DocumentIndexer<T>::query(output);
}

/**************************************************************************************************/

template<typename T>
TextDocumentIndexer<T>::TextDocumentIndexer(bool use_phonetic_encoder)
  : DocumentIndexer<T>(),
    m_tokenizer(new Tokenizer()), // Fixme: check for leak
    m_phonetic_index()
{
  if (use_phonetic_encoder)
    m_phonetic_index.reset(new PhoneticDocumentIndexerType());
}

template<typename T>
TextDocumentIndexer<T>::~TextDocumentIndexer()
{}

template<typename T>
void
TextDocumentIndexer<T>::insert(const TextDocument & text_document, const DocumentTypePtr & document)
{
  TokenizedTextDocument tokenized_document = m_tokenizer->process(text_document);
  DocumentIndexerType::insert(tokenized_document, document);
  if (has_phonetic_encoder())
    m_phonetic_index->insert(tokenized_document, document);
}

template<typename T>
typename DocumentIndexer<T>::DocumentMatchesType
TextDocumentIndexer<T>::query(const TextDocument & document, bool like) const
{
  TokenizedTextDocument tokenized_document = m_tokenizer->process(document);
  DocumentMatchesType matches = DocumentIndexerType::query(tokenized_document);
  if (like)
    matches << DocumentIndexerType::like(tokenized_document);
  if (has_phonetic_encoder())
    matches << m_phonetic_index->query(tokenized_document);
  return matches;
}

/**************************************************************************************************/

#endif /* __INDEXER_HXX__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
