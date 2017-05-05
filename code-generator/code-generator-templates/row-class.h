{# -*- mode: fundamental -*- -#}

{%- from "includes/data-stream-operator.jinja" import data_streamer_decl %}
{%- from "includes/debug.jinja" import debug_streamer_decl -%}
{%- from "includes/property.jinja" import property -%}
{%- from "includes/singleton.jinja" import singleton -%}

class {{class_name}};
{# #}
{%- with class_name_schema = class_name + 'Schema' %}
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
{%- endwith %}

/**************************************************************************************************/

class {{class_name}} : public QObject, public QcRowWithId<{{class_name}}Schema>
{
  Q_OBJECT
{%- for member in members %}
  {{ property(member.name, member.type) }}{% endfor %}

public:
  {{class_name}}();
  {{class_name}}(const {{class_name}} & other);
  {{class_name}}(const QJsonObject & json_object); // JSON deserializer
  {{class_name}}(const QVariantHash & variant_hash);
  {{class_name}}(const QVariantList & variants);
  {{class_name}}(const QSqlRecord & record); // SQL deserializer
  {{class_name}}(const QSqlQuery & query); // SQL deserializer
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
  // JSON Serializer
  QJsonObject to_json(bool only_changed = false) const;

  // Generic Variant Serializer
  QVariantHash to_variant_hash(bool only_changed = false) const;
  QVariantList to_variant_list() const;

  // SQL Serializer
  QVariantHash to_variant_hash_sql(bool only_changed = false) const;
  QVariantList to_variant_list_sql() const;

  // Query for update
{%- for member in members %}
  bool is_{{member.name}}_modified() const { return bit_status(Schema::Fields::{{member.name|upper}}); }{% endfor %}

  // Field accessor by position
  QVariant field(int position) const;
  void set_field(int position, const QVariant & value);
{# #}
{%- if schema.foreign_keys %}
  void load_foreign_keys();
{%- for member in schema.foreign_keys %}
  QSharedPointer<{{member.cls_name}}> {{member.relation_name}}();
  void set_{{member.relation_name}}(QSharedPointer<{{member.cls_name}}> & value);{% endfor %}
{% endif -%}
{# #}
signals:
{%- for member in members %}
  void {{member.name}}Changed();{% endfor %}

private:
{%- for member in members %}
  {{member.type}} m_{{member.name}};{% endfor %}
{%- for member in schema.foreign_keys %}
  QSharedPointer<{{member.cls_name}}> m_{{member.relation_name}} = nullptr;{% endfor %}
};

{{ data_streamer_decl(class_name, members) }}

{{ debug_streamer_decl(class_name) }}
