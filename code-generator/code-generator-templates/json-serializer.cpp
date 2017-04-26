{# -*- mode: fundamental -*- -#}
QJsonObject
{{class_name}}::to_json(bool only_changed) const
{
  QJsonObject json_object;

  if (only_changed) {
{%- for member in members %}
    if (m_bits[FieldPosition::{{member.name|upper}}])
      json_object.insert(QLatin1String("{{member.name}}"), QJsonValue({{member.m_name}}));
{%- endfor %}
  } else {
{%- for member in members %}
    json_object.insert(QLatin1String("{{member.name}}"), QJsonValue({{member.m_name}}));
{%- endfor %}
  }

  return json_object;
}
