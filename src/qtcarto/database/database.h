// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

// Fixme: upgrade to ORM

/**************************************************************************************************/

#ifndef __QC_DATABASE_H__
#define __QC_DATABASE_H__

/**************************************************************************************************/

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QVariant>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcDatabase
{
public:
  typedef QHash<QString, QVariant> KeyValuePair;

public:
  QcDatabase();
  virtual ~QcDatabase();

  virtual void create_tables() = 0;

  inline QSqlDatabase & database () { return m_database; }

  inline bool transaction() { return m_database.transaction(); }
  inline bool commit() { return m_database.commit(); }
  inline QSqlQuery new_query() const { return QSqlQuery(m_database); }

  bool execute_query(const QString & sql_query);
  bool execute_queries(const QStringList & sql_queries, bool commit = true);

  QString format_kwarg(const KeyValuePair & kwargs, const QString & sperator = QStringLiteral(","));
  QString format_simple_where(const KeyValuePair & kwargs);

  QSqlQuery select(const QString & table, const QStringList & fields, const QString & where = QStringLiteral(""));
  QSqlRecord select_one(const QString & table, const QStringList & fields, const QString & where = QStringLiteral(""));
  QSqlQuery prepare_query(const QString & sql_query);
  QSqlQuery insert(const QString & table, const KeyValuePair & kwargs, bool commit = false);
  QSqlQuery update(const QString & table, const KeyValuePair & kwargs, const QString & where = QStringLiteral(""));
  QSqlQuery delete_row(const QString & table, const QString & where);

protected:
  QSqlDatabase m_database;
};

/**************************************************************************************************/

struct QcDatabaseConnectionData
{
  QString host;
  int port;
  QString database;
  QString user;
  QString password;
};

/**************************************************************************************************/

class QcNetworkDatabase : public QcDatabase
{
public:
  QcNetworkDatabase();
  virtual ~QcNetworkDatabase();

  void open(const QcDatabaseConnectionData & connection_data);

  bool create_extension(const QString & extension);

  virtual QString driver_name() const = 0;
};

/**************************************************************************************************/

class QcSqliteDatabase : public QcDatabase
{
public:
  QcSqliteDatabase();
  virtual ~QcSqliteDatabase();

  bool open(QString sqlite_path);
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_DATABASE_H__ */
