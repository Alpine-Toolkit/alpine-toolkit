// This file was automatically generated by SqlOrm

/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine Toolkit software.
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

#include "document.h"
#include "alpine_toolkit.h"

#include "orm/database_query.h"
#include "orm/type_conversion.h"

#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE


DocumentSchema::DocumentSchema()
: QoSchema(QLatin1String("Document"), QLatin1String("document"))
{
  {
    QoSchemaPrimaryKey field(
      QLatin1String("id"),
      QLatin1String("int"),
      QLatin1String("integer"),
      QLatin1String("id"),
      QLatin1String("id"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    field.set_nullable(false);
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("name"),
      QLatin1String("QString"),
      QLatin1String("text"),
      QLatin1String("name"),
      QLatin1String("name"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("author"),
      QLatin1String("QString"),
      QLatin1String("text"),
      QLatin1String("author"),
      QLatin1String("author"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("version"),
      QLatin1String("int"),
      QLatin1String("integer"),
      QLatin1String("version"),
      QLatin1String("version"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("date"),
      QLatin1String("QDateTime"),
      QLatin1String("integer"),
      QLatin1String("date"),
      QLatin1String("date"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("description"),
      QLatin1String("QString"),
      QLatin1String("text"),
      QLatin1String("description"),
      QLatin1String("description"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("url"),
      QLatin1String("QUrl"),
      QLatin1String("text"),
      QLatin1String("url"),
      QLatin1String("url"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("size"),
      QLatin1String("int"),
      QLatin1String("integer"),
      QLatin1String("size"),
      QLatin1String("size"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
}

DocumentSchema::~DocumentSchema()
{}

/**************************************************************************************************/

Document::Document()
  : QObject(),
    QoRow<DocumentSchema>(),
    m_id(),
    m_name(),
    m_author(),
    m_version(),
    m_date(),
    m_description(),
    m_url(),
    m_size()
{
}

Document::Document(const Document & other)
  : QObject(),
    QoRow<DocumentSchema>(other),
    m_id(other.m_id),
    m_name(other.m_name),
    m_author(other.m_author),
    m_version(other.m_version),
    m_date(other.m_date),
    m_description(other.m_description),
    m_url(other.m_url),
    m_size(other.m_size)
{
}

Document::Document(const QJsonObject & json_object)
 : Document()
{
  m_id = json_object[QLatin1String("id")].toInt();
  m_name = json_object[QLatin1String("name")].toString();
  m_author = json_object[QLatin1String("author")].toString();
  m_version = json_object[QLatin1String("version")].toInt();
  m_date = orm_type_conversion::load_datetime(json_object[QLatin1String("date")]);
  m_description = json_object[QLatin1String("description")].toString();
  m_url = json_object[QLatin1String("url")].toString();
  m_size = json_object[QLatin1String("size")].toInt();
}

Document::Document(const QVariantHash & variant_hash)
 : Document()
{
  m_id = variant_hash[QLatin1String("id")].toInt();
  m_name = variant_hash[QLatin1String("name")].toString();
  m_author = variant_hash[QLatin1String("author")].toString();
  m_version = variant_hash[QLatin1String("version")].toInt();
  m_date = variant_hash[QLatin1String("date")].toDateTime();
  m_description = variant_hash[QLatin1String("description")].toString();
  m_url = variant_hash[QLatin1String("url")].toUrl();
  m_size = variant_hash[QLatin1String("size")].toInt();
}

Document::Document(const QVariantList & variants)
 : Document()
{
  m_id = variants[0].toInt();
  m_name = variants[1].toString();
  m_author = variants[2].toString();
  m_version = variants[3].toInt();
  m_date = variants[4].toDateTime();
  m_description = variants[5].toString();
  m_url = variants[6].toUrl();
  m_size = variants[7].toInt();
}

Document::Document(const QSqlRecord & record)
 : QoRow<DocumentSchema>(record)
{
  m_id = record.value(0).toInt();
  m_name = record.value(1).toString();
  m_author = record.value(2).toString();
  m_version = record.value(3).toInt();
  m_date = orm_type_conversion::load_sql_datetime_as_epoch(record.value(4));
  m_description = record.value(5).toString();
  m_url = record.value(6).toUrl();
  m_size = record.value(7).toInt();
}

Document::Document(const QSqlQuery & query, int offset)
 : QoRow<DocumentSchema>(query)
{
  m_id = query.value(offset++).toInt();
  m_name = query.value(offset++).toString();
  m_author = query.value(offset++).toString();
  m_version = query.value(offset++).toInt();
  m_date = orm_type_conversion::load_sql_datetime_as_epoch(query.value(offset++));
  m_description = query.value(offset++).toString();
  m_url = query.value(offset++).toUrl();
  m_size = query.value(offset).toInt();
}

Document::~Document()
{
// qATInfo() << "--- Delete" << "Document" << *this;
}

// bit array ?
Document &
Document::operator=(const Document & other)
{
  if (this != &other) {
    QoRow<DocumentSchema>::operator=(other);
    m_id = other.m_id;
    m_name = other.m_name;
    m_author = other.m_author;
    m_version = other.m_version;
    m_date = other.m_date;
    m_description = other.m_description;
    m_url = other.m_url;
    m_size = other.m_size;
  }

  return *this;
}

// bit array ?
bool
Document::operator==(const Document & other) const
{
  if (not QoRow<DocumentSchema>::operator==(other))
    return false;
  if (m_id != other.m_id)
    return false;
  if (m_name != other.m_name)
    return false;
  if (m_author != other.m_author)
    return false;
  if (m_version != other.m_version)
    return false;
  if (m_date != other.m_date)
    return false;
  if (m_description != other.m_description)
    return false;
  if (m_url != other.m_url)
    return false;
  if (m_size != other.m_size)
    return false;

  return true;
}

void
Document::set_id(int value)
{
  if (m_id != value) {
    m_id = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::ID);

    emit idChanged();
    if (not is_changed)
      emit changed();
  }
}

void
Document::set_name(const QString & value)
{
  if (m_name != value) {
    m_name = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::NAME);

    emit nameChanged();
    if (not is_changed)
      emit changed();
  }
}

void
Document::set_author(const QString & value)
{
  if (m_author != value) {
    m_author = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::AUTHOR);

    emit authorChanged();
    if (not is_changed)
      emit changed();
  }
}

void
Document::set_version(int value)
{
  if (m_version != value) {
    m_version = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::VERSION);

    emit versionChanged();
    if (not is_changed)
      emit changed();
  }
}

void
Document::set_date(const QDateTime & value)
{
  if (m_date != value) {
    m_date = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::DATE);

    emit dateChanged();
    if (not is_changed)
      emit changed();
  }
}

void
Document::set_description(const QString & value)
{
  if (m_description != value) {
    m_description = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::DESCRIPTION);

    emit descriptionChanged();
    if (not is_changed)
      emit changed();
  }
}

void
Document::set_url(const QUrl & value)
{
  if (m_url != value) {
    m_url = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::URL);

    emit urlChanged();
    if (not is_changed)
      emit changed();
  }
}

void
Document::set_size(int value)
{
  if (m_size != value) {
    m_size = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::SIZE);

    emit sizeChanged();
    if (not is_changed)
      emit changed();
  }
}

QJsonObject
Document::to_json(bool only_changed) const
{
  QJsonObject json_object;

 if (only_changed) {
    if (is_id_modified())
      json_object.insert(QLatin1String("id"), QJsonValue(m_id));
    if (is_name_modified())
      json_object.insert(QLatin1String("name"), QJsonValue(m_name));
    if (is_author_modified())
      json_object.insert(QLatin1String("author"), QJsonValue(m_author));
    if (is_version_modified())
      json_object.insert(QLatin1String("version"), QJsonValue(m_version));
    if (is_date_modified())
      json_object.insert(QLatin1String("date"), orm_type_conversion::dump_datetime(m_date));
    if (is_description_modified())
      json_object.insert(QLatin1String("description"), QJsonValue(m_description));
    if (is_url_modified())
      json_object.insert(QLatin1String("url"), orm_type_conversion::dump_url(m_url));
    if (is_size_modified())
      json_object.insert(QLatin1String("size"), QJsonValue(m_size));
  } else {
    json_object.insert(QLatin1String("id"), QJsonValue(m_id));
    json_object.insert(QLatin1String("name"), QJsonValue(m_name));
    json_object.insert(QLatin1String("author"), QJsonValue(m_author));
    json_object.insert(QLatin1String("version"), QJsonValue(m_version));
    json_object.insert(QLatin1String("date"), orm_type_conversion::dump_datetime(m_date));
    json_object.insert(QLatin1String("description"), QJsonValue(m_description));
    json_object.insert(QLatin1String("url"), orm_type_conversion::dump_url(m_url));
    json_object.insert(QLatin1String("size"), QJsonValue(m_size));
  }

  return json_object;
}

QVariantHash
Document::to_variant_hash(bool only_changed) const
{
  QVariantHash variant_hash;

  if (only_changed) {
    if (is_id_modified())
      variant_hash[QLatin1String("id")] = m_id;
    if (is_name_modified())
      variant_hash[QLatin1String("name")] = m_name;
    if (is_author_modified())
      variant_hash[QLatin1String("author")] = m_author;
    if (is_version_modified())
      variant_hash[QLatin1String("version")] = m_version;
    if (is_date_modified())
      variant_hash[QLatin1String("date")] = m_date;
    if (is_description_modified())
      variant_hash[QLatin1String("description")] = m_description;
    if (is_url_modified())
      variant_hash[QLatin1String("url")] = m_url;
    if (is_size_modified())
      variant_hash[QLatin1String("size")] = m_size;
  } else {
    variant_hash[QLatin1String("id")] = m_id;
    variant_hash[QLatin1String("name")] = m_name;
    variant_hash[QLatin1String("author")] = m_author;
    variant_hash[QLatin1String("version")] = m_version;
    variant_hash[QLatin1String("date")] = m_date;
    variant_hash[QLatin1String("description")] = m_description;
    variant_hash[QLatin1String("url")] = m_url;
    variant_hash[QLatin1String("size")] = m_size;
  }

  return variant_hash;
}

QVariantList
Document::to_variant_list() const
{
  QVariantList variants;

  variants << m_id;
  variants << m_name;
  variants << m_author;
  variants << m_version;
  variants << m_date;
  variants << m_description;
  variants << m_url;
  variants << m_size;

  return variants;
}

QVariantHash
Document::to_variant_hash_sql(bool only_changed, bool duplicate) const
{
  QVariantHash variant_hash;

  if (only_changed) {
    if (is_id_modified())
      variant_hash[QLatin1String("id")] = m_id;
    if (is_name_modified())
      variant_hash[QLatin1String("name")] = m_name;
    if (is_author_modified())
      variant_hash[QLatin1String("author")] = m_author;
    if (is_version_modified())
      variant_hash[QLatin1String("version")] = m_version;
    if (is_date_modified())
      variant_hash[QLatin1String("date")] = orm_type_conversion::dump_sql_datetime_as_epoch(m_date);
    if (is_description_modified())
      variant_hash[QLatin1String("description")] = m_description;
    if (is_url_modified())
      variant_hash[QLatin1String("url")] = m_url;
    if (is_size_modified())
      variant_hash[QLatin1String("size")] = m_size;
  } else {
    if (duplicate)
      variant_hash[QLatin1String("id")] = m_id;
    variant_hash[QLatin1String("name")] = m_name;
    variant_hash[QLatin1String("author")] = m_author;
    variant_hash[QLatin1String("version")] = m_version;
    variant_hash[QLatin1String("date")] = orm_type_conversion::dump_sql_datetime_as_epoch(m_date);
    variant_hash[QLatin1String("description")] = m_description;
    variant_hash[QLatin1String("url")] = m_url;
    variant_hash[QLatin1String("size")] = m_size;
  }

  return variant_hash;
}

QVariantList
Document::to_variant_list_sql(bool duplicate) const
{
  QVariantList variants;

  if (duplicate)
    variants << m_id;
  variants << m_name;
  variants << m_author;
  variants << m_version;
  variants << orm_type_conversion::dump_sql_datetime_as_epoch(m_date);
  variants << m_description;
  variants << m_url;
  variants << m_size;

  return variants;
}

QVariant
Document::field(int position) const
{
  switch(position) {
   case Schema::Fields::ID:
     return m_id;
   case Schema::Fields::NAME:
     return m_name;
   case Schema::Fields::AUTHOR:
     return m_author;
   case Schema::Fields::VERSION:
     return m_version;
   case Schema::Fields::DATE:
     return m_date;
   case Schema::Fields::DESCRIPTION:
     return m_description;
   case Schema::Fields::URL:
     return m_url;
   case Schema::Fields::SIZE:
     return m_size;
   default:
     return QVariant(); // error
  }
}

void
Document::set_field(int position, const QVariant & value)
{
  switch(position) {
   case Schema::Fields::ID: {
     m_id = value.toInt();
     break;
   }
   case Schema::Fields::NAME: {
     m_name = value.toString();
     break;
   }
   case Schema::Fields::AUTHOR: {
     m_author = value.toString();
     break;
   }
   case Schema::Fields::VERSION: {
     m_version = value.toInt();
     break;
   }
   case Schema::Fields::DATE: {
     m_date = value.toDateTime();
     break;
   }
   case Schema::Fields::DESCRIPTION: {
     m_description = value.toString();
     break;
   }
   case Schema::Fields::URL: {
     m_url = value.toUrl();
     break;
   }
   case Schema::Fields::SIZE: {
     m_size = value.toInt();
     break;
   }
  }
}

void
Document::set_insert_id(int id)
{
  set_id(id);

}

bool
Document::can_update() const
{
  return m_id > 0;
}

QVariantHash
Document::rowid_kwargs() const // To update row
{
  QVariantHash where_kwargs;
  where_kwargs[QLatin1String("id")] = m_id;
  return where_kwargs;
}

QDataStream &
operator<<(QDataStream & out, const Document & obj)
{
  out << obj.id();
  out << obj.name();
  out << obj.author();
  out << obj.version();
  out << obj.date();
  out << obj.description();
  out << obj.url();
  out << obj.size();

  return out;
}

QDataStream &
operator>>(QDataStream & in, Document & obj)
{
  QDateTime _QDateTime;
  QString _QString;
  QUrl _QUrl;
  int _int;
  in >> _int;
  obj.set_id(_int);
  in >> _QString;
  obj.set_name(_QString);
  in >> _QString;
  obj.set_author(_QString);
  in >> _int;
  obj.set_version(_int);
  in >> _QDateTime;
  obj.set_date(_QDateTime);
  in >> _QString;
  obj.set_description(_QString);
  in >> _QUrl;
  obj.set_url(_QUrl);
  in >> _int;
  obj.set_size(_int);

  return in;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const Document & obj)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  // Fixme: quote string !
  debug.nospace() << QStringLiteral("Document(");
  debug << obj.id();
  debug << QStringLiteral(", ");
  debug << obj.name();
  debug << QStringLiteral(", ");
  debug << obj.author();
  debug << QStringLiteral(", ");
  debug << obj.version();
  debug << QStringLiteral(", ");
  debug << obj.date();
  debug << QStringLiteral(", ");
  debug << obj.description();
  debug << QStringLiteral(", ");
  debug << obj.url();
  debug << QStringLiteral(", ");
  debug << obj.size();
  debug << ')';

  return debug;
}
#endif

/**************************************************************************************************/

#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const DocumentPtr & obj)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.noquote() << QStringLiteral("DocumentPtr ->");
  if (obj)
    debug << *obj;
   else
  debug  << QStringLiteral("NULL");

  return debug;
}
#endif

/**************************************************************************************************/

DocumentCache::DocumentCache()
 : m_loaded_instances(),
   m_modified_instances()
{}

DocumentCache::~DocumentCache()
{}

void
DocumentCache::add(DocumentPtr & ptr)
{
  m_loaded_instances.insert(ptr.data(), ptr);
  QObject::connect(ptr.data(), &Document::changed,
                   this, &DocumentCache::on_changed);
}

void
DocumentCache::remove(DocumentPtr & ptr)
{
  Q_UNUSED(ptr);
}

void
DocumentCache::on_changed()
{
  Document * row = qobject_cast<Document *>(QObject::sender());
  qATInfo() << "On changed" << row;
  DocumentPtr row_ptr = m_loaded_instances[row];
  if (row_ptr)
    m_modified_instances.insert(row, row_ptr);
}

/**************************************************************************************************/

DocumentModel::DocumentModel()
  : QAbstractListModel(),
    m_items()
{}

DocumentModel::DocumentModel(const ItemList & items)
  : QAbstractListModel(),
    m_items(items)
{}

DocumentModel::~DocumentModel()
{}

int
DocumentModel::rowCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);
  return m_items.size();
}

QVariant
DocumentModel::data(const QModelIndex & index, int role) const
{
  if (!index.isValid() || index.row() < 0)
    return QVariant();

  if (index.row() >= m_items.count()) {
    qWarning() << "DocumentModel: Index out of bound";
    return QVariant();
  }

  const Item & item = m_items[index.row()];
  switch (role) {
  case ID:
    return item->id();
  case NAME:
    return item->name();
  case AUTHOR:
    return item->author();
  case VERSION:
    return item->version();
  case DATE:
    return item->date();
  case DESCRIPTION:
    return item->description();
  case URL:
    return item->url();
  case SIZE:
    return item->size();
  default:
    break;
  }

  return QVariant();
}

QHash<int, QByteArray>
DocumentModel::roleNames() const
{
  // Fixme: cache ???
  QHash<int, QByteArray> role_names;
  role_names[ID] = QStringLiteral("id").toLatin1();
  role_names[NAME] = QStringLiteral("name").toLatin1();
  role_names[AUTHOR] = QStringLiteral("author").toLatin1();
  role_names[VERSION] = QStringLiteral("version").toLatin1();
  role_names[DATE] = QStringLiteral("date").toLatin1();
  role_names[DESCRIPTION] = QStringLiteral("description").toLatin1();
  role_names[URL] = QStringLiteral("url").toLatin1();
  role_names[SIZE] = QStringLiteral("size").toLatin1();

  return role_names;
}

void
DocumentModel::clear_items()
{
  beginResetModel();
  m_items.clear();
  endResetModel();
}

void
DocumentModel::set_items(const ItemList & items)
{
  beginResetModel();
  m_items = items;
  endResetModel();
}
DocumentDatabaseSchema::DocumentDatabaseSchema(QoDatabase & database)
  : QoDatabaseSchema(database),
    m_document(nullptr),
    m_document_cache()
{
  m_document = &register_table(DocumentSchema::instance());
}

DocumentDatabaseSchema::~DocumentDatabaseSchema()
{}

template<>
void
DocumentDatabaseSchema::register_row<Document>(DocumentPtr & row)
{
  qATInfo() << "Register in cache" << row;
  m_document_cache.add(row);
}

/**************************************************************************************************/
// QC_END_NAMESPACE