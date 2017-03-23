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

#include "camptocamp_cache.h"

#include <QJsonDocument>
#include <QSqlError>
#include <QtDebug>

/**************************************************************************************************/

// https://www.sqlite.org/json1.html

/**************************************************************************************************/

static const QString DATA = "data";
static const QString DOCUMENT = "document";
static const QString ID = "id";
static const QString KEY = "key";
static const QString METADATA = "metadata";
static const QString NULL_STRING = "";
static const QString PASSWORD = "password";
static const QString USERNAME = "username";
static const QString VALUE = "value";
static const QString VERSION = "version";

C2cCache::C2cCache(const QString & sqlite_path)
{
  bool created = open(sqlite_path);

  // if (!created)
}

C2cCache::~C2cCache()
{}

void
C2cCache::create_tables()
{
  qInfo() << "Create Table"; // << sqlite_path();

  // # https://www.sqlite.org/autoinc.html
  // # Fixme: how to handle auto-increment overflow ?

  // Fixme: migrate table using VERSION

  QList<QString> schemas;

  const QString metadata_schema =
    "CREATE TABLE metadata ("
    "key TEXT NOT NULL,"
    "value TEXT"
    ")";
  schemas << metadata_schema;

  const QString document_schema =
    "CREATE TABLE document ("
    "id INTEGER NOT NULL,"
    "data BLOB" // JSON HIDDEN
    ")";
  schemas << document_schema;

  QSqlQuery query = new_query();
  for (const auto & sql_query : schemas)
    if (!query.exec(sql_query))
      qWarning() << query.lastError().text();

  init();
  commit();
}

QString
C2cCache::read_metadata(const QString & key)
{
  KeyValuePair kwargs;
  kwargs[KEY] = key;
  QString where = format_simple_where(kwargs);
  QSqlRecord record = select_one(METADATA, QStringList(VALUE), where);
  return record.value(0).toString();
}

void
C2cCache::init_metadata(const QString & key, const QString & value)
{
  KeyValuePair kwargs;
  kwargs[KEY] = key;
  kwargs[VALUE] = value;
  insert(METADATA, kwargs);
}

void
C2cCache::update_metadata(const QString & key, const QString & value)
{
  KeyValuePair kwargs_where;
  kwargs_where[KEY] = key;
  KeyValuePair kwargs_update;
  kwargs_update[VALUE] = value;
  QString where = format_simple_where(kwargs_where);
  update(METADATA, kwargs_update, where);
}

void
C2cCache::init()
{
  KeyValuePair kwargs;

  // Set version
  init_metadata(VERSION, QString::number(1));

  // Set Login
  init_metadata(USERNAME, NULL_STRING);
  init_metadata(PASSWORD, NULL_STRING);
}

C2cLogin
C2cCache::login() // Fixme: const
{
  QString username = read_metadata(USERNAME);
  QString password = read_metadata(PASSWORD);
  return C2cLogin(username, password);
}

void
C2cCache::save_login(const C2cLogin & login)
{
  update_metadata(USERNAME, login.username());
  update_metadata(PASSWORD, login.password()); // Fixme: clear password !
  commit();
}

void
C2cCache::save_document(const C2cDocument & document)
{
  unsigned int document_id = document.id();
  if (has_document(document_id)) {
    KeyValuePair kwargs_where;
    kwargs_where[ID] = document_id;
    KeyValuePair kwargs_update;
    kwargs_update[DATA] = document.to_json();
    QString where = format_simple_where(kwargs_where);
    update(DOCUMENT, kwargs_update, where);
    qInfo() << "Updated document " << document_id << " in cache";
  } else  {
    KeyValuePair kwargs;
    kwargs[ID] = document_id;
    kwargs[DATA] = document.to_json();
    insert(DOCUMENT, kwargs);
    qInfo() << "Inserted document " << document_id << " in cache";
  }
}

bool
C2cCache::has_document(unsigned int document_id) const
{
  KeyValuePair kwargs;
  kwargs[ID] = document_id;
  // Fixme: count
  QString where = format_simple_where(kwargs);
  QSqlRecord record = select_one(DOCUMENT, QStringList(ID), where);
  return record.isEmpty() == false;
}

C2cDocument *
C2cCache::get_document(unsigned int document_id) const
{
  KeyValuePair kwargs;
  kwargs[ID] = document_id;
  QString where = format_simple_where(kwargs);
  QSqlRecord record = select_one(DOCUMENT, QStringList(DATA), where);
  if (record.isEmpty())
    return nullptr;
  else {
    QByteArray json_data = record.value(0).toByteArray();
    QJsonDocument json_document = QJsonDocument::fromJson(json_data);
    return C2cDocument(json_document.object()).cast(); // Fixme: delete
  }
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
