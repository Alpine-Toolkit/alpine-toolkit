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

#ifndef __DATABASE_SHEMA_H__
#define __DATABASE_SHEMA_H__

/**************************************************************************************************/

// #include <QObject>

#include "database/database.h"
#include "database/database_table.h"
#include "database/schema.h"

/**************************************************************************************************/

class QcDatabaseSchema // : QObject
{
public:
  QcDatabaseSchema(QcDatabase & database); // register tables in subclass
  // T(const QList<QcSchema> & schemas);
  ~QcDatabaseSchema();

  QcDatabaseTable & register_table(const QString & name);
  QcDatabaseTable & register_table(const QcSchema & schema);

  QcDatabaseTable & get_table(const QString & name) { return m_tables[name]; } // Fixme: wrong name ?
  QcDatabaseTable & operator[](const QString & name) { return get_table(name); }

  // QcDatabaseTable * table() { return m_table; }

private:
  QcDatabase & m_database;
  QHash<QString, QcDatabaseTable> m_tables; // => QcDatabaseTable() => QcDatabase * Fixme: QcDatabaseTable * solve it
  // QcDatabaseTable * m_table;
};

/**************************************************************************************************/

#endif /* __DATABASE_SHEMA_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
