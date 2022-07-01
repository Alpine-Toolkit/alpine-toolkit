// -*- mode: c++ -*-
/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef __DATABASE_ROW_LIST_HXX__
#define __DATABASE_ROW_LIST_HXX__

/**************************************************************************************************/

#include "database_row_list.h" // for checker
#include "alpine_toolkit.h"

#include <QtDebug>

/**************************************************************************************************/

template<class Row, class RowPtr>
QoRowList<Row, RowPtr>::QoRowList()
  : m_items(),
    m_removed_items()
{}

template<class Row, class RowPtr>
QoRowList<Row, RowPtr>::QoRowList(const QoRowList & other)
  : m_items(other.m_items),
    m_removed_items(other.m_removed_items)
{}

template<class Row, class RowPtr>
QoRowList<Row, RowPtr>::~QoRowList()
{
  // qATInfo() << "--- Delete QoRowList" << m_items.size() << m_removed_items.size();
  // m_items.clear();
  // for (auto & item : m_items) {
  //   qATInfo() << item;
  //   // item->break_relations();
  // }
}

template<class Row, class RowPtr>
QoRowList<Row, RowPtr> &
QoRowList<Row, RowPtr>::operator=(const QoRowList & other)
{
  if (this != &other) {
    m_items = other.m_items;
    m_removed_items = other.m_removed_items;
  }

  return *this;
}

template<class Row, class RowPtr>
QoRowList<Row, RowPtr> &
QoRowList<Row, RowPtr>::operator=(const RowPtrList & rows)
{
  //  m_items = rows;
  for (const auto & row : rows)
    m_items << row.toWeakRef();
  m_removed_items.clear();

  return *this;
}

template<class Row, class RowPtr>
void
QoRowList<Row, RowPtr>::append(const RowPtr & row)
{
  RowWeakPtr weak_ptr = row.toWeakRef();
  // Fixme: contains !
  if (not m_items.contains(weak_ptr)) {
    m_items << weak_ptr;
    // qATInfo() << "QoRowList::append" << row;
  }
  if (m_removed_items.contains(weak_ptr)) {
    m_removed_items.removeAll(weak_ptr);
    qATInfo() << "QoRowList::append was removed" << row;
  }
}

template<class Row, class RowPtr>
QoRowList<Row, RowPtr> &
QoRowList<Row, RowPtr>::operator<<(const RowPtr & row)
{
  append(row);
  return *this;
}

template<class Row, class RowPtr>
void
QoRowList<Row, RowPtr>::remove(const RowPtr & row)
{
  RowWeakPtr weak_ptr = row.toWeakRef();
  if (m_items.contains(weak_ptr)) {
    m_items.removeAll(weak_ptr);
    // if (not m_removed_items.contains(row)) {
    m_removed_items.append(weak_ptr);
    qATInfo() << "QoRowList::remove" << row;
  }
}

/**************************************************************************************************/

#endif /* __DATABASE_ROW_LIST_HXX__ */
