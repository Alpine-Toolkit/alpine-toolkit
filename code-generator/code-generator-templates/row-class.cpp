{# -*- mode: fundamental -*- -#}

{%- from "includes/accessor.jinja" import setter_impl -%}
{%- from "includes/cdtor.jinja" import ctor_impl, copy_ctor_impl, copy_operator_impl, dtor_impl -%}
{%- from "includes/data-stream-operator.jinja" import data_streamer_impl -%}
{%- from "includes/debug.jinja" import debug_streamer_impl -%}
{%- from "includes/operator.jinja" import equal_operator_impl -%}

{{class_name}}Schema::{{class_name}}Schema()
: QcSchema(QLatin1String("{{class_name}}"), QLatin1String("{{schema.table_name}}"))
{
{%- for field in schema %}
  {
    {{field.shema_field_ctor}} field(
      QLatin1String("{{field.name}}"),
      {% if field.is_foreign_key %}QLatin1String("{{field.foreign_key.dot_syntax}}"),{% endif %}
      QLatin1String("{{field.qt_type}}"),
      QLatin1String("{{field.sql_type}}"),
      QLatin1String("{{field.sql_name}}"),
      QLatin1String("{{field.json_name}}"),
      QLatin1String("{{field.title}}"),
      QLatin1String("{{field.description}}"));
    // Optional parameters
    {% if field.autoincrement %}field.set_autoincrement(true);{% endif %}
    {% if not field.nullable %}field.set_nullable(false);{% endif %}
    {% if field.unique %}field.set_unique(true);{% endif %}
    {% if field.default %}field.set_default_value({{field.default}});{% endif %}
    add_field(field);
  }{% endfor %}
}

{{ dtor_impl(class_name + "Schema") }}

/**************************************************************************************************/

{% set base_class = schema.base_class + "<" + class_name + "Schema>" -%}
{%- set base_classes = (base_class,) -%}

{{ ctor_impl(class_name, all_members, base_classes) }}

{{ copy_ctor_impl(class_name, all_members, base_classes) }}

{% include "includes/orm/json-ctor.cpp" %}

{% include "includes/orm/sql-ctor.cpp" %}

{{ dtor_impl(class_name) }}

// bit array ?
{{ copy_operator_impl(class_name, all_members, base_classes) }}

// bit array ?
{{ equal_operator_impl(class_name, members, base_classes) }}
{# #}
{%- for member in members %}
{{ setter_impl(class_name, member) }}
{% endfor %}
{# #}
{%- include "includes/orm/json-serializer.cpp" %}

{% include "includes/orm/variant-serializer.cpp" %}

{% include "includes/orm/field-accessor.cpp" %}
{# #}
{%- if schema.relations %}
void
{{class_name}}::load_relations()
{
{%- for relation in schema.relations %}
  {{relation.name}}();{% endfor %}
}
{# #}
{%- for relation in schema.relations %}
{%- if relation.is_one_to_many %}
QSharedPointer<{{relation.cls_name}}>
{{class_name}}::{{relation.name}}()
{
  if (m_{{relation.name}}.isNull())
    m_{{relation.name}} = database_schema()->query_by_id<{{relation.cls_name}}>(m_{{relation.foreign_key_name}});
  return m_{{relation.name}};
}

void
{{class_name}}::set_{{relation.name}}(QSharedPointer<{{relation.cls_name}}> & value)
{
{#
{%- if relation.peer_relation %}
  QSharedPointer<{{class_name}}> self(this);
  if (not m_{{relation.name}}.isNull())
    m_{{relation.name}}->{{relation.peer_relation.name}}().remove(self);
{% endif %}
#}
  m_{{relation.name}} = value;
  set_{{relation.foreign_key_name}}(value->id());
{#
{%- if relation.peer_relation %}
  m_{{relation.name}}->{{relation.peer_relation.name}}().append(self);
{% endif -%}
#}
}

void
{{class_name}}Ptr::set_{{relation.name}}({{relation.cls_name}}Ptr & value)
{
{%- if relation.peer_relation %}
  if (not m_ptr->m_{{relation.name}}.isNull())
    m_ptr->m_{{relation.name}}->{{relation.peer_relation.name}}().remove(ptr());
{% endif %}
  m_ptr->set_{{relation.name}}(value.ptr());
{%- if relation.peer_relation %}
  value->{{relation.peer_relation.name}}().append(ptr());
{% endif -%}
}
{% endif -%}
{% endfor %}
{% endif -%}
{# #}
{{ data_streamer_impl(class_name, members, member_types) }}

{{ debug_streamer_impl(class_name, members) }}
