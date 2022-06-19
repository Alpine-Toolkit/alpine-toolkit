/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "settings_database.h"
#include "alpine_toolkit.h"

#include "orm/sql_record_wrapper.h"

// #include <type_traits>

#include <QSqlError>
#include <QtDebug>

/**************************************************************************************************/

static const QString NAME = "name";
static const QString PARENT = "parent";
static const QString VALUE = "value";

enum class DirectoryField: int {
  Id,
  Name,
  Parent
};

int
Int(const DirectoryField & index) {
  return static_cast<int>(index);
}

enum class KeyField: int {
  Name,
  Parent,
  Value
};

int
Int(const KeyField & index) {
  return static_cast<int>(index);
}

/* C++14
template <typename E>
constexpr auto to_underlying(E e) noexcept
{
    return static_cast<std::underlying_type_t<E>>(e);
}
*/

SettingsDatabase::SettingsDatabase(QoDatabase & database)
  : QoDatabaseSchema(database),
    m_directory_table(nullptr),
    m_key_value_table(nullptr)
{}

SettingsDatabase::~SettingsDatabase()
{}

void
SettingsDatabase::register_tables()
{
  QoSchemaPrimaryKey rowid(QLatin1String("id"), QLatin1String("int"), QLatin1String("INTEGER"));
  rowid.set_nullable(false);

  QoSchemaField name_field(NAME, QLatin1String("QString"), QLatin1String("TEXT"));
  name_field.set_nullable(false);

  // Fixme: copy ???
  QoSchemaPrimaryKey name_field_pk(NAME, QLatin1String("QString"), QLatin1String("TEXT"));
  name_field_pk.set_nullable(false);

  QoSchema directory_schema(QLatin1String("directory"));
  directory_schema << rowid;
  directory_schema << name_field;
  directory_schema << QoSchemaField(PARENT, QLatin1String("int"), QLatin1String("INTEGER")); // Foreign key to self.rowid
  m_directory_table = &register_table(directory_schema);

  // Fixme: primary key (name, parent) but parent is foreign key or null
  //   define root ?
  QoSchema key_value_schema(QLatin1String("key"));
  key_value_schema << name_field_pk;
  // key_value_schema << QoSchemaForeignKey(PARENT, QLatin1String("directory.id"), QLatin1String("int"), QLatin1String("INTEGER"));
  key_value_schema << QoSchemaPrimaryKey(PARENT, QLatin1String("int"), QLatin1String("INTEGER")); // can be null !
  key_value_schema << QoSchemaField(VALUE, QLatin1String("QVariant"), QLatin1String("BLOB"));
  m_key_value_table = &register_table(key_value_schema);
}

QString
SettingsDatabase::directory_part(const QString & key) const
{
  int index = key.lastIndexOf('/');
  return index != -1 ? key.left(index) : QString();
}

QString
SettingsDatabase::name_part(const QString & key) const
{
  int index = key.lastIndexOf('/');
  return index != -1 ? key.mid(index + 1) : key;
}

int
SettingsDatabase::number_of_directories() const
{
  return m_directory_table->count();
}

int
SettingsDatabase::number_of_keys() const
{
  return m_key_value_table->count();
}

QVariantHash
SettingsDatabase::directory_kwargs(const QString & directory, int parent)
{
  QVariantHash kwargs;
  kwargs[NAME] = directory;
  kwargs[PARENT] = parent;
  return kwargs;
}

int
SettingsDatabase::add_directory(const QString & directory, int parent)
{
  QSqlQuery query = m_directory_table->insert(directory_kwargs(directory, parent));
  int rowid = query.lastInsertId().toInt();
  // qATInfo() << "added directory" << directory << parent << rowid;
  return rowid;
}

int
SettingsDatabase::directory_rowid(const QString & directory, int parent)
{
  return m_directory_table->rowid(directory_kwargs(directory, parent));
}

int
SettingsDatabase::lookup_path(const QString & _path, bool create)
{
  QString path = _path;

  // Remove first /
  if (path.startsWith('/'))
    path = path.mid(1);

  // Remove trailing /
  if (path.endsWith('/'))
    path = path.left(path.size() - 1);

  if (path.isEmpty())
    return 0;
  else if (m_path_cache.contains(path))
    return m_path_cache[path];

  QStringList directories = path.split('/');

  int parent = 0; // start at root
  for (const auto & directory : directories) {
    int rowid = directory_rowid(directory, parent);
    if (rowid > 0) // Fixme: > 0 ???
      parent = rowid;
    else {
      if (create)
        parent = add_directory(directory, parent); // not const
      else
        return -1;
    }
  }
  // Note: rowid = parent

  m_path_cache[path] = parent;

  return parent;
}

int
SettingsDatabase::parent_of(const QString & key, bool create)
{
  QString directory = directory_part(key);
  // qATInfo() << "parent_of" << key << directory;
  return lookup_path(directory, create);
}

QVariantHash
SettingsDatabase::key_kwargs(const QString & key)
{
  QVariantHash kwargs;
  kwargs[NAME] = name_part(key);
  kwargs[PARENT] = parent_of(key);
  return kwargs;
}

bool
SettingsDatabase::contains(const QString & key)
{
  if (m_key_cache.contains(key))
    return true;
  else
    return m_key_value_table->count(key_kwargs(key)) > 0;
}

QVariant
SettingsDatabase::value(const QString & key)
{
  if (m_key_cache.contains(key))
    return m_key_cache[key];
  else {
    QSqlRecord record = m_key_value_table->select_one(VALUE, key_kwargs(key));
    if (record.isEmpty())
      return QVariant();
    else {
      QVariant value = record.value(0);
      m_key_cache[key] = value;
      return value;
    }
  }
}

void
SettingsDatabase::set_value(const QString & key, const QVariant & value)
{
  QVariantHash kwargs = key_kwargs(key);
  // Fixme: can use contains
  if (m_key_value_table->count(kwargs)) {
    QVariantHash kwargs_update;
    // qATInfo() << "value is of type" << value.typeName();
    kwargs_update[VALUE] = value;
    m_key_value_table->update(kwargs_update, kwargs);
    // qATInfo() << "updated key" << rowid << key << value;
  } else {
    kwargs[VALUE] = value;
    QSqlQuery query = m_key_value_table->insert(kwargs);
    // qATInfo() << "added key" << key << value;
  }

  m_key_cache[key] = value;
}

void
SettingsDatabase::remove(const QString & key)
{
  m_key_value_table->delete_row(key_kwargs(key));
  if (m_key_cache.contains(key))
    m_key_cache.remove(key);
}

void
SettingsDatabase::delete_all()
{
  m_key_value_table->delete_row();
  m_directory_table->delete_row();

  m_rowid_path_cache.clear();
  m_path_cache.clear();
  m_key_cache.clear();
}

QStringList
SettingsDatabase::keys(const QString & path)
{
  // Don't use cache

  int parent =(path.isEmpty() or path == QLatin1String("/")) ?
    0 : parent_of(path + '/', false); // Fixme: / is required to get directory_part
  if (parent >= 0) {
    QVariantHash kwargs;
    kwargs[PARENT] = parent;
    QSqlQuery query = m_key_value_table->select(NAME, kwargs);
    QStringList keys;
    while (query.next())
      keys << query.value(0).toString();
    return keys;
  } else // path son't exists
    return QStringList();
}

QString
SettingsDatabase::parent_to_path(int path_parent)
{
  if (path_parent > 0) {
    QoSqlRecordWrapper record = m_directory_table->select_by_id(path_parent);
    int parent = record.toInt(Int(DirectoryField::Parent));
    QString path;
    if (parent > 0)
      path = parent_to_path(parent) + '/';
    path += record.toString(Int(DirectoryField::Name));
    m_rowid_path_cache[path_parent] =  path;
    return path;
  } else
    return QString();
}

void
SettingsDatabase::load()
{
  QoSqlQueryWrapper query = m_key_value_table->select_where();
  while (query.next()) {
    QString name = query.toString(Int(KeyField::Name));
    int parent = query.toInt(Int(KeyField::Parent));
    QVariant value = query.value(Int(KeyField::Value));
    QString path = m_rowid_path_cache.contains(parent) ?
      m_rowid_path_cache[parent] : parent_to_path(parent);
    QString key = path.isEmpty() ? name : path + '/' + name;
    m_key_cache[key] = value;
  }
}

void
SettingsDatabase::clear_cache()
{
  m_rowid_path_cache.clear();
  m_path_cache.clear();
  m_key_cache.clear();
}

void
SettingsDatabase::load_directory()
{
  // id -> directory map
  QHash<int, SettingsDatabaseDirectory*> directory_map;
  directory_map[0] = &m_root;

  {
    // Fixme: table -> schema -> int cast
    QoSqlField parent_field = m_directory_table->schema().sql_field(Int(DirectoryField::Parent));
    QoSqlQuery sql_query = m_directory_table->sql_query().order_by(parent_field).all();
    QoSqlQueryWrapper query = sql_query.exec();
    while (query.next()) {
      int id = query.toInt(Int(DirectoryField::Id));
      QString name = query.toString(Int(DirectoryField::Name));
      int parent = query.toInt(Int(DirectoryField::Parent));
      SettingsDatabaseDirectory * parent_directory = directory_map[parent];
      SettingsDatabaseDirectory & directory = parent_directory->add_directory(name);
      directory_map[id] = &directory;
    }
  }

  {
    QoSqlQueryWrapper query = m_key_value_table->select_where();
    while (query.next()) {
      QString name = query.toString(Int(KeyField::Name));
      int parent = query.toInt(Int(KeyField::Parent));
      QVariant value = query.value(Int(KeyField::Value));
      SettingsDatabaseDirectory * directory = directory_map[parent];
      directory->add_key(name, value);
    }
  }
}

void
SettingsDatabase::save_directory(const SettingsDatabaseDirectory & directory)
{
  for (const auto & key : directory.keys())
    set_value(key.path(), key.value());
  for (const auto & subdirectory : directory.directories())
    save_directory(subdirectory);
}

void
SettingsDatabase::load_json_document(const QJsonDocument & json_document)
{
  m_root.from_json(json_document.object());
  save_directory(m_root);
}

QJsonDocument
SettingsDatabase::to_json_document() // const
{
  // Fixme:: const: use local tree ?
  //   if already loaded ???
  load_directory();

  QJsonDocument document;
  document.setObject(m_root.to_json());

  return document;
}

/**************************************************************************************************/

SqliteSettingsDatabase::SqliteSettingsDatabase(const QString & sqlite_path)
  : QoSqliteDatabase(sqlite_path),
    m_settings_database(*this)
    // SettingsDatabase(*this)
{
  m_settings_database.register_tables();
}

SqliteSettingsDatabase::~SqliteSettingsDatabase()
{}
