{# -*- mode: fundamental -*- -#}

{%- from "includes/data-stream-operator.jinja" import data_streamer_decl %}
{%- from "includes/debug.jinja" import debug_streamer_decl -%}
{%- from "includes/property.jinja" import property -%}
{%- from "includes/singleton.jinja" import singleton -%}

{%- set class_name_schema = schema.schema_cls_name %}
{%- set class_name_ptr = schema.ptr_cls_name %}
{%- set class_name_cache = schema.cache_cls_name %}

class {{class_name}};
class {{class_name_ptr}};
{# #}
{%- for relation in schema.relations %}
{%- if relation.is_one_to_many %}
class {{relation.cls_name}};
class {{relation.ptr_cls_name}};
{% endif %}{% endfor %}

/**************************************************************************************************/

class {{class_name_schema}} : public QcSchema
{
public:
  enum Fields {
{%- for member in members %}
    {{member.name|upper}}{% if not loop.last %},{% endif %}{% endfor %}
  };
  static const int NUMBER_OF_FIELDS = {{ members|count }};

{{ singleton(class_name_schema) }}
};

/**************************************************************************************************/

class {{class_name}} : public QObject, public {{schema.base_class}}<{{class_name_schema}}>
{
  Q_OBJECT
{%- for member in members %}
  {{ property(member.name, member.type) }}{% endfor %}

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

  bool operator==(const {{class_name}} & other);

  // Getter/Setter
{# #}
{%- for member in members %}
  {{member.getter_type}} {{member.name}}() const { return m_{{member.name}}; }
  void set_{{member.name}}({{member.setter_type}} value);
{% endfor -%}
{# #}
{%- if schema.has_rowid_primary_key %}
  void set_insert_id(int id);
  bool exists_on_database() const { return m_{{schema.rowid_primary_key.name}} > 0; } // require NOT NULL
{%- endif %}

  // JSON Serializer
  QJsonObject to_json(bool only_changed = false) const;

  // Generic Variant Serializer
  QVariantHash to_variant_hash(bool only_changed = false) const;
  QVariantList to_variant_list() const;

  // SQL Serializer
  QVariantHash to_variant_hash_sql(bool only_changed = false, bool duplicate = false) const;
  QVariantList to_variant_list_sql(bool duplicate = false) const;

  // Query for update
{%- for member in members %}
  bool is_{{member.name}}_modified() const { return bit_status(Schema::Fields::{{member.name|upper}}); }{% endfor %}

  // Field accessor by position
  QVariant field(int position) const;
  void set_field(int position, const QVariant & value);
{# #}
{%- if schema.relations %}
{%- if schema.has_foreign_keys %}
  bool can_save() const;{% endif %}
  void load_relations();
  void save_relations();
{%- for relation in schema.relations %}
  {%- if relation.is_many_to_one %}
  {{relation.ptr_cls_name}} {{relation.name}}();
  {% endif -%}
  {%- if relation.is_one_to_many %}
  QcRowList<{{relation.cls_name}}, {{relation.ptr_cls_name}}> & {{relation.name}}() { return m_{{relation.name}}; }
  {% endif -%}
  {% endfor %}
{% endif -%}
{# #}
  bool can_update() const; // To update row
  QVariantHash rowid_kwargs() const;

signals:
  void changed();
{%- for member in members %}
  void {{member.name}}Changed();{% endfor %}

private:
{%- for member in members %}
  {{member.type}} m_{{member.name}};{% endfor %}
{%- for relation in schema.relations %}
  {%- if relation.is_many_to_one %}
  {{relation.ptr_cls_name}} m_{{relation.name}};
  {% endif -%}
  {%- if relation.is_one_to_many %}
  QcRowList<{{relation.cls_name}}, {{relation.ptr_cls_name}}> m_{{relation.name}};
  {% endif %}{% endfor %}
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
    // qInfo() << "--- Delete {{class_name_ptr}} of" << *m_ptr;
    qInfo() << "--- Delete {{class_name_ptr}}";
    // m_ptr.clear();
  }

  {{class_name_ptr}} & operator=(const {{class_name_ptr}} & other) {
    if (this != &other)
      m_ptr = other.m_ptr;
    return *this;
   }

  // QcRowTraits ctor
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
{%- if relation.is_many_to_one %}
  void set_{{relation.name}}({{relation.ptr_cls_name}} & value);
{% endif %}{% endfor %}

private:
  QSharedPointer<Class> m_ptr;
};

// uint qHash(const {{class_name_ptr}} & obj) { return static_cast<uint>(obj.data()); }

{{ debug_streamer_decl(class_name_ptr) }}

/**************************************************************************************************/

class {{class_name_cache}} : public QObject
{
  Q_OBJECT

public:
  {{class_name_cache}}();
  ~{{class_name_cache}}();

   void add({{class_name_ptr}} & ptr);
   void remove({{class_name_ptr}} & ptr);

public slots:
  void on_changed();

private:
  // QLinkedList<{{class_name_ptr}}> m_loaded_instances;
  // QLinkedList<{{class_name_ptr}}> m_modified_instances;
  QMap<{{class_name}} *, {{class_name_ptr}}> m_loaded_instances;
  QMap<{{class_name}} *, {{class_name_ptr}}> m_modified_instances;
};
