{# -*- mode: fundamental -*- -#}
QVariant
{{class_name}}::field(int position) const
{
  switch(position) {
{%- for field in fields %}
   case {{class_name}}Schema::Fields::{{field.name|upper}}: return m_{{field.name}};{% endfor %}
  }
}

void
{{class_name}}::set_field(int position, const QVariant & value)
{
  switch(position) {
{%- for field in fields %}
   case {{class_name}}Schema::Fields::{{field.name|upper}}: m_{{field.name}} = value.{{field.variable.from_variant}}();{% endfor %}
  }
}
