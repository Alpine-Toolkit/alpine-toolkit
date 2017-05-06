{# -*- mode: fundamental -*- -#}

{%- macro variant_from_record(i) -%}
record.value({{i}})
{%- endmacro -%}

{%- macro variant_from_query(i) -%}
query.value({{i}})
{%- endmacro -%}

{%- macro from_variant(field, variant) -%}
{{variant}}.{{field.variable.from_variant}}()
{%- endmacro -%}

{%- macro cast_from_variant(value, cast) -%}
{% if cast -%}{{cast}}({{value}}){%- else -%}{{value}}{%- endif %}
{%- endmacro -%}

{%- macro get_field_value(field, variant) -%}
{%- if field.type_conversion.cast_from_sql -%}
{{field.type_conversion.cast_from_sql}}({{variant}})
{%- else -%}
{{ cast_from_variant(from_variant(field, variant), field.variable.cast_from_variant) }}
{%- endif -%}
{%- endmacro -%}

{%- macro set_member(field, value) -%}
m_{{field.name}} = {{ get_field_value(field, value) }};
{%- endmacro -%}



{{class_name}}::{{class_name}}(const QSqlRecord & record)
 : {{base_class}}(record)
{
{%- for field in schema %}
  {{ set_member(field, variant_from_record(loop.index0)) }}{% endfor %}
}

{{class_name}}::{{class_name}}(const QSqlQuery & query)
 : {{base_class}}(query)
{
{%- for field in schema %}
  {{ set_member(field, variant_from_query(loop.index0)) }}{% endfor %}
}
