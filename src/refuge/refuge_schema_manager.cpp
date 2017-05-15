/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
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
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include "refuge_schema_manager.h"

#include "phonetic_algorithm/phonetic_algorithm.h"

// #include "refuge_sqlite_database.h"

#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QtDebug>

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/



/**************************************************************************************************/

RefugeSchemaManager::RefugeSchemaManager()
  : SchemaManager(),
    m_refuge_cache()
{}

RefugeSchemaManager::RefugeSchemaManager(const QString & json_path)
  : RefugeSchemaManager()
{
  load_json(json_path);
}

RefugeSchemaManager::RefugeSchemaManager(const QJsonDocument & json_document)
 : RefugeSchemaManager()
{
  load_json_document(json_document);
}

RefugeSchemaManager::~RefugeSchemaManager()
{}

void
RefugeSchemaManager::load_json_document(const QJsonDocument & json_document)
{
  QJsonArray array = json_document.array();

  for (const auto & json_value : array) {
    RefugePtr refuge(json_value.toObject());
    m_refuge_cache.add(refuge);
    m_refuges << refuge;
    m_soundex_map.insert(soundex_fr(refuge->short_name()), refuge);
  }

  m_filtered_refuges = m_refuges;
  m_refuge_model.set_items(m_refuges);
}

QJsonDocument
RefugeSchemaManager::to_json_document() const
{
  QJsonArray array;

  for (const auto & refuge : m_refuge_cache.items())
    array << refuge->to_json();

  return QJsonDocument(array);
}

void
RefugeSchemaManager::to_sql(const QString & sqlite_path)
{
  // RefugeSqliteDatabase refuge_sqlite_database(sqlite_path);
  // RefugeSchema & refuge_schema = refuge_sqlite_database.schema();

  // for (const auto & refuge : ...)
  //   refuge_schema.add_ptr(refuge);
}

QList<QObject *>
RefugeSchemaManager::refuges_as_object_list() // const
{
  qInfo() << "RefugeSchemaManager::refuges_as_object_list";

  QList<QObject *> list;

  for (auto & refuge : m_filtered_refuges)
    list << refuge.data();

  return list;
}

QQmlListProperty<Refuge>
RefugeSchemaManager::refuge_list_property()
{
  qInfo() << "RefugeSchemaManager::refuge_list_property";
  return QQmlListProperty<Refuge>(this,
                                  nullptr, // data
                                  &RefugeSchemaManager::refuge_list_property_count,
                                  &RefugeSchemaManager::refuge_list_property_at);
}

int
RefugeSchemaManager::refuge_list_property_count(QQmlListProperty<Refuge> * list)
{
  qInfo() << "RefugeSchemaManager::refuge_list_property_count";
  RefugeSchemaManager * refuge_schema_manager = qobject_cast<RefugeSchemaManager *>(list->object);
  return refuge_schema_manager->m_filtered_refuges.size();
}

Refuge *
RefugeSchemaManager::refuge_list_property_at(QQmlListProperty<Refuge> * list, int index)
{
  qInfo() << "RefugeSchemaManager::refuge_list_property_at";
  RefugeSchemaManager * refuge_schema_manager = qobject_cast<RefugeSchemaManager *>(list->object);
  RefugePtr & refuge = refuge_schema_manager->m_filtered_refuges[index];
  return refuge.data();
}

void
RefugeSchemaManager::filter_refuge_list(const QString & query)
{
  // ...

  // #include <algorithm>
  // std::sort(refuges.begin(), refuges.end()); // , qLess<Refuge *>()
}

/**************************************************************************************************/

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
