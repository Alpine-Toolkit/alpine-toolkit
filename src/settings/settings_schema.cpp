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

#include "settings_schema.h"
#include "alpine_toolkit.h"

#include "orm/database_query.h"
#include "orm/type_conversion.h"

#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE


DirectorySchema::DirectorySchema()
: QoSchema(QLatin1String("Directory"), QLatin1String("directory"))
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
    QoSchemaForeignKey field(
      QLatin1String("parent"),
      QLatin1String("directory.id"),
      QLatin1String("int"),
      QLatin1String("integer"),
      QLatin1String("parent"),
      QLatin1String("parent"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
}

DirectorySchema::~DirectorySchema()
{}

/**************************************************************************************************/

Directory::Directory()
  : QObject(),
    QoRow<DirectorySchema>(),
    m_id(),
    m_name(),
    m_parent()
{
}

Directory::Directory(const Directory & other)
  : QObject(),
    QoRow<DirectorySchema>(other),
    m_id(other.m_id),
    m_name(other.m_name),
    m_parent(other.m_parent)
{
}

Directory::Directory(const QJsonObject & json_object)
 : Directory()
{
  m_id = json_object[QLatin1String("id")].toInt();
  m_name = json_object[QLatin1String("name")].toString();
  m_parent = json_object[QLatin1String("parent")].toInt();
}

Directory::Directory(const QVariantHash & variant_hash)
 : Directory()
{
  m_id = variant_hash[QLatin1String("id")].toInt();
  m_name = variant_hash[QLatin1String("name")].toString();
  m_parent = variant_hash[QLatin1String("parent")].toInt();
}

Directory::Directory(const QVariantList & variants)
 : Directory()
{
  m_id = variants[0].toInt();
  m_name = variants[1].toString();
  m_parent = variants[2].toInt();
}

Directory::Directory(const QSqlRecord & record)
 : QoRow<DirectorySchema>(record)
{
  m_id = record.value(0).toInt();
  m_name = record.value(1).toString();
  m_parent = record.value(2).toInt();
}

Directory::Directory(const QSqlQuery & query, int offset)
 : QoRow<DirectorySchema>(query)
{
  m_id = query.value(offset++).toInt();
  m_name = query.value(offset++).toString();
  m_parent = query.value(offset).toInt();
}

Directory::~Directory()
{
// qATInfo() << "--- Delete" << "Directory" << *this;
}

// bit array ?
Directory &
Directory::operator=(const Directory & other)
{
  if (this != &other) {
    QoRow<DirectorySchema>::operator=(other);
    m_id = other.m_id;
    m_name = other.m_name;
    m_parent = other.m_parent;
  }

  return *this;
}

// bit array ?
bool
Directory::operator==(const Directory & other) const
{
  if (not QoRow<DirectorySchema>::operator==(other))
    return false;
  if (m_id != other.m_id)
    return false;
  if (m_name != other.m_name)
    return false;
  if (m_parent != other.m_parent)
    return false;

  return true;
}

void
Directory::set_id(int value)
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
Directory::set_name(const QString & value)
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
Directory::set_parent(int value)
{
  if (m_parent != value) {
    m_parent = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::PARENT);

    emit parentChanged();
    if (not is_changed)
      emit changed();
  }
}

QJsonObject
Directory::to_json(bool only_changed) const
{
  QJsonObject json_object;

 if (only_changed) {
    if (is_id_modified())
      json_object.insert(QLatin1String("id"), QJsonValue(m_id));
    if (is_name_modified())
      json_object.insert(QLatin1String("name"), QJsonValue(m_name));
    if (is_parent_modified())
      json_object.insert(QLatin1String("parent"), QJsonValue(m_parent));
  } else {
    json_object.insert(QLatin1String("id"), QJsonValue(m_id));
    json_object.insert(QLatin1String("name"), QJsonValue(m_name));
    json_object.insert(QLatin1String("parent"), QJsonValue(m_parent));
  }

  return json_object;
}

QVariantHash
Directory::to_variant_hash(bool only_changed) const
{
  QVariantHash variant_hash;

  if (only_changed) {
    if (is_id_modified())
      variant_hash[QLatin1String("id")] = m_id;
    if (is_name_modified())
      variant_hash[QLatin1String("name")] = m_name;
    if (is_parent_modified())
      variant_hash[QLatin1String("parent")] = m_parent;
  } else {
    variant_hash[QLatin1String("id")] = m_id;
    variant_hash[QLatin1String("name")] = m_name;
    variant_hash[QLatin1String("parent")] = m_parent;
  }

  return variant_hash;
}

QVariantList
Directory::to_variant_list() const
{
  QVariantList variants;

  variants << m_id;
  variants << m_name;
  variants << m_parent;

  return variants;
}

QVariantHash
Directory::to_variant_hash_sql(bool only_changed, bool duplicate) const
{
  QVariantHash variant_hash;

  if (only_changed) {
    if (is_id_modified())
      variant_hash[QLatin1String("id")] = m_id;
    if (is_name_modified())
      variant_hash[QLatin1String("name")] = m_name;
    if (is_parent_modified())
      variant_hash[QLatin1String("parent")] = m_parent;
  } else {
    if (duplicate)
      variant_hash[QLatin1String("id")] = m_id;
    variant_hash[QLatin1String("name")] = m_name;
    variant_hash[QLatin1String("parent")] = m_parent;
  }

  return variant_hash;
}

QVariantList
Directory::to_variant_list_sql(bool duplicate) const
{
  QVariantList variants;

  if (duplicate)
    variants << m_id;
  variants << m_name;
  variants << m_parent;

  return variants;
}

QVariant
Directory::field(int position) const
{
  switch(position) {
   case Schema::Fields::ID:
     return m_id;
   case Schema::Fields::NAME:
     return m_name;
   case Schema::Fields::PARENT:
     return m_parent;
   default:
     return QVariant(); // error
  }
}

void
Directory::set_field(int position, const QVariant & value)
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
   case Schema::Fields::PARENT: {
     m_parent = value.toInt();
     break;
   }
  }
}

void
Directory::set_insert_id(int id)
{
  set_id(id);

  for (const auto & item_weak_ref : m_keys)
    item_weak_ref.toStrongRef().data()->set_directory_id(id); // Fixme: check ref
}

bool
Directory::can_save() const
{
  if (m_parent == 0)
    return false;

  return true;
}

void
Directory::load_relations()
{
  qATInfo() << "Load relations of" << *this;
  {
    // Load one-to-many relation keys
    Key::PtrList rows = database_schema()->query_by_foreign_key<Key>(
      QLatin1String("directory_id"),
      m_id); // true
    m_keys = rows;
  }
}

void
Directory::save_relations()
{
  qATInfo() << "Save relations of" << *this;
  for (const auto & item_weak_ref : m_keys) {
    Key * item_ptr = item_weak_ref.toStrongRef().data();
    if (not item_ptr->exists_on_database())
      database_schema()->add(*item_ptr);
  }
}

bool
Directory::can_update() const
{
  return m_id > 0;
}

QVariantHash
Directory::rowid_kwargs() const // To update row
{
  QVariantHash where_kwargs;
  where_kwargs[QLatin1String("id")] = m_id;
  return where_kwargs;
}

QDataStream &
operator<<(QDataStream & out, const Directory & obj)
{
  out << obj.id();
  out << obj.name();
  out << obj.parent();

  return out;
}

QDataStream &
operator>>(QDataStream & in, Directory & obj)
{
  QString _QString;
  int _int;
  in >> _int;
  obj.set_id(_int);
  in >> _QString;
  obj.set_name(_QString);
  in >> _int;
  obj.set_parent(_int);

  return in;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const Directory & obj)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  // Fixme: quote string !
  debug.nospace() << QStringLiteral("Directory(");
  debug << obj.id();
  debug << QStringLiteral(", ");
  debug << obj.name();
  debug << QStringLiteral(", ");
  debug << obj.parent();
  debug << ')';

  return debug;
}
#endif

/**************************************************************************************************/

#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const DirectoryPtr & obj)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.noquote() << QStringLiteral("DirectoryPtr ->");
  if (obj)
    debug << *obj;
   else
  debug  << QStringLiteral("NULL");

  return debug;
}
#endif

/**************************************************************************************************/

DirectoryCache::DirectoryCache()
 : m_loaded_instances(),
   m_modified_instances()
{}

DirectoryCache::~DirectoryCache()
{}

void
DirectoryCache::add(DirectoryPtr & ptr)
{
  m_loaded_instances.insert(ptr.data(), ptr);
  QObject::connect(ptr.data(), &Directory::changed,
                   this, &DirectoryCache::on_changed);
}

void
DirectoryCache::remove(DirectoryPtr & ptr)
{
  Q_UNUSED(ptr);
}

void
DirectoryCache::on_changed()
{
  Directory * row = qobject_cast<Directory *>(QObject::sender());
  qATInfo() << "On changed" << row;
  DirectoryPtr row_ptr = m_loaded_instances[row];
  if (row_ptr)
    m_modified_instances.insert(row, row_ptr);
}

/**************************************************************************************************/

DirectoryModel::DirectoryModel()
  : QAbstractListModel(),
    m_items()
{}

DirectoryModel::DirectoryModel(const ItemList & items)
  : QAbstractListModel(),
    m_items(items)
{}

DirectoryModel::~DirectoryModel()
{}

int
DirectoryModel::rowCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);
  return m_items.size();
}

QVariant
DirectoryModel::data(const QModelIndex & index, int role) const
{
  if (!index.isValid() || index.row() < 0)
    return QVariant();

  if (index.row() >= m_items.count()) {
    qWarning() << "DirectoryModel: Index out of bound";
    return QVariant();
  }

  const Item & item = m_items[index.row()];
  switch (role) {
  case ID:
    return item->id();
  case NAME:
    return item->name();
  case PARENT:
    return item->parent();
  default:
    break;
  }

  return QVariant();
}

QHash<int, QByteArray>
DirectoryModel::roleNames() const
{
  // Fixme: cache ???
  QHash<int, QByteArray> role_names;
  role_names[ID] = QStringLiteral("id").toLatin1();
  role_names[NAME] = QStringLiteral("name").toLatin1();
  role_names[PARENT] = QStringLiteral("parent").toLatin1();

  return role_names;
}

void
DirectoryModel::clear_items()
{
  beginResetModel();
  m_items.clear();
  endResetModel();
}

void
DirectoryModel::set_items(const ItemList & items)
{
  beginResetModel();
  m_items = items;
  endResetModel();
}

KeySchema::KeySchema()
: QoSchema(QLatin1String("Key"), QLatin1String("key"))
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
    QoSchemaForeignKey field(
      QLatin1String("directory_id"),
      QLatin1String("directory.id"),
      QLatin1String("int"),
      QLatin1String("integer"),
      QLatin1String("directory_id"),
      QLatin1String("directory_id"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("value"),
      QLatin1String("QVariant"),
      QLatin1String("blob"),
      QLatin1String("value"),
      QLatin1String("value"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
}

KeySchema::~KeySchema()
{}

/**************************************************************************************************/

Key::Key()
  : QObject(),
    QoRow<KeySchema>(),
    m_id(),
    m_name(),
    m_directory_id(),
    m_value()
{
}

Key::Key(const Key & other)
  : QObject(),
    QoRow<KeySchema>(other),
    m_id(other.m_id),
    m_name(other.m_name),
    m_directory_id(other.m_directory_id),
    m_value(other.m_value)
{
}

Key::Key(const QJsonObject & json_object)
 : Key()
{
  m_id = json_object[QLatin1String("id")].toInt();
  m_name = json_object[QLatin1String("name")].toString();
  m_directory_id = json_object[QLatin1String("directory_id")].toInt();
  m_value = json_object[QLatin1String("value")].toVariant();
}

Key::Key(const QVariantHash & variant_hash)
 : Key()
{
  m_id = variant_hash[QLatin1String("id")].toInt();
  m_name = variant_hash[QLatin1String("name")].toString();
  m_directory_id = variant_hash[QLatin1String("directory_id")].toInt();
  m_value = variant_hash[QLatin1String("value")];
}

Key::Key(const QVariantList & variants)
 : Key()
{
  m_id = variants[0].toInt();
  m_name = variants[1].toString();
  m_directory_id = variants[2].toInt();
  m_value = variants[3];
}

Key::Key(const QSqlRecord & record)
 : QoRow<KeySchema>(record)
{
  m_id = record.value(0).toInt();
  m_name = record.value(1).toString();
  m_directory_id = record.value(2).toInt();
  m_value = record.value(3);
}

Key::Key(const QSqlQuery & query, int offset)
 : QoRow<KeySchema>(query)
{
  m_id = query.value(offset++).toInt();
  m_name = query.value(offset++).toString();
  m_directory_id = query.value(offset++).toInt();
  m_value = query.value(offset);
}

Key::~Key()
{
// qATInfo() << "--- Delete" << "Key" << *this;
}

// bit array ?
Key &
Key::operator=(const Key & other)
{
  if (this != &other) {
    QoRow<KeySchema>::operator=(other);
    m_id = other.m_id;
    m_name = other.m_name;
    m_directory_id = other.m_directory_id;
    m_value = other.m_value;
  }

  return *this;
}

// bit array ?
bool
Key::operator==(const Key & other) const
{
  if (not QoRow<KeySchema>::operator==(other))
    return false;
  if (m_id != other.m_id)
    return false;
  if (m_name != other.m_name)
    return false;
  if (m_directory_id != other.m_directory_id)
    return false;
  if (m_value != other.m_value)
    return false;

  return true;
}

void
Key::set_id(int value)
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
Key::set_name(const QString & value)
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
Key::set_directory_id(int value)
{
  if (m_directory_id != value) {
    m_directory_id = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::DIRECTORY_ID);

    emit directory_idChanged();
    if (not is_changed)
      emit changed();
  }
}

void
Key::set_value(const QVariant & value)
{
  if (m_value != value) {
    m_value = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::VALUE);

    emit valueChanged();
    if (not is_changed)
      emit changed();
  }
}

QJsonObject
Key::to_json(bool only_changed) const
{
  QJsonObject json_object;

 if (only_changed) {
    if (is_id_modified())
      json_object.insert(QLatin1String("id"), QJsonValue(m_id));
    if (is_name_modified())
      json_object.insert(QLatin1String("name"), QJsonValue(m_name));
    if (is_directory_id_modified())
      json_object.insert(QLatin1String("directory_id"), QJsonValue(m_directory_id));
    if (is_value_modified())
      json_object.insert(QLatin1String("value"), m_value.toJsonValue()
);
  } else {
    json_object.insert(QLatin1String("id"), QJsonValue(m_id));
    json_object.insert(QLatin1String("name"), QJsonValue(m_name));
    json_object.insert(QLatin1String("directory_id"), QJsonValue(m_directory_id));
    json_object.insert(QLatin1String("value"), m_value.toJsonValue()
);
  }

  return json_object;
}

QVariantHash
Key::to_variant_hash(bool only_changed) const
{
  QVariantHash variant_hash;

  if (only_changed) {
    if (is_id_modified())
      variant_hash[QLatin1String("id")] = m_id;
    if (is_name_modified())
      variant_hash[QLatin1String("name")] = m_name;
    if (is_directory_id_modified())
      variant_hash[QLatin1String("directory_id")] = m_directory_id;
    if (is_value_modified())
      variant_hash[QLatin1String("value")] = m_value;
  } else {
    variant_hash[QLatin1String("id")] = m_id;
    variant_hash[QLatin1String("name")] = m_name;
    variant_hash[QLatin1String("directory_id")] = m_directory_id;
    variant_hash[QLatin1String("value")] = m_value;
  }

  return variant_hash;
}

QVariantList
Key::to_variant_list() const
{
  QVariantList variants;

  variants << m_id;
  variants << m_name;
  variants << m_directory_id;
  variants << m_value;

  return variants;
}

QVariantHash
Key::to_variant_hash_sql(bool only_changed, bool duplicate) const
{
  QVariantHash variant_hash;

  if (only_changed) {
    if (is_id_modified())
      variant_hash[QLatin1String("id")] = m_id;
    if (is_name_modified())
      variant_hash[QLatin1String("name")] = m_name;
    if (is_directory_id_modified())
      variant_hash[QLatin1String("directory_id")] = m_directory_id;
    if (is_value_modified())
      variant_hash[QLatin1String("value")] = m_value;
  } else {
    if (duplicate)
      variant_hash[QLatin1String("id")] = m_id;
    variant_hash[QLatin1String("name")] = m_name;
    variant_hash[QLatin1String("directory_id")] = m_directory_id;
    variant_hash[QLatin1String("value")] = m_value;
  }

  return variant_hash;
}

QVariantList
Key::to_variant_list_sql(bool duplicate) const
{
  QVariantList variants;

  if (duplicate)
    variants << m_id;
  variants << m_name;
  variants << m_directory_id;
  variants << m_value;

  return variants;
}

QVariant
Key::field(int position) const
{
  switch(position) {
   case Schema::Fields::ID:
     return m_id;
   case Schema::Fields::NAME:
     return m_name;
   case Schema::Fields::DIRECTORY_ID:
     return m_directory_id;
   case Schema::Fields::VALUE:
     return m_value;
   default:
     return QVariant(); // error
  }
}

void
Key::set_field(int position, const QVariant & value)
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
   case Schema::Fields::DIRECTORY_ID: {
     m_directory_id = value.toInt();
     break;
   }
   case Schema::Fields::VALUE: {
     m_value = value;
     break;
   }
  }
}

void
Key::set_insert_id(int id)
{
  set_id(id);

}

bool
Key::can_save() const
{
  if (m_directory_id == 0)
    return false;

  return true;
}

void
Key::load_relations()
{
  qATInfo() << "Load relations of" << *this;
  directory();
}

void
Key::save_relations()
{
  qATInfo() << "Save relations of" << *this;
}

DirectoryPtr
Key::directory()
{
  if (m_directory.isNull())
    // Fixme: query_by_id must be defined in QoDatabaseSchema but we cannot call register_row
    m_directory = database_schema()->query_by_id<Directory>(m_directory_id);
  return m_directory;
}

bool
Key::can_update() const
{
  return m_id > 0;
}

QVariantHash
Key::rowid_kwargs() const // To update row
{
  QVariantHash where_kwargs;
  where_kwargs[QLatin1String("id")] = m_id;
  return where_kwargs;
}

QDataStream &
operator<<(QDataStream & out, const Key & obj)
{
  out << obj.id();
  out << obj.name();
  out << obj.directory_id();
  out << obj.value();

  return out;
}

QDataStream &
operator>>(QDataStream & in, Key & obj)
{
  QString _QString;
  QVariant _QVariant;
  int _int;
  in >> _int;
  obj.set_id(_int);
  in >> _QString;
  obj.set_name(_QString);
  in >> _int;
  obj.set_directory_id(_int);
  in >> _QVariant;
  obj.set_value(_QVariant);

  return in;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const Key & obj)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  // Fixme: quote string !
  debug.nospace() << QStringLiteral("Key(");
  debug << obj.id();
  debug << QStringLiteral(", ");
  debug << obj.name();
  debug << QStringLiteral(", ");
  debug << obj.directory_id();
  debug << QStringLiteral(", ");
  debug << obj.value();
  debug << ')';

  return debug;
}
#endif

/**************************************************************************************************/

void
KeyPtr::set_directory(DirectoryPtr & value)
{
  if (m_ptr->m_directory)
    m_ptr->m_directory->keys().remove(*this);
  m_ptr->m_directory = value;
  m_ptr->set_directory_id(value->id());
  value->keys().append(*this);
}

#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const KeyPtr & obj)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.noquote() << QStringLiteral("KeyPtr ->");
  if (obj)
    debug << *obj;
   else
  debug  << QStringLiteral("NULL");

  return debug;
}
#endif

/**************************************************************************************************/

KeyCache::KeyCache()
 : m_loaded_instances(),
   m_modified_instances()
{}

KeyCache::~KeyCache()
{}

void
KeyCache::add(KeyPtr & ptr)
{
  m_loaded_instances.insert(ptr.data(), ptr);
  QObject::connect(ptr.data(), &Key::changed,
                   this, &KeyCache::on_changed);
}

void
KeyCache::remove(KeyPtr & ptr)
{
  Q_UNUSED(ptr);
}

void
KeyCache::on_changed()
{
  Key * row = qobject_cast<Key *>(QObject::sender());
  qATInfo() << "On changed" << row;
  KeyPtr row_ptr = m_loaded_instances[row];
  if (row_ptr)
    m_modified_instances.insert(row, row_ptr);
}

/**************************************************************************************************/

KeyModel::KeyModel()
  : QAbstractListModel(),
    m_items()
{}

KeyModel::KeyModel(const ItemList & items)
  : QAbstractListModel(),
    m_items(items)
{}

KeyModel::~KeyModel()
{}

int
KeyModel::rowCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);
  return m_items.size();
}

QVariant
KeyModel::data(const QModelIndex & index, int role) const
{
  if (!index.isValid() || index.row() < 0)
    return QVariant();

  if (index.row() >= m_items.count()) {
    qWarning() << "KeyModel: Index out of bound";
    return QVariant();
  }

  const Item & item = m_items[index.row()];
  switch (role) {
  case ID:
    return item->id();
  case NAME:
    return item->name();
  case DIRECTORY_ID:
    return item->directory_id();
  case VALUE:
    return item->value();
  default:
    break;
  }

  return QVariant();
}

QHash<int, QByteArray>
KeyModel::roleNames() const
{
  // Fixme: cache ???
  QHash<int, QByteArray> role_names;
  role_names[ID] = QStringLiteral("id").toLatin1();
  role_names[NAME] = QStringLiteral("name").toLatin1();
  role_names[DIRECTORY_ID] = QStringLiteral("directory_id").toLatin1();
  role_names[VALUE] = QStringLiteral("value").toLatin1();

  return role_names;
}

void
KeyModel::clear_items()
{
  beginResetModel();
  m_items.clear();
  endResetModel();
}

void
KeyModel::set_items(const ItemList & items)
{
  beginResetModel();
  m_items = items;
  endResetModel();
}
BlogApplicationSchema::BlogApplicationSchema(QoDatabase & database)
  : QoDatabaseSchema(database),
    m_directory(nullptr),
    m_key(nullptr),
    m_directory_cache(),
    m_key_cache()
{
  m_directory = &register_table(DirectorySchema::instance());
  m_key = &register_table(KeySchema::instance());
}

BlogApplicationSchema::~BlogApplicationSchema()
{}

template<>
void
BlogApplicationSchema::register_row<Directory>(DirectoryPtr & row)
{
  qATInfo() << "Register in cache" << row;
  m_directory_cache.add(row);
}
template<>
void
BlogApplicationSchema::register_row<Key>(KeyPtr & row)
{
  qATInfo() << "Register in cache" << row;
  m_key_cache.add(row);
}

/**************************************************************************************************/
// QC_END_NAMESPACE