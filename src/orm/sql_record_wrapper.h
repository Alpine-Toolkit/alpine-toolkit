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

#ifndef __SQL_RECORD_WRAPPER_H__
#define __SQL_RECORD_WRAPPER_H__

/**************************************************************************************************/

#include <QByteArray>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QVariant>

/**************************************************************************************************/

class QcSqlRecordWrapper
{
public:
  QcSqlRecordWrapper(const QSqlRecord & record)
    : m_record(record)
  {}

  const QSqlRecord & record() const { return m_record; }

  bool is_empty() const { return m_record.isEmpty(); }
  bool is_not_empty() const { return not is_empty(); }

  int to_int(int position = 0) const {
    return m_record.value(position).toInt();
  }

  QByteArray to_byte_array(int position = 0) const {
    return m_record.value(position).toByteArray();
  }

  QString to_string(int position = 0) const {
    return m_record.value(position).toString();
  }

private:
  const QSqlRecord & m_record;
};

// Fixme: same QSqlQuery ?

/**************************************************************************************************/

#endif /* __SQL_RECORD_WRAPPER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
