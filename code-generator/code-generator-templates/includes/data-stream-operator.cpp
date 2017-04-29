{# -*- mode: fundamental -*- -#}
QDataStream &
operator<<(QDataStream & out, const {{class_name}} & obj)
{
{%- for member in members %}
  out << obj.{{member.name}}();{% endfor %}

  return out;
}

QDataStream &
operator>>(QDataStream & in, {{class_name}} & obj)
{
{%- for type in member_types %}
  {{type}} _{{type|replace(' ', '_')}};{% endfor %}
{% for member in members %}
  in >> _{{member.type}};
  obj.set_{{member.name}}(_{{member.type}});{% endfor %}

  return in;
}
