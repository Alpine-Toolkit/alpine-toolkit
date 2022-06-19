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

#ifndef __NETWORK_DATABASE_H__
#define __NETWORK_DATABASE_H__

/**************************************************************************************************/

#include "orm/database.h"
#include "orm/database_connection.h"

/**************************************************************************************************/

class QoNetworkDatabase : public QoDatabase
{
public:
  QoNetworkDatabase();
  virtual ~QoNetworkDatabase();

  void open(const QoDatabaseConnectionData & connection_data);

  bool create_extension(const QString & extension);

  virtual QString driver_name() const = 0;
};

/**************************************************************************************************/

#endif /* __NETWORK_DATABASE_H__ */
