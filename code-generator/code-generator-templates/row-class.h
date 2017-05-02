{# -*- mode: fundamental -*- -#}
{%- from "includes/singleton.h" import singleton -%}
{%- from "includes/property.h" import property -%}

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
  bool is_modified() const { return not m_bits.isNull(); }
{%- for member in members %}
  bool is_{{member.name}}_modified() const { return m_bits[{{class_name}}Schema::Fields::{{member.name|upper}}]; }{% endfor %}

  // Field accessor by position
  QVariant field(int position) const;
  void set_field(int position, const QVariant & value);

signals:
{%- for member in members %}
  void {{member.name}}Changed();{% endfor %}

private:
{%- for member in members %}
  {{member.type}} m_{{member.name}};{% endfor %}
};

{% include "includes/data-stream-operator.h" %}

{% include "includes/debug.h" %}
