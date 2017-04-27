{# -*- mode: fundamental -*- -#}
{{class_name}}::{{class_name}}(const QJsonObject & json_object)
 : {{class_name}}()
{
{%- macro from_json(field) -%}
json_object[QLatin1String("{{field.json_name}}")].{{field.variable.from_json}}()
{%- endmacro -%}
{%- for field in fields %}
  {%- if field.from_json_cast %}
   m_{{field.name}} = {{field.variable.from_json_cast}}({{ from_json(field) }});
  {%- else %}
   m_{{field.name}} = {{ from_json(field) }};
  {%- endif %}{% endfor %}
}

{{class_name}}::{{class_name}}(const QVariantHash & variant_hash)
 : {{class_name}}()
{
{%- for field in fields %}
   m_{{field.name}} = variant_hash[QLatin1String("{{field.name}}")].{{field.variable.from_variant}}();{% endfor %}
}

{{class_name}}::{{class_name}}(const QVariantList & variants)
 : {{class_name}}()
{
{%- for field in fields %}
   m_{{field.name}} = variants[{{loop.index0}}].{{field.variable.from_variant}}();{% endfor %}
}

{{class_name}}::{{class_name}}(const QSqlRecord & record)
 : {{class_name}}()
{
{%- for field in fields %}
   m_{{field.name}} = record.value({{loop.index0}}).{{field.variable.from_variant}}();{% endfor %}
}

{{class_name}}::{{class_name}}(const QSqlQuery & query)
 : {{class_name}}()
{
{%- for field in fields %}
   m_{{field.name}} = query.value({{loop.index0}}).{{field.variable.from_variant}}();{% endfor %}
}
