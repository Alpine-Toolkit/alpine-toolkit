// -*- mode: c++ -*-
/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef __JSON_ADAPTATOR_H__
#define __JSON_ADAPTATOR_H__

/**************************************************************************************************/

#include <QJsonDocument>
#include <QString>

/**************************************************************************************************/

// Fixme: to_json cannot be const if e.g. it modifies internal cache ...

class QoJsonSchemaTraits
{
public:
  void load_json(const QString & json_path); // Fixme: throw ???
  void to_json(const QString & json_path); // Fixme: throw ??? // const

  virtual void load_json_document(const QJsonDocument & json_document) = 0;
  virtual QJsonDocument to_json_document() = 0; // const
};

/**************************************************************************************************/

#endif /* __JSON_ADAPTATOR_H__ */
