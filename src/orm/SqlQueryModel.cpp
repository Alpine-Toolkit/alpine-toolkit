// -*- mode: c++ -*-

/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire.
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

#include <QtDebug>
#include <QSqlRecord>
#include <QSqlField>

#include "SqlQueryModel.h"

/**************************************************************************************************/

SqlQueryModel::SqlQueryModel(QObject *parent)
  : QSqlQueryModel(parent)
{
}

void
SqlQueryModel::set_query(const QString & query, const QSqlDatabase & db)
{
  QSqlQueryModel::setQuery(query, db);
  generate_role_names();
}

void
SqlQueryModel::set_query(const QSqlQuery & query)
{
  QSqlQueryModel::setQuery(query);
  generate_role_names();
}

void
SqlQueryModel::generate_role_names()
{
  m_role_names.clear();
  for (int i = 0; i < record().count(); i++) {
    m_role_names.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
  }
}

QVariant
SqlQueryModel::data(const QModelIndex & index, int role) const
{
  QVariant value;

  if(role < Qt::UserRole) {
    value = QSqlQueryModel::data(index, role);
  }
  else {
    int column = role - Qt::UserRole - 1;
    QModelIndex model_index = this->index(index.row(), column);
    value = QSqlQueryModel::data(model_index, Qt::DisplayRole);
  }
  qInfo() << index << role << value;

  return value;
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
