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

#ifndef __DATABASE_ROW_HXX__
#define __DATABASE_ROW_HXX__

/**************************************************************************************************/

#include "database_row.h" // for checker

/**************************************************************************************************/

template<class S>
QoRow<S>::QoRow()
  : QoRowTraits(),
    m_bits(number_of_fields())
{}

template<class S>
QoRow<S>::QoRow(const QoRow & other)
  : QoRow()
    // m_bits(other.m_bits) // Fixme: ???
{
    Q_UNUSED(other);
}

/**************************************************************************************************/

/*
template<class S>
QoRowWithId<S>::QoRowWithId()
  : QoRow<S>()
{}

template<class S>
QoRowWithId<S>::QoRowWithId(const QoRowWithId & other)
  : QoRow<S>(static_cast<const QoRow<S> &>(other)),
    m_id(other.m_id)
{}

template<class S>
QoRowWithId<S>::QoRowWithId(const QJsonObject & json_object)
 : QoRowWithId()
{}

template<class S>
QoRowWithId<S>::QoRowWithId(const QVariantHash & variant_hash)
 : QoRowWithId()
{
  m_id = variant_hash[QLatin1String("id")].toInt();
}

template<class S>
QoRowWithId<S>::QoRowWithId(const QVariantList & variants)
 : QoRowWithId()
{
  m_id = variants[0].toInt();
}

template<class S>
QoRowWithId<S>::QoRowWithId(const QSqlRecord & record)
 : QoRowWithId()
{
  m_id = record.value(0).toInt();
}

template<class S>
QoRowWithId<S>::QoRowWithId(const QSqlQuery & query)
 : QoRowWithId()
{
  m_id = query.value(0).toInt();
}

template<class S>
QoRowWithId<S>::~QoRowWithId()
{}

template<class S>
QoRowWithId<S> &
QoRowWithId<S>::operator=(const QoRowWithId & other)
{
  if (this != &other) {
    m_id = other.m_id;
  }

  return *this;
}

template<class S>
bool
QoRowWithId<S>::operator==(const QoRowWithId & other)
{
  return m_id == other.m_id;
}

template<class S>
void
QoRowWithId<S>::detach()
{
  m_id = INVALID_ID;
  QoRowTraits::set_database_schema(nullptr);
}
*/

/*
template<class S>
void
QoRowWithId<S>::set_id(int value)
{
  if (m_id != value) {
    m_id = value;
    emit idChanged();
  }
}
*/

/**************************************************************************************************/

#endif /* __DATABASE_ROW_HXX__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
