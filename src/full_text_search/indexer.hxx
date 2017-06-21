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

/**************************************************************************************************/

#ifndef __INDEXER_HXX__
#define __INDEXER_HXX__

/**************************************************************************************************/

template<typename T>
DocumentIndexer<T>::DocumentIndexer()
  : m_tokenizer(new Tokenizer()), // Fixme: check for leak
    m_token_map(),
    m_document_map()
{}

template<typename T>
DocumentIndexer<T>::DocumentIndexer(Tokenizer * tokenizer)
  : m_tokenizer(tokenizer),
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
  if (m_tokenizer) {
    TokenizedTextDocument tokenized_document = m_tokenizer->process(text_document);
    index(tokenized_document, document);
  }
}

/*
template<typename T>
void
DocumentIndexer<T>::index(const QString & text, const DocumentTypePtr & document)
{
  if (m_tokenizer) {
    TokenizedTextDocument tokenized_document = m_tokenizer->process(text);
    index(tokenized_document, document);
  }
}
*/

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

/*
template<typename T>
bool
DocumentIndexer<T>::contains(const QString & text) const
{
}
*/

template<typename T>
typename DocumentIndexer<T>::DocumentTypePtrList
DocumentIndexer<T>::query(const Token & token) const
{
  // DocumentTypePtrList documents;

  // typename TokenMap::const_iterator i = m_token_map.find(token);
  // while (i != m_token_map.end() && i.key() == token) {
  //   documents << i.value();
  //   ++i;
  // }

  // typename TokenMap::const_iterator map_iterator = m_token_map.find(token);
  // for (const auto & document : map_iterator)
  //   documents << document;

  return m_token_map.values(token);

  // return documents;
}

template<typename T>
typename DocumentIndexer<T>::DocumentTypePtrList
DocumentIndexer<T>::query(const TokenizedTextDocument & tokenized_document) const
{
  DocumentTypePtrSet documents;

  for (const auto & token : tokenized_document) {
    qInfo() << "Query token" << token;
    for (const auto & document : query(token)) {
      documents += document;
      qInfo() << "Query token" << token << document;
    }
  }

  return documents.toList();
}

template<typename T>
typename DocumentIndexer<T>::DocumentTypePtrList
DocumentIndexer<T>::query(const TextDocument & document) const
{
  if (m_tokenizer) {
    TokenizedTextDocument tokenized_document = m_tokenizer->process(document);
    return query(tokenized_document);
  } else
    return DocumentTypePtrList();
}

/*
template<typename T>
typename DocumentIndexer<T>::DocumentTypePtrList
DocumentIndexer<T>::query(const QString & text) const
{
  if (m_tokenizer) {
    TokenizedTextDocument tokenized_document = m_tokenizer->process(TextDocument(text));
    return query(tokenized_document);
  } else
    return DocumentTypePtrList();
}
*/

template<typename T>
typename DocumentIndexer<T>::TokenList
DocumentIndexer<T>::document_tokens(const DocumentTypePtr & document)
{
  TokenList tokens;

  if (m_document_map.contains(document)) {
    // m_document_map[document]
    // for (const auto & token : map_iterator)
    //   tokens << token;
    // typename DocumentMap::const_iterator it = m_document_map.find(document);
    // while (it != m_document_map.end() && it.key() == document) {
    //   tokens<< it.value();
    tokens = m_document_map.values(document);
  }

  return tokens;
}

/**************************************************************************************************/

#endif /* __INDEXER_HXX__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
