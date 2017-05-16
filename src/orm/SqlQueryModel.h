// -*- mode: c++ -*-

/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire.
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

#ifndef __SQUERY_MODEL_H__
#define __SQUERY_MODEL_H__

/**************************************************************************************************/

#include <QSqlQueryModel>

/**************************************************************************************************/

class SqlQueryModel : public QSqlQueryModel
{
  Q_OBJECT

public:
  explicit SqlQueryModel(QObject *parent = 0);

  void set_query(const QString & query, const QSqlDatabase & db = QSqlDatabase());
  void set_query(const QSqlQuery & query);
  QVariant data(const QModelIndex & index, int role) const;
  QHash<int, QByteArray> roleNames() const { return m_role_names; }

private:
  void generate_role_names();
  QHash<int, QByteArray> m_role_names;
};

#endif /* __SQUERY_MODEL_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
