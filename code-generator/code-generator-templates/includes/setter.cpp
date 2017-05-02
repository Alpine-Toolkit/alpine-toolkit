{# -*- mode: fundamental -*- -#}
void
{{class_name}}::set_{{member.name}}({{member.setter_type}} value)
{
  if (m_{{member.name}} != value) {
    m_{{member.name}} = value;
    set_bit(Schema::Fields::{{member.name|upper}});
    emit {{member.name}}Changed();
  }
}
