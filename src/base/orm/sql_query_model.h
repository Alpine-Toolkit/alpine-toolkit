// -*- mode: c++ -*-

/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef __SQL_QUERY_MODEL_H__
#define __SQL_QUERY_MODEL_H__

/**************************************************************************************************/

#include <QSqlQueryModel>

/**************************************************************************************************/

class SqlQueryModel : public QSqlQueryModel
{
  Q_OBJECT

public:
  explicit SqlQueryModel(QObject *parent = 0);

  void set_query(const QString & query, const QSqlDatabase & db = QSqlDatabase());
  // Fixme: Qt6
  // void set_query(const QSqlQuery & query);
  QVariant data(const QModelIndex & index, int role) const;
  QHash<int, QByteArray> roleNames() const { return m_role_names; }

private:
  void generate_role_names();
  QHash<int, QByteArray> m_role_names;
};

#endif /* __SQL_QUERY_MODEL_H__ */
