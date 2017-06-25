{# -*- mode: fundamental -*- -#}

{#  ################################################################################################
 #
 # $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 #
 # Copyright (C) 2017 Fabrice Salvaire
 # Contact: http://www.fabrice-salvaire.fr
 #
 # This file is part of the QtCarto library.
 #
 # This program is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with this program.  If not, see <http://www.gnu.org/licenses/>.
 #
 # $ALPINE_TOOLKIT_END_LICENSE$
 #
 ############################################################################################### -#}

{% from "includes/data-stream-operator.jinja" import data_streamer_decl %}
{% from "includes/debug.jinja" import debug_streamer_decl %}
{% from "includes/property.jinja" import property, read_only_property %}
{% from "includes/singleton.jinja" import singleton -%}

{% set class_name = schema.cls_name %}
{% set class_name_schema = schema.schema_cls_name %}
{% set class_name_ptr = schema.ptr_cls_name %}
{% set class_name_cache = schema.cache_cls_name %}
{% set class_name_model = schema.model_cls_name %}
{% set members = schema.members %}
{% if schema.has_post_init %}
{% set post_init = 'post_init' %}
{% endif %}

class {{class_name}};
class {{class_name_ptr}};

{% for relation in schema.relations %}
{% if relation.is_one_to_many %}
class {{relation.cls_name}};
class {{relation.ptr_cls_name}};
{% endif %}
{% endfor %}{# space #}

/**************************************************************************************************/

class {{class_name_schema}} : public QcSchema
{
public:
  enum Fields {
{% for member in members %}
    {{member.name|upper}}{% if not loop.last %},{% endif %} 
{% endfor %}{# space #}
  };
  static const int NUMBER_OF_FIELDS = {{ members|count }};

{{ singleton(class_name_schema) }}

{%- if custom_class_schema %}
// Custom Declarations
{{custom_class_schema}}
{% endif %} 
};

/**************************************************************************************************/

class {{class_name}} : public QObject, public {{schema.base_class}}<{{class_name_schema}}>
{
  Q_OBJECT
{% for member in members %}
  {{ property(member.name, member.type) }}
{% endfor %}
{% for member in schema.computed_members %}
  {{ read_only_property(member.name, member.type) }}
{% endfor %}

public:
  typedef {{class_name_ptr}} Ptr;
  typedef QList<Ptr> PtrList;
  friend class {{class_name_ptr}};

public:
  {{class_name}}();
  {{class_name}}(const {{class_name}} & other);
  {{class_name}}(const QJsonObject & json_object); // JSON deserializer
  {{class_name}}(const QVariantHash & variant_hash);
  {{class_name}}(const QVariantList & variants);
  {{class_name}}(const QSqlRecord & record); // SQL deserializer
  {{class_name}}(const QSqlQuery & query, int offset = 0); // SQL deserializer
  ~{{class_name}}();

  {{class_name}} & operator=(const {{class_name}} & other);

  bool operator==(const {{class_name}} & other) const;

  // Getter/Setter

{% for member in members %}
  {{member.getter_type}} {{member.name}}() const { return m_{{member.name}}; }
  void set_{{member.name}}({{member.setter_type}} value);

{% endfor -%}

{% if schema.has_rowid_primary_key %}
  void set_insert_id(int id);
  bool exists_on_database() const { return m_{{schema.rowid_primary_key.name}} > 0; } // require NOT NULL
{% endif %}

  // JSON Serializer
  QJsonObject to_json(bool only_changed = false) const;

  // Generic Variant Serializer
  QVariantHash to_variant_hash(bool only_changed = false) const;
  QVariantList to_variant_list() const;

  // SQL Serializer
  QVariantHash to_variant_hash_sql(bool only_changed = false, bool duplicate = false) const;
  QVariantList to_variant_list_sql(bool duplicate = false) const;

  // Query for update
{% for member in members %}
  bool is_{{member.name}}_modified() const { return bit_status(Schema::Fields::{{member.name|upper}}); }
{% endfor %}

  // Field accessor by position
  QVariant field(int position) const;
  void set_field(int position, const QVariant & value);

{% if schema.relations %}
{% if schema.has_foreign_keys %}
  bool can_save() const;
{% endif %}{# space #}

  void load_relations();
  void save_relations();

{% for relation in schema.relations %}{# space #}
{% if relation.is_many_to_one %}
  {{relation.ptr_cls_name}} {{relation.name}}();
{% endif %}
{% if relation.is_one_to_many %}
  QcRowList<{{relation.cls_name}}, {{relation.ptr_cls_name}}> & {{relation.name}}() { return m_{{relation.name}}; }
{% endif %}
{% endfor %}
{% endif %}

  bool can_update() const; // To update row
  QVariantHash rowid_kwargs() const;

signals:
  void changed();
{% for member in members %}
  void {{member.name}}Changed();
{% endfor %}
{% for member in schema.computed_members %}
  void {{member.name}}Changed();
{% endfor %}

{% if schema.has_post_init %}
private:
  void post_init();
{% endif %}{# space #}

private:
{% for member in members %}
  {{member.type}} m_{{member.name}};
{% endfor -%}

{% for relation in schema.relations %}
{% if relation.is_many_to_one %}
  {{relation.ptr_cls_name}} m_{{relation.name}};
{% endif %}
{% if relation.is_one_to_many %}
  QcRowList<{{relation.cls_name}}, {{relation.ptr_cls_name}}> m_{{relation.name}};
{% endif %}
{% endfor %}

{%- if custom_cls_decl %}

// Custom Declarations
{{custom_cls_decl}}
{% endif %} 
};

{{ data_streamer_decl(class_name, members) }}

{{ debug_streamer_decl(class_name) }}

/**************************************************************************************************/

class {{class_name_ptr}}
{
public:
  typedef {{class_name}} Class;

public:
  {{class_name_ptr}}() : m_ptr() {}
  {{class_name_ptr}}(const {{class_name_ptr}} & other) : m_ptr(other.m_ptr) {}
  ~{{class_name_ptr}}() {
    // Fixme: *this return bool ???
    // Fixme: signal ???
    //// qInfo() << "--- Delete {{class_name_ptr}} of" << *m_ptr;
    // qInfo() << "--- Delete {{class_name_ptr}}";
    // m_ptr.clear();
  }

  {{class_name_ptr}} & operator=(const {{class_name_ptr}} & other) {
    if (this != &other)
      m_ptr = other.m_ptr;
    return *this;
   }

  // QcRowTraits ctor
  {{class_name_ptr}}(const QSharedPointer<Class> & ptr) : m_ptr(ptr) {}
  {{class_name_ptr}}(const Class & other) : m_ptr(new Class(other)) {} // Fixme: clone ?
  {{class_name_ptr}}(const QJsonObject & json_object) : m_ptr(new Class(json_object)) {}
  {{class_name_ptr}}(const QVariantHash & variant_hash) : m_ptr(new Class(variant_hash)) {}
  {{class_name_ptr}}(const QVariantList & variants) : m_ptr(new Class(variants)) {}
  {{class_name_ptr}}(const QSqlRecord & record) : m_ptr(new Class(record)) {}
  {{class_name_ptr}}(const QSqlQuery & query, int offset = 0) : m_ptr(new Class(query, offset)) {}

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

  bool operator==(const {{class_name_ptr}} & other) const { return m_ptr == other.m_ptr; }

  // Relations API
{% for relation in schema.relations %}
{% if relation.is_many_to_one %}
  void set_{{relation.name}}({{relation.ptr_cls_name}} & value);
{% endif %}
{% endfor %}

private:
  QSharedPointer<Class> m_ptr;

{%- if custom_class_ptr %}
// Custom Declarations
{{custom_class_ptr}}
{% endif %} 
};

// uint qHash(const {{class_name_ptr}} & obj) { return static_cast<uint>(obj.data()); }

{{ debug_streamer_decl(class_name_ptr) }}

/**************************************************************************************************/

class {{class_name_cache}} : public QObject
{
  Q_OBJECT

public:
  typedef {{class_name}} * t_Key;
  typedef {{class_name_ptr}} Ptr;
  typedef QList<Ptr> PtrList;

public:
  {{class_name_cache}}();
  ~{{class_name_cache}}();

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

{%- if custom_class_cache %}
// Custom Declarations
{{custom_class_cache}}
{% endif %} 
};

/**************************************************************************************************/

class {{class_name_model}} : public QAbstractListModel
{
  Q_OBJECT

public:
  typedef {{class_name_ptr}} Item;
  typedef QList<Item> ItemList;

public:
  {{class_name_model}}();
  {{class_name_model}}(const ItemList & items);
  ~{{class_name_model}}();

  // Fixme: use {{class_name_schema}}::Fields ???
  enum Roles {
{% for member in members + schema.computed_members %}
    {{member.name|upper}}{% if loop.first %} = Qt::UserRole + 1{% endif %}{% if not loop.last %},{% endif %} 
{% endfor %}{# space #}
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

{%- if custom_class_model %}
// Custom Declarations
{{custom_class_model}}
{% endif %} 
};

/**************************************************************************************************/

