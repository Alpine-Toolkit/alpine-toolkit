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

#ifndef __INDEXER_H__
#define __INDEXER_H__

/**************************************************************************************************/

#include "full_text_search/token.h"
#include "full_text_search/tokenizer.h"

// #include <QHash>
// #include <QMap>
#include <QList>
#include <QMultiMap>
#include <QSharedPointer>

/**************************************************************************************************/

template<typename T>
class DocumentMatch
{
public:
  typedef T DocumentType;
  typedef QSharedPointer<DocumentType> DocumentTypePtr;
  typedef QList<Token> TokenList;

public:
  DocumentMatch();
  DocumentMatch(const DocumentTypePtr & document);
  DocumentMatch(const DocumentTypePtr & document, const Token & token);
  DocumentMatch(const DocumentMatch & other);

  DocumentMatch & operator=(const DocumentMatch & other);

  bool operator==(const DocumentMatch & other) const;

  const DocumentTypePtr & document() const { return  m_document; }
  const TokenList & tokens() const { return m_tokens; }

  DocumentMatch & operator<<(const Token & token);
  DocumentMatch & operator<<(const DocumentMatch & other);

  int pertinence() const { return m_tokens.size(); }

  bool operator<(const DocumentMatch & other) { return pertinence() < other.pertinence(); }

private:
  DocumentTypePtr m_document;
  TokenList m_tokens; // Fixme: Set ?
};

/**************************************************************************************************/

template<typename T>
class DocumentMatches
{
public:
  typedef T DocumentType;
  typedef QSharedPointer<DocumentType> DocumentTypePtr;
  typedef DocumentMatch<DocumentType> DocumentMatchType;
  typedef QMap<DocumentTypePtr, DocumentMatchType> DocumentMap;
  typedef QList<DocumentMatchType> DocumentMatchList;

public:
  DocumentMatches();
  DocumentMatches(const DocumentMatches & other);

  DocumentMatches & operator=(const DocumentMatches & other);

  bool operator==(const DocumentMatches & other) const;

  // bool contains(const DocumentTypePtr & document) const;

  void insert(const DocumentMatchType match);

  typename DocumentMatchList::const_reverse_iterator begin(); // call sort
  typename DocumentMatchList::const_reverse_iterator end() const;

  // typename DocumentMatchList::const_iterator cbegin() const;
  // typename DocumentMatchList::const_iterator cend() const;

private:
  void sort();

private:
  DocumentMap m_document_map;
  DocumentMatchList m_matches;
  bool m_dirty = true;
};

/**************************************************************************************************/

template<typename T>
class DocumentIndexer
{
public:
  typedef T DocumentType;
  typedef QSharedPointer<DocumentType> DocumentTypePtr;
  typedef QList<DocumentTypePtr> DocumentTypePtrList;
  typedef QSet<DocumentTypePtr> DocumentTypePtrSet;
  typedef QList<Token> TokenList;
  typedef QMultiMap<Token, DocumentTypePtr> TokenMap;
  typedef QMultiMap<DocumentTypePtr, Token> DocumentMap; // TokenList
  typedef DocumentMatch<T> DocumentMatchType;
  typedef DocumentMatches<T> DocumentMatchesType;

public:
  DocumentIndexer();
  // DocumentIndexer(Tokenizer * tokenizer);
  ~DocumentIndexer();

  Tokenizer & tokenizer() { return *m_tokenizer; }
  void tokenizer(const Tokenizer * tokenizer) { m_tokenizer = tokenizer; }

  // void index(const QString & text, const DocumentTypePtr & document);
  void index(const TextDocument & text_document, const DocumentTypePtr & document);
  void index(const TokenizedTextDocument & tokenized_document, const DocumentTypePtr & document);
  void index(const Token & token, const DocumentTypePtr & document);

  // DocumentTypePtrList query(const QString & text) const;
  DocumentMatchesType query(const TextDocument & text_document) const;
  DocumentMatchesType query(const TokenizedTextDocument & tokenized_document) const;
  DocumentTypePtrList query(const Token & token) const;

  void remove(const DocumentType & document);

  // bool contains(const QString & text) const;
  bool contains(const Token & token) const;

  TokenList document_tokens(const DocumentTypePtr & document);

private:
  QSharedPointer<Tokenizer> m_tokenizer;
  TokenMap m_token_map;
  DocumentMap m_document_map;
};

/**************************************************************************************************/

#ifndef QC_MANUAL_INSTANTIATION
#include "indexer.hxx"
#endif

/**************************************************************************************************/

#endif /* __INDEXER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
