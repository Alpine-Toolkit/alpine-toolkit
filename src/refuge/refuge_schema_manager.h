// -*- mode: c++ -*-

/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the QtCarto library.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $ALPINE_TOOLKIT_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __REFUGE_SCHEMA_MANAGER_H__
#define __REFUGE_SCHEMA_MANAGER_H__

/**************************************************************************************************/

#include "full_text_search/indexer.h"
#include "orm/schema_manager.h"
#include "refuge/refuge_schema.h"

#include <QQmlListProperty>
#include<QHash>
#include<QJsonDocument>
#include<QObject>
#include<QString>

/**************************************************************************************************/

// Q_DECLARE_METATYPE(Refuge)
// Q_DECLARE_METATYPE(Refuge*)

/**************************************************************************************************/

class RefugeSchemaManager : public SchemaManager
{
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<Refuge> refuges READ refuge_list_property NOTIFY refugeListChanged)

public:
  RefugeSchemaManager();
  RefugeSchemaManager(const QString & json_path);
  RefugeSchemaManager(const QJsonDocument & json_document);
  // RefugeSchemaManager(const class RefugeSchemaManager & other);
  ~RefugeSchemaManager();

  // RefugeSchemaManager & operator=(const RefugeSchemaManager & other);

  void load_json_document(const QJsonDocument & json_document);
  QJsonDocument to_json_document(); // const

  void to_sql(const QString & sqlite_path);

  const Refuge::PtrList refuges() const { return m_refuge_cache.items(); }

  const Refuge::PtrList & refuges_list() const { return m_refuges; }
  Q_INVOKABLE QList<QObject *> refuges_as_object_list(); // const
  Q_INVOKABLE QVariant refuges_as_object_list_variant() { return QVariant::fromValue(refuges_as_object_list()); } // const

  Q_INVOKABLE void filter_refuge_list(const QString & query);

  Q_INVOKABLE RefugeModel * model() { return &m_refuge_model; }

signals:
  void refugeListChanged();

private:
  // QQmlListProperty can only be used for lists of QObject-derived object pointers.
  // Refuges must be registered
  QQmlListProperty<Refuge> refuge_list_property();
  static int refuge_list_property_count(QQmlListProperty<Refuge> * list);
  static Refuge * refuge_list_property_at(QQmlListProperty<Refuge> * list, int index);

private:
  RefugeCache m_refuge_cache;
  Refuge::PtrList m_refuges;
  Refuge::PtrList m_filtered_refuges;
  DocumentIndexer<Refuge> m_refuge_index;
  RefugeModel m_refuge_model;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

#endif /* __REFUGE_SCHEMA_MANAGER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
