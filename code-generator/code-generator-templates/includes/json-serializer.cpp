{# -*- mode: fundamental -*- -#}

{%- macro to_json(field) -%}
{% if field.variable.cast_to_json %}{{field.variable.cast_to_json}}(m_{{field.name}}){% else %}QJsonValue(m_{{field.name}}){% endif %}
{%- endmacro -%}

{%- macro insert(field) -%}
  {#- json_object[] = -#}
  json_object.insert(QLatin1String("{{field.json_name}}"), {{ to_json(field) }});
{%- endmacro -%}

QJsonObject
{{class_name}}::to_json(bool only_changed) const
{
  QJsonObject json_object;

 if (only_changed) {
{%- for field in fields %}
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

{%- macro insert(field) -%}
variant_hash[QLatin1String("{{field.name}}")] = {{ cast_to_variant(field) }};
{%- endmacro -%}

{%- macro to_variant(prefix) %}
QVariantHash
{{class_name}}::to_variant_hash{{prefix}}(bool only_changed) const
{
  QVariantHash variant_hash;

  if (only_changed) {
{%- for field in fields %}
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
{% endmacro -%}

{%- macro cast_to_variant(field) -%}
{% if field.variable.cast_variant %}QVariant::fromValue(m_{{field.name}}){% else %}m_{{field.name}}{% endif %}
{%- endmacro -%}

{# fix blank line #}
{{ to_variant('') }}

QVariantList
{{class_name}}::to_variant_list() const
{
  QVariantList variants;

{%- for field in fields %}
  variants << {{ cast_to_variant(field) }};
{%- endfor %}

  return variants;
}
