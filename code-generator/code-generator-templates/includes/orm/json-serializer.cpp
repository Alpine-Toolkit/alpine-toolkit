{# -*- mode: fundamental -*- -#}

{% macro to_json(field) -%}
{% if field.variable.cast_to_json -%}
{{field.variable.cast_to_json}}(m_{{field.name}})
{%- else -%}
QJsonValue(m_{{field.name}})
{%- endif %}
{%- endmacro -%}

{% macro insert(field) -%}
{# json_object[] = -#}
json_object.insert(QLatin1String("{{field.json_name}}"), {{ to_json(field) }});
{%- endmacro %}

QJsonObject
{{class_name}}::to_json(bool only_changed) const
{
  QJsonObject json_object;

 if (only_changed) {
{% for field in schema.json_fields %}
    if (is_{{field.name}}_modified())
      {{ insert(field) }}
{% endfor %}
  } else {
{% for field in schema.json_fields %}
    {{ insert(field) }}
{% endfor %}
  }

  return json_object;
}
