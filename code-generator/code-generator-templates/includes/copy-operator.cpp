{# -*- mode: fundamental -*- -#}
{{class_name}} &
{{class_name}}::operator=(const {{class_name}} & other)
{
  if (this != &other) {
{%- for member in members %}
    m_{{member.name}} = other.m_{{member.name}};{% endfor %}
  }

  return *this;
}
