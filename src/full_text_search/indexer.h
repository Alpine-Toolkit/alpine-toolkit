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
class DocumentIndexer
{
private:
  typedef T DocumentType;
  typedef QSharedPointer<DocumentType> DocumentTypePtr;
  typedef QList<DocumentTypePtr> DocumentTypePtrList;
  typedef QSet<DocumentTypePtr> DocumentTypePtrSet;
  typedef QList<Token> TokenList;
  typedef QMultiMap<Token, DocumentTypePtr> TokenMap;
  typedef QMultiMap<DocumentTypePtr, Token> DocumentMap; // TokenList

public:
  DocumentIndexer();
  DocumentIndexer(Tokenizer * tokenizer);
  ~DocumentIndexer();

  Tokenizer & tokenizer() { return *m_tokenizer; }
  void tokenizer(const Tokenizer * tokenizer) { m_tokenizer = tokenizer; }

  // void index(const QString & text, const DocumentTypePtr & document);
  void index(const TextDocument & text_document, const DocumentTypePtr & document);
  void index(const TokenizedTextDocument & tokenized_document, const DocumentTypePtr & document);
  void index(const Token & token, const DocumentTypePtr & document);

  // DocumentTypePtrList query(const QString & text) const;
  DocumentTypePtrList query(const TextDocument & text_document) const;
  DocumentTypePtrList query(const TokenizedTextDocument & tokenized_document) const;
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
