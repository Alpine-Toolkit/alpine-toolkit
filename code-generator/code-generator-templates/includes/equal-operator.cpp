{# -*- mode: fundamental -*- -#}
bool
{{class_name}}::operator==(const {{class_name}} & other)
{
{%- for member in members %}
  if (m_{{member.name}} != other.m_{{member.name}})
    return false;{% endfor %}

  return true;
}
