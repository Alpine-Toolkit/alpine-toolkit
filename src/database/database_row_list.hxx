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

#ifndef __DATABASE_ROW_LIST_HXX__
#define __DATABASE_ROW_LIST_HXX__

/**************************************************************************************************/

#include "database_row_list.h" // for checker

#include <QtDebug>

/**************************************************************************************************/

template<class T>
QcRowList<T>::QcRowList()
  : m_items(),
    m_removed_items()
{}

template<class T>
QcRowList<T>::QcRowList(const QcRowList & other)
  : m_items(other.m_items),
    m_removed_items(other.m_removed_items)
{}

template<class T>
QcRowList<T>::~QcRowList()
{
  qInfo() << "--- Delete QcRowList" << m_items.size() << m_removed_items.size();
  // m_items.clear();
  // for (auto & item : m_items) {
  //   qInfo() << item;
  //   // item->break_relations();
  // }
}

template<class T>
QcRowList<T> &
QcRowList<T>::operator=(const QcRowList & other)
{
  if (this != &other) {
    m_items = other.m_items;
    m_removed_items = other.m_removed_items;
  }

  return *this;
}

template<class T>
QcRowList<T> &
QcRowList<T>::operator=(const RowPtrList & rows)
{
  m_items = rows;
  m_removed_items.clear();

  return *this;
}

template<class T>
void
QcRowList<T>::append(const RowPtr & row)
{
  if (not m_items.contains(row)) {
    m_items << row;
    qInfo() << "QcRowList::append" << row;
  }
  if (m_removed_items.contains(row)) {
    m_removed_items.removeAll(row);
    qInfo() << "QcRowList::append was removed" << row;
  }
}

template<class T>
QcRowList<T> &
QcRowList<T>::operator<<(const RowPtr & row)
{
  append(row);
  return *this;
}

template<class T>
void
QcRowList<T>::remove(const RowPtr & row)
{
  if (m_items.contains(row)) {
    m_items.removeAll(row);
    // if (not m_removed_items.contains(row)) {
    m_removed_items.append(row);
    qInfo() << "QcRowList::remove" << row;
  }
}

/**************************************************************************************************/

#endif /* __DATABASE_ROW_LIST_HXX__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
