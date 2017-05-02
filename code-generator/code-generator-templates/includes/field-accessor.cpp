{# -*- mode: fundamental -*- -#}

{%- macro field_enum(field) -%}
Schema::Fields::{{field.name|upper}}
{%- endmacro -%}

{%- macro cast_to_variant(field) -%}
{% if field.variable.cast_variant %}QVariant::fromValue(m_{{field.name}}){% else %}m_{{field.name}}{% endif %}
{%- endmacro -%}

{%-  macro from_variant(field, value) -%}
value.{{field.variable.from_variant}}()
{%- endmacro -%}

{%-  macro set_member(name, value, cast) -%}
m_{{name}} = {% if cast -%}{{cast}}({{ value }}){%- else -%}{{ value }}{%- endif %}
{%- endmacro -%}

QVariant
{{class_name}}::field(int position) const
{
  switch(position) {
{%- for field in schema %}
   case {{ field_enum(field) }}:
     return {{ cast_to_variant(field) }};{% endfor %}
   default:
     return QVariant(); // error
  }
}

void
{{class_name}}::set_field(int position, const QVariant & value)
{
  switch(position) {
{%- for field in schema %}
   case {{ field_enum(field) }}: {
     {{ set_member(field.name, from_variant(field, value), field.variable.cast_from_variant) }};
     break;
   }{% endfor %}
  }
}
