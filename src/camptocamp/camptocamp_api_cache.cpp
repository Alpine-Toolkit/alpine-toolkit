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

#include "camptocamp_api_cache.h"

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

C2cApiCache::C2cApiCache(const QString & sqlite_path)
  : QcSqliteDatabase(sqlite_path),
    QcDatabaseSchema(*((QcSqliteDatabase *) this)), // Fixme: ???
    m_metadata_table(nullptr),
    m_document_table(nullptr)
{
  // Fixme: migrate table using VERSION

  QcSchema metadata_schema(METADATA);
  QcSchemaField key_field(KEY, QLatin1String("QString"), QLatin1String("TEXT"));
  key_field.set_nullable(false);
  metadata_schema << key_field;
  metadata_schema << QcSchemaField(VALUE, QLatin1String("QString"), QLatin1String("TEXT"));
  m_metadata_table = &register_table(metadata_schema);

  QcSchema document_schema(DOCUMENT);
  // # https://www.sqlite.org/autoinc.html
  // # Fixme: how to handle auto-increment overflow ?
  QcSchemaField id_field(ID, QLatin1String("int"), QLatin1String("INTEGER"));
  id_field.set_nullable(false);
  document_schema << id_field;
  document_schema << QcSchemaField(DATA, QLatin1String("QByteArray"), QLatin1String("BLOB")); // JSON HIDDEN
  m_document_table = &register_table(document_schema);
}

C2cApiCache::~C2cApiCache()
{}

QString
C2cApiCache::read_metadata(const QString & key)
{
  QVariantHash kwargs;
  kwargs[KEY] = key;
  QSqlRecord record = m_metadata_table->select_one(QStringList(VALUE), kwargs);
  return record.value(0).toString();
}

void
C2cApiCache::init_metadata(const QString & key, const QString & value)
{
  QVariantHash kwargs;
  kwargs[KEY] = key;
  kwargs[VALUE] = value;
  m_metadata_table->insert(kwargs);
}

void
C2cApiCache::update_metadata(const QString & key, const QString & value)
{
  QVariantHash kwargs_where;
  kwargs_where[KEY] = key;
  QVariantHash kwargs_update;
  kwargs_update[VALUE] = value;
  m_metadata_table->update(kwargs_update, kwargs_where);
}

void
C2cApiCache::init()
{
  QVariantHash kwargs;

  // Set version
  init_metadata(VERSION, QString::number(1));

  // Set Login
  init_metadata(USERNAME, NULL_STRING);
  init_metadata(PASSWORD, NULL_STRING);
}

C2cLogin
C2cApiCache::login() // Fixme: const
{
  QString username = read_metadata(USERNAME);
  QString password = read_metadata(PASSWORD);
  return C2cLogin(username, password);
}

void
C2cApiCache::save_login(const C2cLogin & login)
{
  update_metadata(USERNAME, login.username());
  update_metadata(PASSWORD, login.password()); // Fixme: clear password !
  commit();
}

void
C2cApiCache::save_document(const C2cDocument & document)
{
  unsigned int document_id = document.id();
  if (has_document(document_id)) {
    QVariantHash kwargs_where;
    kwargs_where[ID] = document_id;
    QVariantHash kwargs_update;
    kwargs_update[DATA] = document.to_json();
    m_document_table->update(kwargs_update, kwargs_where);
    qInfo() << "Updated document " << document_id << " in cache";
  } else  {
    QVariantHash kwargs;
    kwargs[ID] = document_id;
    kwargs[DATA] = document.to_json();
    m_document_table->insert(kwargs);
    qInfo() << "Inserted document " << document_id << " in cache";
  }
}

bool
C2cApiCache::has_document(unsigned int document_id) const
{
  QVariantHash kwargs;
  kwargs[ID] = document_id;
  // Fixme: count
  QSqlRecord record = m_document_table->select_one(QStringList(ID), kwargs);
  return record.isEmpty() == false;
}

C2cDocument *
C2cApiCache::get_document(unsigned int document_id) const
{
  QVariantHash kwargs;
  kwargs[ID] = document_id;
  QSqlRecord record = m_document_table->select_one(QStringList(DATA), kwargs);
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
