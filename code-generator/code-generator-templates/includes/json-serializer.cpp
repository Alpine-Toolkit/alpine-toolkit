{# -*- mode: fundamental -*- -#}
QJsonObject
{{class_name}}::to_json(bool only_changed) const
{
  QJsonObject json_object;

 if (only_changed) {
{%- macro insert(member) -%}
  json_object.insert(QLatin1String("{{member.name}}"), QJsonValue({{member.m_to_json}}));
{%- endmacro -%}
{%- for member in members %}
    {#- if (m_bits[{{class_name}}Schema::FieldPosition::{{member.name|upper}}]) #}
    if (is_{{member.name}}_modified())
      {{ insert(member) }}
{%- endfor %}
  } else {
{%- for member in members %}
    {{ insert(member) }}
{%- endfor %}
  }

  return json_object;
}

QVariantMap
{{class_name}}::to_variant_map(bool only_changed) const
{
  QVariantMap variant_map;

 if (only_changed) {
{%- macro insert(member) -%}
variant_map[QLatin1String("{{member.name}}")] = {{member.m_name}};
{%- endmacro -%}
{%- for member in members %}
    {#- if (m_bits[{{class_name}}Schema::FieldPosition::{{member.name|upper}}]) #}
    if (is_{{member.name}}_modified())
      {{ insert(member) }}
{%- endfor %}
  } else {
{%- for member in members %}
    {{ insert(member) }}
{%- endfor %}
  }

  return variant_map;
}
