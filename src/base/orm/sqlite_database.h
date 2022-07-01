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

#ifndef __SQLITE_DATABASE_H__
#define __SQLITE_DATABASE_H__

/**************************************************************************************************/

#include "orm/database.h"

/**************************************************************************************************/

class QoSqliteDatabase : public QoDatabase
{
public:
  QoSqliteDatabase(const QString & sqlite_path, bool use_spatialite = false);
  virtual ~QoSqliteDatabase();

  bool created() { return m_created; }

private:
  void open();
  void init_spatialite();

  virtual bool move_database(const QString & new_path, bool commit = true);

private:
  QString m_sqlite_path;
  bool m_created = false;
  bool m_use_spatialite;
};

/**************************************************************************************************/

#endif /* __SQLITE_DATABASE_H__ */
