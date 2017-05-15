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
#include <QSet>
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
    QString soundex = soundex_fr(refuge->short_name());
    qInfo() << refuge->short_name() << soundex;
    m_soundex_map.insert(soundex, refuge);
  }

  m_filtered_refuges = m_refuges;
  m_refuge_model.set_items(m_refuges);

  // #include <algorithm>
  // std::sort(refuges.begin(), refuges.end()); // , qLess<Refuge *>()
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
  qInfo() << "RefugeSchemaManager::refuge_list_property_at" << index;
  RefugeSchemaManager * refuge_schema_manager = qobject_cast<RefugeSchemaManager *>(list->object);
  RefugePtr & refuge = refuge_schema_manager->m_filtered_refuges[index];
  return refuge.data();
}

void
RefugeSchemaManager::filter_refuge_list(const QString & query)
{
  qInfo() << "filter_refuge_list" << query;

  if (query.isEmpty()) {
    m_filtered_refuges = m_refuges;
  } else {
    m_filtered_refuges.clear();
    QSet<RefugePtr> matches;
    QString soundex = soundex_fr(query);
    qInfo() << "soundex" << query << soundex;
    if (m_soundex_map.contains(soundex)) {
      auto & refuge = m_soundex_map[soundex];
      matches << refuge;
    }
    for (const auto & refuge : m_refuges) {
      QString name = refuge->name();
      QString normalized_name = name.normalized(QString::NormalizationForm_D);
      QString alpha_name;
      for (const auto & c : normalized_name)
        if (c.isLetterOrNumber() or c.isSpace())
          alpha_name += c;
      qInfo() << name << alpha_name;
      if (alpha_name.contains(query, Qt::CaseInsensitive))
        matches << refuge;
    }
    m_filtered_refuges = matches.values();
  }

  emit refugeListChanged();
}

// rowCount
// roleNames
// rowCount
// data QModelIndex(0,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(0,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(1,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(0,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(1,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(0,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(1,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(1,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(2,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(2,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(2,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(3,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(3,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(3,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(4,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(4,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(4,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(5,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(5,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(5,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(6,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(6,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(6,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(7,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(7,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(7,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(8,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(8,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(8,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(9,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(9,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(9,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(10,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(10,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(10,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(11,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(11,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(11,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(12,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(12,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(12,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(13,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(13,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(13,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(14,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(14,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(14,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(15,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(15,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(15,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(16,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(16,0,0x0,RefugeModel(0x1f19c28)) 258
// rowCount
// data QModelIndex(16,0,0x0,RefugeModel(0x1f19c28)) 269
// rowCount
// data QModelIndex(17,0,0x0,RefugeModel(0x1f19c28)) 269

// RefugeSchemaManager::refuge_list_property
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 0
// RefugeSchemaManager::refuge_list_property_at 0
// RefugeSchemaManager::refuge_list_property_at 1
// RefugeSchemaManager::refuge_list_property_at 0
// RefugeSchemaManager::refuge_list_property_at 1
// RefugeSchemaManager::refuge_list_property_at 0
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 1
// RefugeSchemaManager::refuge_list_property_at 1
// RefugeSchemaManager::refuge_list_property_at 2
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 2
// RefugeSchemaManager::refuge_list_property_at 2
// RefugeSchemaManager::refuge_list_property_at 3
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 3
// RefugeSchemaManager::refuge_list_property_at 3
// RefugeSchemaManager::refuge_list_property_at 4
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 4
// RefugeSchemaManager::refuge_list_property_at 4
// RefugeSchemaManager::refuge_list_property_at 5
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 5
// RefugeSchemaManager::refuge_list_property_at 5
// RefugeSchemaManager::refuge_list_property_at 6
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 6
// RefugeSchemaManager::refuge_list_property_at 6
// RefugeSchemaManager::refuge_list_property_at 7
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 7
// RefugeSchemaManager::refuge_list_property_at 7
// RefugeSchemaManager::refuge_list_property_at 8
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 8
// RefugeSchemaManager::refuge_list_property_at 8
// RefugeSchemaManager::refuge_list_property_at 9
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 9
// RefugeSchemaManager::refuge_list_property_at 9
// RefugeSchemaManager::refuge_list_property_at 10
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 10
// RefugeSchemaManager::refuge_list_property_at 10
// RefugeSchemaManager::refuge_list_property_at 11
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 11
// RefugeSchemaManager::refuge_list_property_at 11
// RefugeSchemaManager::refuge_list_property_at 12
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 12
// RefugeSchemaManager::refuge_list_property_at 12
// RefugeSchemaManager::refuge_list_property_at 13
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 13
// RefugeSchemaManager::refuge_list_property_at 13
// RefugeSchemaManager::refuge_list_property_at 14
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 14
// RefugeSchemaManager::refuge_list_property_at 14
// RefugeSchemaManager::refuge_list_property_at 15
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 15
// RefugeSchemaManager::refuge_list_property_at 15
// RefugeSchemaManager::refuge_list_property_at 16
// RefugeSchemaManager::refuge_list_property_count
// RefugeSchemaManager::refuge_list_property_at 16
// RefugeSchemaManager::refuge_list_property_at 16
// RefugeSchemaManager::refuge_list_property_at 17

/**************************************************************************************************/

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
