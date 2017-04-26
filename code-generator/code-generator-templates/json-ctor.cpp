{# -*- mode: fundamental -*- -#}
{{class_name}}::{{class_name}}(const QJsonObject & json_object)
 : {{class_name}}()
{
{%- for member in members %}
   m_{{member.name}} = json_object[QLatin1String("{{member.name}}")].{{member.from_variant}}();{% endfor %}
}
