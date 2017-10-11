// -*- mode: c++ -*-
/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
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
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef __DATABASE_ROW_LIST_H__
#define __DATABASE_ROW_LIST_H__

/**************************************************************************************************/

#include<QList>
#include<QSharedPointer>
#include<QWeakPointer>

/**************************************************************************************************/

// Row::Ptr is not yet defined
template<class Row, class RowPtr>
class QoRowList
{
 public:
  typedef QWeakPointer<Row> RowWeakPtr;
  typedef QList<RowPtr> RowPtrList;
  typedef QList<RowWeakPtr> RowWeakPtrList; // Fixme QLinkedList ?

public:
  QoRowList();
  QoRowList(const QoRowList & other);
  // QoRowList(const QoRowList && other);
  // QoRowList(std::initializer_list<T> args);
  ~QoRowList();

  QoRowList & operator=(const QoRowList & other);
  QoRowList & operator=(const RowPtrList & rows);

  bool operator==(const QoRowList & other);

  void append(const RowPtr & row);
  QoRowList & operator<<(const RowPtr & row);
  // QoRowList & operator<<(const RowWeakPtrList & rows);

  void remove(const RowPtr & row);

  // void append(const QList<T> &value)

  int size() const { return m_items.size(); }

  typename RowWeakPtrList::iterator begin() { return m_items.begin(); }
  typename RowWeakPtrList::const_iterator cbegin() const { return m_items.cbegin(); }
  typename RowWeakPtrList::iterator end() { return m_items.end(); }
  typename RowWeakPtrList::const_iterator cend() const { return m_items.cend(); }

private:
  RowWeakPtrList m_items;
  RowWeakPtrList m_removed_items;
};

/**************************************************************************************************/

/**************************************************************************************************/

#ifndef QC_MANUAL_INSTANTIATION
#include "database_row_list.hxx"
#endif

/**************************************************************************************************/

#endif /* __DATABASE_ROW_LIST_H__ */
