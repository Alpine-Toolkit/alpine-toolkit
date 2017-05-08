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
{}

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
void
QcRowList<T>::append(const RowPtr & value)
{
  if (not m_items.contains(value)) {
    m_items << value;
    qInfo() << "QcRowList::append" << value << *value;
  }
  if (m_removed_items.contains(value)) {
    m_removed_items.removeAll(value);
    qInfo() << "QcRowList::append was removed" << value << *value;
  }
}

template<class T>
QcRowList<T> &
QcRowList<T>::operator<<(const RowPtr & value)
{
  append(value);
  return *this;
}

template<class T>
void
QcRowList<T>::remove(const RowPtr & value)
{
  if (m_items.contains(value)) {
    m_items.removeAll(value);
    // if (not m_removed_items.contains(value)) {
    m_removed_items.append(value);
    qInfo() << "QcRowList::remove" << value << *value;
  }
}

/**************************************************************************************************/

#endif /* __DATABASE_ROW_LIST_HXX__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
