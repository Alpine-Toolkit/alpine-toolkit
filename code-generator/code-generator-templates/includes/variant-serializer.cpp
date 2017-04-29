{# -*- mode: fundamental -*- -#}

{%- macro cast_to_variant(field) -%}
{% if field.variable.cast_variant %}QVariant::fromValue(m_{{field.name}}){% else %}m_{{field.name}}{% endif %}
{%- endmacro -%}

{%- macro insert(field) -%}
variant_hash[QLatin1String("{{field.name}}")] = {{ field_value(field) }};
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

QVariantList
{{class_name}}::to_variant_list{{prefix}}() const
{
  QVariantList variants;

{%- for field in fields %}
  variants << {{ field_value(field) }};
{%- endfor %}

  return variants;
}
{% endmacro -%}

{%- macro field_value(field) -%}
{{ cast_to_variant(field) }}
{%- endmacro -%}

{{ to_variant('') }}

{%- macro field_value(field) -%}
{% if field.context.cast_to_sql_variant %}{{field.context.cast_to_sql_variant}}(m_{{field.name}}){% else %}{{ cast_to_variant(field) }}{% endif %}
{%- endmacro -%}

{{ to_variant('_sql') }}

