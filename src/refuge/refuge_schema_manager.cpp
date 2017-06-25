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

#include "refuge_schema_manager.h"

#include "full_text_search/phonetic_encoder.h"

// #include "refuge_sqlite_database.h"

#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QSet>
#include <QtDebug>

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

RefugeSchemaManager::RefugeSchemaManager()
  : SchemaManager(),
    m_refuge_cache(),
    m_refuges(),
    m_filtered_refuges(),
    m_refuge_index(true), // use phonetic encoder
    m_refuge_model()
{
  Tokenizer & tokenizer = m_refuge_index.tokenizer();
  tokenizer << new PreLanguageFilter();
  tokenizer << new CaseFoldingFilter();
  tokenizer << new AccentFoldingFilter(); // Must run language filter before !
  tokenizer << new LocalizedStopWordFilter("../ressources/data/stop-words.json");
  // tokenizer << new LocalizedStemmerFilter(); // is not suited for names or localities
}

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
    // qInfo() << refuge->short_name() << soundex;
    TextDocument short_name(QLocale::French, refuge->short_name());
    m_refuge_index.insert(short_name, refuge.ptr());
  }

  m_filtered_refuges = m_refuges;
  m_refuge_model.set_items(m_refuges);

  // #include <algorithm>
  // std::sort(refuges.begin(), refuges.end()); // , qLess<Refuge *>()
}

QJsonDocument
RefugeSchemaManager::to_json_document() // const
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
  // qInfo() << "RefugeSchemaManager::refuges_as_object_list";

  QList<QObject *> list;

  for (auto & refuge : m_filtered_refuges)
    list << refuge.data();

  return list;
}

QQmlListProperty<Refuge>
RefugeSchemaManager::refuge_list_property()
{
  // qInfo() << "RefugeSchemaManager::refuge_list_property";
  return QQmlListProperty<Refuge>(this,
                                  nullptr, // data
                                  &RefugeSchemaManager::refuge_list_property_count,
                                  &RefugeSchemaManager::refuge_list_property_at);
}

int
RefugeSchemaManager::refuge_list_property_count(QQmlListProperty<Refuge> * list)
{
  // qInfo() << "RefugeSchemaManager::refuge_list_property_count";
  RefugeSchemaManager * refuge_schema_manager = qobject_cast<RefugeSchemaManager *>(list->object);
  return refuge_schema_manager->m_filtered_refuges.size();
}

Refuge *
RefugeSchemaManager::refuge_list_property_at(QQmlListProperty<Refuge> * list, int index)
{
  // qInfo() << "RefugeSchemaManager::refuge_list_property_at" << index;
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
    auto matches = m_refuge_index.query(TextDocument(QLocale::French, query), true); // use like
    for (const auto & match : matches) {
      qInfo() << query << "Matched" << match.pertinence() << match.document()->short_name();
      m_filtered_refuges << match.document();
    }
    // m_filtered_refuges = matches.values(); // RefugePtr versus QSharedPointer<Refuge>
  }

  emit refugeListChanged();
}

/**************************************************************************************************/

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
