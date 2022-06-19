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

#ifndef __SCHEMA_MANAGER_H__
#define __SCHEMA_MANAGER_H__

/**************************************************************************************************/

#include "orm/json_adaptator.h"

#include <QObject>

/**************************************************************************************************/

class SchemaManager : public QObject, public QoJsonSchemaTraits
{
  Q_OBJECT

public:
  SchemaManager();
  ~SchemaManager();
};

/**************************************************************************************************/

#endif /* __SCHEMA_MANAGER_H__ */
