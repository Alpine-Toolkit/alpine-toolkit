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

#ifndef __DATABASE_ROW_LIST_H__
#define __DATABASE_ROW_LIST_H__

/**************************************************************************************************/

#include<QList>
#include<QSharedPointer>

/**************************************************************************************************/

template<class T>
class QcRowList
{
 public:
  typedef T Row;
  typedef QSharedPointer<Row> RowPtr;
  typedef QList<RowPtr> RowPtrList;

public:
  QcRowList();
  QcRowList(const QcRowList & other);
  // QcRowList(const QcRowList && other);
  // QcRowList(std::initializer_list<T> args);
  ~QcRowList();

  QcRowList & operator=(const QcRowList & other);

  bool operator==(const QcRowList & other);

  void append(const RowPtr & value);
  QcRowList & operator<<(const RowPtr & value);

  void remove(const RowPtr & value);

  // void append(const QList<T> &value)

  int size() const { return m_items.size(); }

  typename RowPtrList::iterator begin() { return m_items.begin(); }
  typename RowPtrList::const_iterator cbegin() const { return m_items.cbegin(); }
  typename RowPtrList::iterator end() { return m_items.end(); }
  typename RowPtrList::const_iterator cend() const { return m_items.cend(); }

private:
  RowPtrList m_items;
  RowPtrList m_removed_items;
};

/**************************************************************************************************/

// const T & at(int i) const
// T & back()
// const T & back() const
// iterator begin()
// const_iterator begin() const
// const_iterator cbegin() const
// const_iterator cend() const
// void clear()
// const_iterator constBegin() const
// const_iterator constEnd() const
// const T & constFirst() const
// const T & constLast() const
// bool contains(const T &value) const
// int count(const T &value) const
// int count() const
// const_reverse_iterator crbegin() const
// const_reverse_iterator crend() const
// bool empty() const
// iterator end()
// const_iterator end() const
// bool endsWith(const T &value) const
// iterator erase(iterator pos)
// iterator erase(iterator begin, iterator end)
// T & first()
// const T & first() const
// T & front()
// const T & front() const
// int indexOf(const T &value, int from = 0) const
// void insert(int i, const T &value)
// iterator insert(iterator before, const T &value)
// bool isEmpty() const
// T & last()
// const T & last() const
// int lastIndexOf(const T &value, int from = -1) const
// int length() const
// QList<T> mid(int pos, int length = -1) const
// void move(int from, int to)
// void pop_back()
// void pop_front()
// void prepend(const T &value)
// void push_back(const T &value)
// void push_front(const T &value)
// reverse_iterator rbegin()
// const_reverse_iterator rbegin() const
// int removeAll(const T &value)
// void removeAt(int i)
// void removeFirst()
// void removeLast()
// bool removeOne(const T &value)
// reverse_iterator rend()
// const_reverse_iterator rend() const
// void replace(int i, const T &value)
// void reserve(int alloc)
// int size() const
// bool startsWith(const T &value) const
// void swap(QList<T> &other)
// void swap(int i, int j)
// T takeAt(int i)
// T takeFirst()
// T takeLast()
// QSet<T> toSet() const
// std::list<T> toStdList() const
// QVector<T> toVector() const
// T value(int i) const
// T value(int i, const T &defaultValue) const
// bool operator!=(const QList<T> &other) const
// QList<T> operator+(const QList<T> &other) const
// QList<T> & operator+=(const QList<T> &other)
// QList<T> & operator+=(const T &value)
// QList<T> & operator<<(const QList<T> &other)
// QList<T> & operator<<(const T &value)
// QList<T> & operator=(const QList<T> &other)
// QList & operator=(QList<T> &&other)
// bool operator==(const QList<T> &other) const
// T & operator[](int i)
// const T & operator[](int i) const

/**************************************************************************************************/

#ifndef QC_MANUAL_INSTANTIATION
#include "database_row_list.hxx"
#endif

/**************************************************************************************************/

#endif /* __DATABASE_ROW_LIST_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
