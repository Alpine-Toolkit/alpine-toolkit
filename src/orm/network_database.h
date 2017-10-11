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
