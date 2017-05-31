// -*- mode: c++ -*-
/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire
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

#ifndef __JSON_ADAPTATOR_H__
#define __JSON_ADAPTATOR_H__

/**************************************************************************************************/

#include <QJsonDocument>
#include <QString>

/**************************************************************************************************/

// Fixme: to_json cannot be const if e.g. it modifies internal cache ...

class QcJsonSchemaTraits
{
public:
  void load_json(const QString & json_path); // Fixme: throw ???
  void to_json(const QString & json_path); // Fixme: throw ??? // const

  virtual void load_json_document(const QJsonDocument & json_document) = 0;
  virtual QJsonDocument to_json_document() = 0; // const
};

/**************************************************************************************************/

#endif /* __JSON_ADAPTATOR_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
