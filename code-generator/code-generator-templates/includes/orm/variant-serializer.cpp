{# -*- mode: fundamental -*- -#}

{%- macro cast_to_variant(field) -%}
{% if field.variable.cast_variant %}QVariant::fromValue(m_{{field.name}}){% else %}m_{{field.name}}{% endif %}
{%- endmacro -%}

{%- macro insert(field) -%}
variant_hash[QLatin1String("{{field.name}}")] = {{ field_value(field) }};
{%- endmacro -%}

{%- macro to_variant_hash(prefix, fields) %}
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
{%- endmacro -%}

{%- macro to_variant_list(prefix, fields) %}
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



{#- Fixme: can use call -#}
{%- macro field_value(field) -%}
{{ cast_to_variant(field) }}
{%- endmacro -%}

{{ to_variant_hash('', schema) }}

{{ to_variant_list('', schema) }}

{%- macro field_value(field) -%}
{% if field.type_conversion.cast_to_sql %}{{field.type_conversion.cast_to_sql}}(m_{{field.name}}){% else %}{{ cast_to_variant(field) }}{% endif %}
{%- endmacro -%}

{{ to_variant_hash('_sql', schema) }}

{{ to_variant_list('_sql', schema) }}
