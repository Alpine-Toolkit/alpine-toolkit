{# -*- mode: fundamental -*- -#}

{%- from "includes/orm/setter.jinja" import setter_impl -%}
{%- from "includes/cdtor.jinja" import ctor_impl, copy_ctor_impl, copy_operator_impl, dtor_impl -%}
{%- from "includes/data-stream-operator.jinja" import data_streamer_impl -%}
{%- from "includes/debug.jinja" import debug_streamer_impl -%}
{%- from "includes/operator.jinja" import equal_operator_impl -%}

{%- set class_name_schema = schema.schema_cls_name %}
{%- set class_name_ptr = schema.ptr_cls_name %}
{%- set class_name_cache = schema.cache_cls_name %}

{{class_name_schema}}::{{class_name_schema}}()
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

{{ dtor_impl(class_name_schema) }}

/**************************************************************************************************/

{% set base_class = schema.base_class + '<' + class_name_schema + '>' -%}
{%- set base_classes = (base_class,) -%}

{{ ctor_impl(class_name, all_members, base_classes) }}

{{ copy_ctor_impl(class_name, all_members, base_classes) }}

{% include "includes/orm/json-ctor.cpp" %}

{% include "includes/orm/sql-ctor.cpp" %}

{# {{ dtor_impl(class_name) }} #}
{{class_name}}::~{{class_name}}()
{
  qInfo() << "--- Delete" << "{{class_name}}" << *this;
}

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

void
{{class_name}}::set_insert_id(int id)
{
  set_{{schema.rowid_primary_key.name}}(id);

{%- for relation in schema.relations %}
{%- if relation.is_one_to_many %}
  for (const auto & item_weak_ref : m_{{relation.name}})
    item_weak_ref.data()->set_{{relation.peer_relation.foreign_key_name}}(id); // Fixme: check ref
{% endif -%}
{% endfor %}
}

{% if schema.relations %}
{%- if schema.has_foreign_keys %}
bool
{{class_name}}::can_save() const
{
{%- for foreign_key in schema.foreign_keys %}
  if (m_{{foreign_key.name}} == 0)
    return false;
{% endfor %}
  return true;
}
{% endif %}

void
{{class_name}}::load_relations()
{
  qInfo() << "Load relations of" << *this;
{%- for relation in schema.relations %}
{%- if relation.is_many_to_one %}
  {{relation.name}}();
{% endif -%}
{%- if relation.is_one_to_many %}
  {
    // Load one-to-many relation {{relation.name}}
    {{relation.cls_name}}::PtrList rows = database_schema()->query_by_foreign_key<{{relation.cls_name}}>(
      QLatin1String("{{relation.peer_relation.foreign_key_name}}"),
      m_{{relation.peer_relation.foreign_key_related_column}}); // true
    m_{{relation.name}} = rows;
  }
{% endif -%}
{% endfor %}
}

void
{{class_name}}::save_relations()
{
  qInfo() << "Save relations of" << *this;
{%- for relation in schema.relations %}
{%- if relation.is_one_to_many %}
  for (const auto & item_weak_ref : m_{{relation.name}}) {
    {{relation.cls_name}} * item_ptr = item_weak_ref.data();
    if (not item_ptr->exists_on_database())
      database_schema()->add(*item_ptr);
  }
{% endif -%}
{% endfor %}
}
{# #}
{%- for relation in schema.relations %}
{%- if relation.is_many_to_one %}
{{relation.ptr_cls_name}}
{{class_name}}::{{relation.name}}()
{
  if (m_{{relation.name}}.isNull())
    // Fixme: query_by_id must be defined in QcDatabaseSchema but we cannot call register_row
    m_{{relation.name}} = database_schema()->query_by_id<{{relation.cls_name}}>(m_{{relation.foreign_key_name}});
  return m_{{relation.name}};
}
{% endif -%}
{% endfor %}
{% endif -%}

bool
{{class_name}}::can_update() const
{
  {%- if schema.has_rowid_primary_key %}
  return m_{{schema.rowid_primary_key.name}} > 0;
  {# Fixme: else #}
  {% endif %}
}

QVariantHash
{{class_name}}::rowid_kwargs() const // To update row
{
  QVariantHash where_kwargs;
  {# {%- if schema.has_rowid_primary_key %}
  where_kwargs[QLatin1String("{{schema.rowid_primary_key.name}}")] = m_{{schema.rowid_primary_key.name}}; #}
  {% for primary_key in schema.primary_keys %}
  where_kwargs[QLatin1String("{{primary_key.name}}")] = m_{{primary_key.name}};
  {% endfor %}
  return where_kwargs;
}

{{ data_streamer_impl(class_name, members, member_types) }}

{{ debug_streamer_impl(class_name, members) }}

/**************************************************************************************************/

{%- for relation in schema.relations %}
{%- if relation.is_many_to_one %}
void
{{class_name_ptr}}::set_{{relation.name}}({{relation.ptr_cls_name}} & value)
{
{%- if relation.peer_relation %}
  if (m_ptr->m_{{relation.name}})
    m_ptr->m_{{relation.name}}->{{relation.peer_relation.name}}().remove(*this);
{% endif %}
  m_ptr->m_{{relation.name}} = value;
  m_ptr->set_{{relation.foreign_key_name}}(value->id());
{%- if relation.peer_relation %}
  value->{{relation.peer_relation.name}}().append(*this);
{% endif -%}
}
{% endif -%}
{% endfor %}

#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const {{class_name_ptr}} & obj)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.noquote() << QLatin1Literal("{{class_name_ptr}} ->");
  if (obj)
    debug << *obj;
   else
  debug  << QLatin1Literal("NULL");

  return debug;
}
#endif

/**************************************************************************************************/

{{class_name_cache}}::{{class_name_cache}}()
 : m_loaded_instances(),
   m_modified_instances()
{}

{{class_name_cache}}::~{{class_name_cache}}()
{}

void
{{class_name_cache}}::add({{class_name_ptr}} & ptr)
{
  m_loaded_instances.insert(ptr.data(), ptr);
  QObject::connect(ptr.data(), &{{class_name}}::changed,
                   this, &{{class_name_cache}}::on_changed);
}

void
{{class_name_cache}}::remove({{class_name_ptr}} & ptr)
{}

void
{{class_name_cache}}::on_changed()
{
  {{class_name}} * row = qobject_cast<{{class_name}} *>(QObject::sender());
  qInfo() << "On changed" << row;
  {{class_name_ptr}} row_ptr = m_loaded_instances[row];
  if (row_ptr)
    m_modified_instances.insert(row, row_ptr);
}
