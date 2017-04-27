{# -*- mode: fundamental -*- -#}
{%- macro insert(field) -%}
  json_object.insert(QLatin1String("{{field.json_name}}"), QJsonValue({{field.variable.m_to_json}}));
{%- endmacro -%}
QJsonObject
{{class_name}}::to_json(bool only_changed) const
{
  QJsonObject json_object;

 if (only_changed) {
{%- for field in fields %}
    {#- if (m_bits[{{class_name}}Schema::Fields::{{field.name|upper}}]) #}
    if (is_{{field.name}}_modified())
      {{ insert(field) }}
{%- endfor %}
  } else {
{%- for field in fields %}
    {{ insert(field) }}
{%- endfor %}
  }

  return json_object;
}

{%- macro to_variant(prefix) -%}
QVariantHash
{{class_name}}::to_variant_hash{{prefix}}(bool only_changed) const
{
  QVariantHash variant_hash;

  if (only_changed) {
{%- for field in fields %}
    {#- if (m_bits[{{class_name}}Schema::Fields::{{field.name|upper}}]) #}
    if (is_{{field.name}}_modified())
      {{ insert(field) }}
{%- endfor %}
  } else {
{%- for field in fields %}
    {{ insert(field) }}
{%- endfor %}
  }

  return variant_hash;
}
{%- endmacro %}

{% macro insert(field) -%}
variant_hash[QLatin1String("{{field.name}}")] = m_{{field.name}};
{%- endmacro -%}
{{ to_variant('') }}

{% macro insert(field) -%}
variant_hash[QLatin1String("{{field.sql_name}}")] = m_{{field.name}};
{%- endmacro -%}
{{ to_variant('_sql') }}

{% macro insert(field) -%}
variant_hash[QLatin1String("{{field.json_name}}")] = m_{{field.name}};
{%- endmacro -%}
{{ to_variant('_json') }}

QVariantList
{{class_name}}::to_variant_list() const
{
  QVariantList variants;

{%- for field in fields %}
  variants << m_{{field.name}};
{%- endfor %}

  return variants;
}
