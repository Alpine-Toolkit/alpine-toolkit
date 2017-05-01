{# -*- mode: fundamental -*- -#}

{%-  macro set_member(name, value, cast) -%}
m_{{name}} = {% if cast -%}{{cast}}({{ value }}){%- else -%}{{ value }}{%- endif %};
{%- endmacro -%}

{%- macro from_json(json_name, from_json) -%}
json_object[QLatin1String("{{json_name}}")]{% if from_json %}.{{from_json}}(){% endif %}
{%- endmacro -%}

{%- macro from_variant_hash(field) -%}
variant_hash[QLatin1String("{{field.name}}")].{{field.variable.from_variant}}()
{%- endmacro -%}

{%- macro from_record(i, field) -%}
record.value({{i}}).{{field.variable.from_variant}}()
{%- endmacro -%}

{%- macro from_query(i, field) -%}
query.value({{i}}).{{field.variable.from_variant}}()
{%- endmacro -%}

{{class_name}}::{{class_name}}(const QJsonObject & json_object)
 : {{class_name}}()
{
{%- for field in schema %}
  {{ set_member(field.name,
                from_json(field.name, field.variable.from_json),
                field.variable.cast_from_json)
  }}{% endfor %}
}

{{class_name}}::{{class_name}}(const QVariantHash & variant_hash)
 : {{class_name}}()
{
{%- for field in schema %}
  {{ set_member(field.name, from_variant_hash(field), field.variable.cast_from_variant) }}{% endfor %}
}

{{class_name}}::{{class_name}}(const QVariantList & variants)
 : {{class_name}}()
{
{%- macro from_variant_list(i, field) -%}
variants[{{i}}].{{field.variable.from_variant}}()
{%- endmacro -%}
{%- for field in schema %}
  {{ set_member(field.name, from_variant_list(loop.index0, field), field.variable.cast_from_variant) }}{% endfor %}
}
