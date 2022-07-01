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

#include "sql_query_model.h"
#include "alpine_toolkit.h"

#include <QtDebug>
#include <QSqlRecord>
#include <QSqlField>

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

/*
void
SqlQueryModel::set_query(const QSqlQuery & query)
{
  // Fixme: Qt6 setQuery(QSqlQuery &&query)
  QSqlQueryModel::setQuery(query);
  generate_role_names();
}
*/

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
  qATInfo() << index << role << value;

  return value;
}
