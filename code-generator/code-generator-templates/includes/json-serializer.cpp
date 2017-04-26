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

QVariantHash
{{class_name}}::to_variant_hash(bool only_changed) const
{
  QVariantHash variant_hash;

 if (only_changed) {
{%- macro insert(member) -%}
variant_hash[QLatin1String("{{member.name}}")] = {{member.m_name}};
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

  return variant_hash;
}
