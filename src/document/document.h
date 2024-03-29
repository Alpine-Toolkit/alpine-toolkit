// -*- mode: c++ -*-
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

#ifndef __DOCUMENT_H__
#define __DOCUMENT_H__

/**************************************************************************************************/

#define QT_SHAREDPOINTER_TRACK_POINTERS // For dubug purpose

#include "alpine_toolkit.h"
#include "orm/database_row.h"
#include "orm/database_row_list.h"
#include "orm/database_schema.h"
#include "orm/schema.h"

#include <QAbstractListModel>
#include <QDataStream>
#include <QDateTime>
#include <QJsonObject>
#include <QMap>
#include <QSharedPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QtDebug>
#include <QUrl>
#include <QVariant>
#include <QVariantList>

/**************************************************************************************************/

class Document;
class DocumentPtr;

/**************************************************************************************************/

class DocumentSchema : public QoSchema
{
public:
  enum Fields {
    ID,
    NAME,
    AUTHOR,
    VERSION,
    DATE,
    DESCRIPTION,
    URL,
    SIZE
  };
  static const int NUMBER_OF_FIELDS = 8;

public:
  static DocumentSchema & instance()
  {
    static DocumentSchema m_instance;
    return m_instance;
  }

  // delete copy and move constructors and assign operators
  DocumentSchema(const DocumentSchema &) = delete;
  DocumentSchema(DocumentSchema &&) = delete;
  DocumentSchema & operator=(const DocumentSchema &) = delete;
  DocumentSchema & operator=(DocumentSchema &&) = delete;

protected:
  DocumentSchema();
  ~DocumentSchema();
};

/**************************************************************************************************/

class Document : public QObject, public QoRow<DocumentSchema>
{
  Q_OBJECT
  Q_PROPERTY(int id READ id WRITE set_id NOTIFY idChanged)
  Q_PROPERTY(QString name READ name WRITE set_name NOTIFY nameChanged)
  Q_PROPERTY(QString author READ author WRITE set_author NOTIFY authorChanged)
  Q_PROPERTY(int version READ version WRITE set_version NOTIFY versionChanged)
  Q_PROPERTY(QDateTime date READ date WRITE set_date NOTIFY dateChanged)
  Q_PROPERTY(QString description READ description WRITE set_description NOTIFY descriptionChanged)
  Q_PROPERTY(QUrl url READ url WRITE set_url NOTIFY urlChanged)
  Q_PROPERTY(int size READ size WRITE set_size NOTIFY sizeChanged)

public:
  typedef DocumentPtr Ptr;
  typedef QList<Ptr> PtrList;
  friend class DocumentPtr;

public:
  Document();
  Document(const Document & other);
  Document(const QJsonObject & json_object); // JSON deserializer
  Document(const QVariantHash & variant_hash);
  Document(const QVariantList & variants);
  Document(const QSqlRecord & record); // SQL deserializer
  Document(const QSqlQuery & query, int offset = 0); // SQL deserializer
  ~Document();

  Document & operator=(const Document & other);

  bool operator==(const Document & other) const;

  // Getter/Setter

  int id() const { return m_id; }
  void set_id(int value);

  const QString & name() const { return m_name; }
  void set_name(const QString & value);

  const QString & author() const { return m_author; }
  void set_author(const QString & value);

  int version() const { return m_version; }
  void set_version(int value);

  const QDateTime & date() const { return m_date; }
  void set_date(const QDateTime & value);

  const QString & description() const { return m_description; }
  void set_description(const QString & value);

  const QUrl & url() const { return m_url; }
  void set_url(const QUrl & value);

  int size() const { return m_size; }
  void set_size(int value);

  void set_insert_id(int id);
  bool exists_on_database() const { return m_id > 0; } // require NOT NULL

  // JSON Serializer
  QJsonObject to_json(bool only_changed = false) const;

  // Generic Variant Serializer
  QVariantHash to_variant_hash(bool only_changed = false) const;
  QVariantList to_variant_list() const;

  // SQL Serializer
  QVariantHash to_variant_hash_sql(bool only_changed = false, bool duplicate = false) const;
  QVariantList to_variant_list_sql(bool duplicate = false) const;

  // Query for update
  bool is_id_modified() const { return bit_status(Schema::Fields::ID); }
  bool is_name_modified() const { return bit_status(Schema::Fields::NAME); }
  bool is_author_modified() const { return bit_status(Schema::Fields::AUTHOR); }
  bool is_version_modified() const { return bit_status(Schema::Fields::VERSION); }
  bool is_date_modified() const { return bit_status(Schema::Fields::DATE); }
  bool is_description_modified() const { return bit_status(Schema::Fields::DESCRIPTION); }
  bool is_url_modified() const { return bit_status(Schema::Fields::URL); }
  bool is_size_modified() const { return bit_status(Schema::Fields::SIZE); }

  // Field accessor by position
  QVariant field(int position) const;
  void set_field(int position, const QVariant & value);

  bool can_update() const; // To update row
  QVariantHash rowid_kwargs() const;

signals:
  void changed();
  void idChanged();
  void nameChanged();
  void authorChanged();
  void versionChanged();
  void dateChanged();
  void descriptionChanged();
  void urlChanged();
  void sizeChanged();

private:
  int m_id;
  QString m_name;
  QString m_author;
  int m_version;
  QDateTime m_date;
  QString m_description;
  QUrl m_url;
  int m_size;

};

QDataStream & operator<<(QDataStream & out, const Document & obj);
QDataStream & operator>>(QDataStream & in, Document & obj);
// qRegisterMetaTypeStreamOperators<Document>("Document");

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const Document & obj);
#endif

/**************************************************************************************************/

class DocumentPtr
{
public:
  typedef Document Class;

public:
  DocumentPtr() : m_ptr() {}
  DocumentPtr(const DocumentPtr & other) : m_ptr(other.m_ptr) {}
  ~DocumentPtr() {
    // Fixme: *this return bool ???
    // Fixme: signal ???
    //// qATInfo() << "--- Delete DocumentPtr of" << *m_ptr;
    // qATInfo() << "--- Delete DocumentPtr";
    // m_ptr.clear();
  }

  DocumentPtr & operator=(const DocumentPtr & other) {
    if (this != &other)
      m_ptr = other.m_ptr;
    return *this;
   }

  // QoRowTraits ctor
  DocumentPtr(const QSharedPointer<Class> & ptr) : m_ptr(ptr) {}
  DocumentPtr(const Class & other) : m_ptr(new Class(other)) {} // Fixme: clone ?
  DocumentPtr(const QJsonObject & json_object) : m_ptr(new Class(json_object)) {}
  DocumentPtr(const QVariantHash & variant_hash) : m_ptr(new Class(variant_hash)) {}
  DocumentPtr(const QVariantList & variants) : m_ptr(new Class(variants)) {}
  DocumentPtr(const QSqlRecord & record) : m_ptr(new Class(record)) {}
  DocumentPtr(const QSqlQuery & query, int offset = 0) : m_ptr(new Class(query, offset)) {}

  // QSharedPointer API

  QSharedPointer<Class> & ptr() { return m_ptr; }
  QWeakPointer<Class> toWeakRef() const { return m_ptr.toWeakRef(); }

  Class & operator*() const { return *m_ptr; }
  Class * data() { return m_ptr.data(); }
  const Class * data() const { return m_ptr.data(); } // not in the QSharedPointer API

  // row_ptr->method()
  Class * operator->() const { return m_ptr.data(); }

  operator bool() const { return static_cast<bool>(m_ptr); }
  bool isNull() const { return m_ptr.isNull(); }
  bool operator!() const { return m_ptr.isNull(); }

  void clear() { m_ptr.clear(); } // Fixme: danger ???

  bool operator==(const DocumentPtr & other) const { return m_ptr == other.m_ptr; }

  // Relations API

private:
  QSharedPointer<Class> m_ptr;
};

// uint qHash(const DocumentPtr & obj) { return static_cast<uint>(obj.data()); }

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const DocumentPtr & obj);
#endif

/**************************************************************************************************/

class DocumentCache : public QObject
{
  Q_OBJECT

public:
  typedef Document * t_Key;
  typedef DocumentPtr Ptr;
  typedef QList<Ptr> PtrList;

public:
  DocumentCache();
  ~DocumentCache();

   void add(Ptr & ptr);
   void remove(Ptr & ptr);

    // Fixme: efficiency, QMap has key iterator but not value iterator
   PtrList items() { return m_loaded_instances.values(); }
   const PtrList items() const { return m_loaded_instances.values(); }

public slots:
  void on_changed();

private:
  // QLinkedList<Ptr> m_loaded_instances;
  // QLinkedList<Ptr> m_modified_instances;
  QMap<t_Key, Ptr> m_loaded_instances;
  QMap<t_Key, Ptr> m_modified_instances;
};

/**************************************************************************************************/

class DocumentModel : public QAbstractListModel
{
  Q_OBJECT

public:
  typedef DocumentPtr Item;
  typedef QList<Item> ItemList;

public:
  DocumentModel();
  DocumentModel(const ItemList & items);
  ~DocumentModel();

  // Fixme: use DocumentSchema::Fields ???
  enum Roles {
    ID = Qt::UserRole + 1,
    NAME,
    AUTHOR,
    VERSION,
    DATE,
    DESCRIPTION,
    URL,
    SIZE
  };
  Q_ENUMS(Roles) // Fixme: ???

  // QAbstractListModel API
  int rowCount(const QModelIndex & parent) const;
  QVariant data(const QModelIndex & index, int role) const;
  QHash<int, QByteArray> roleNames() const;

  void clear_items();
  void set_items(const ItemList & items);

private:
  ItemList m_items;
};

/**************************************************************************************************/

class DocumentDatabaseSchema : public QoDatabaseSchema
{
public:
  DocumentDatabaseSchema(QoDatabase & database);
  DocumentDatabaseSchema(const DocumentDatabaseSchema & other) = delete;
  ~DocumentDatabaseSchema();

  DocumentDatabaseSchema & operator=(const DocumentDatabaseSchema & other) = delete;

  QoDatabaseTable & document() { return *m_document; }

private:
  template<class T> void register_row(typename T::Ptr & row);

private:
  QoDatabaseTable * m_document;
  DocumentCache m_document_cache;
};

/**************************************************************************************************/
#endif /* __DOCUMENT_H__ */