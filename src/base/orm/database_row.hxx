// -*- mode: c++ -*-
/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
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
