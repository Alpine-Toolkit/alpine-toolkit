{# -*- mode: fundamental -*- -#}
{{class_name}}::{{class_name}}(const QJsonObject & json_object)
 : {{class_name}}()
{
{%- macro from_json(member) -%}
json_object[QLatin1String("{{member.name}}")].{{member.from_json}}()
{%- endmacro -%}
{%- for member in members %}
  {%- if member.from_json_cast %}
   m_{{member.name}} = {{member.from_json_cast}}({{ from_json(member) }});
  {%- else %}
   m_{{member.name}} = {{ from_json(member) }};
  {%- endif %}{% endfor %}
}

{{class_name}}::{{class_name}}(const QVariantMap & variant_map)
 : {{class_name}}()
{
{%- for member in members %}
   m_{{member.name}} = variant_map[QLatin1String("{{member.name}}")].{{member.from_variant}}();{% endfor %}
}
