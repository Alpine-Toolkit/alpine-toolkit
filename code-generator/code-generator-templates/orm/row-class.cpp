{# -*- mode: fundamental -*- -#}

{#  ################################################################################################
 #
 # $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 #
 # Copyright (C) 2017 Fabrice Salvaire
 # Contact: http://www.fabrice-salvaire.fr
 #
 # This file is part of the QtCarto library.
 #
 # This program is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with this program.  If not, see <http://www.gnu.org/licenses/>.
 #
 # $ALPINE_TOOLKIT_END_LICENSE$
 #
 ############################################################################################### -#}

{% from "includes/cdtor.jinja" import ctor_impl, copy_ctor_impl, copy_operator_impl, dtor_impl %}
{% from "includes/data-stream-operator.jinja" import data_streamer_impl %}
{% from "includes/debug.jinja" import debug_streamer_impl %}
{% from "includes/operator.jinja" import equal_operator_impl -%}
{% from "orm/includes/field-accessor.jinja" import get_field, set_field %}
{% from "orm/includes/json-ctor.jinja" import json_ctor, variant_hash_ctor, variant_list_ctor %}
{% from "orm/includes/json-serializer.jinja" import to_json %}
{% from "orm/includes/setter.jinja" import setter_impl %}
{% from "orm/includes/sql-ctor.jinja" import sql_ctor %}

{% set class_name = schema.cls_name %}
{% set class_name_schema = schema.schema_cls_name %}
{% set class_name_ptr = schema.ptr_cls_name %}
{% set class_name_cache = schema.cache_cls_name %}
{% set class_name_model = schema.model_cls_name %}
{% set members = schema.members %}
{% set all_members = schema.all_members %}
{% set member_types = schema.member_types %}
{% if schema.has_post_init %}
{% set post_init = 'post_init' %}
{% endif %}

{{class_name_schema}}::{{class_name_schema}}()
: QcSchema(QLatin1String("{{class_name}}"), QLatin1String("{{schema.table_name}}"))
{
{% for field in schema %}
  {
    {{field.shema_field_ctor}} field(
      QLatin1String("{{field.name}}"),
{% if field.is_foreign_key %}
      QLatin1String("{{field.foreign_key.dot_syntax}}"),
{% endif %}
      QLatin1String("{{field.qt_type}}"),
      QLatin1String("{{field.sql_type}}"),
      QLatin1String("{{field.sql_name}}"),
      QLatin1String("{{field.json_name}}"),
      QLatin1String("{{field.title}}"),
      QLatin1String("{{field.description}}"));
    // Optional parameters
{% if field.autoincrement %}
    field.set_autoincrement(true);
{% endif %}
{% if not field.nullable %}
    field.set_nullable(false);
{% endif %}
{% if field.unique %}
    field.set_unique(true);
{% endif %}
{% if field.default %}
    field.set_default_value({{field.default}});
{% endif %}
    add_field(field);
  }
{% endfor %}
}

{{ dtor_impl(class_name_schema) }}

/**************************************************************************************************/

{% set base_class = schema.base_class + '<' + class_name_schema + '>' %}
{% set base_classes = (base_class,) %}{# Fixme: !!! #}

{{ ctor_impl(class_name, all_members, base_classes, post_init) }}

{{ copy_ctor_impl(class_name, all_members, base_classes, post_init) }}

{{ json_ctor(class_name, schema, post_init) }}

{{ variant_hash_ctor(class_name, schema, post_init) }}

{{ variant_list_ctor(class_name, schema, post_init) }}

{{ sql_ctor(class_name, base_class, schema, post_init) }}

{# {{ dtor_impl(class_name) }} #}
{{class_name}}::~{{class_name}}()
{
// qInfo() << "--- Delete" << "{{class_name}}" << *this;
}

// bit array ?
{{ copy_operator_impl(class_name, all_members, base_classes, post_init) }}

// bit array ?
{{ equal_operator_impl(class_name, members, base_classes) }}

{% for member in members %}
{{ setter_impl(class_name, member) }}
{% endfor %}

{{ to_json(class_name, schema) }}

{% include "orm/includes/variant-serializer.cpp" %}

{{ get_field(class_name, schema) }}

{{ set_field(class_name, schema) }}

void
{{class_name}}::set_insert_id(int id)
{
  set_{{schema.rowid_primary_key.name}}(id);

{% for relation in schema.relations %}{# space #}
{% if relation.is_one_to_many %}
  for (const auto & item_weak_ref : m_{{relation.name}})
    item_weak_ref.data()->set_{{relation.peer_relation.foreign_key_name}}(id); // Fixme: check ref
{% endif %}
{% endfor %}
}

{% if schema.relations -%}

{% if schema.has_foreign_keys %}
bool
{{class_name}}::can_save() const
{
{% for foreign_key in schema.foreign_keys %}
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
{% for relation in schema.relations %}
{% if relation.is_many_to_one %}
  {{relation.name}}();
{% endif -%}

{% if relation.is_one_to_many %}
  {
    // Load one-to-many relation {{relation.name}}
    {{relation.cls_name}}::PtrList rows = database_schema()->query_by_foreign_key<{{relation.cls_name}}>(
      QLatin1String("{{relation.peer_relation.foreign_key_name}}"),
      m_{{relation.peer_relation.foreign_key_related_column}}); // true
    m_{{relation.name}} = rows;
  }
{% endif %}
{% endfor %}
}

void
{{class_name}}::save_relations()
{
  qInfo() << "Save relations of" << *this;
{% for relation in schema.relations %}
{% if relation.is_one_to_many %}
  for (const auto & item_weak_ref : m_{{relation.name}}) {
    {{relation.cls_name}} * item_ptr = item_weak_ref.data();
    if (not item_ptr->exists_on_database())
      database_schema()->add(*item_ptr);
  }
{% endif %}
{% endfor %}
}

{% for relation in schema.relations %}
{% if relation.is_many_to_one %}
{{relation.ptr_cls_name}}
{{class_name}}::{{relation.name}}()
{
  if (m_{{relation.name}}.isNull())
    // Fixme: query_by_id must be defined in QcDatabaseSchema but we cannot call register_row
    m_{{relation.name}} = database_schema()->query_by_id<{{relation.cls_name}}>(m_{{relation.foreign_key_name}});
  return m_{{relation.name}};
}
{% endif %}
{% endfor -%}

{% endif %}

bool
{{class_name}}::can_update() const
{
{% if schema.has_rowid_primary_key %}
  return m_{{schema.rowid_primary_key.name}} > 0;
  {# Fixme: else #}
{% endif %}
}

QVariantHash
{{class_name}}::rowid_kwargs() const // To update row
{
  QVariantHash where_kwargs;
  {# {% if schema.has_rowid_primary_key %}
  where_kwargs[QLatin1String("{{schema.rowid_primary_key.name}}")] = m_{{schema.rowid_primary_key.name}}; #}
{% for primary_key in schema.primary_keys %}
  where_kwargs[QLatin1String("{{primary_key.name}}")] = m_{{primary_key.name}};
{% endfor %}
  return where_kwargs;
}

{{ data_streamer_impl(class_name, members, member_types) }}

{{ debug_streamer_impl(class_name, members) }}

/**************************************************************************************************/

{% for relation in schema.relations %}
{% if relation.is_many_to_one %}
void
{{class_name_ptr}}::set_{{relation.name}}({{relation.ptr_cls_name}} & value)
{
{% if relation.peer_relation %}
  if (m_ptr->m_{{relation.name}})
    m_ptr->m_{{relation.name}}->{{relation.peer_relation.name}}().remove(*this);
{% endif %}
  m_ptr->m_{{relation.name}} = value;
  m_ptr->set_{{relation.foreign_key_name}}(value->id());
{% if relation.peer_relation %}
  value->{{relation.peer_relation.name}}().append(*this);
{% endif %}
}
{% endif %}
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

/**************************************************************************************************/

{{class_name_model}}::{{class_name_model}}()
  : QAbstractListModel(),
    m_items()
{}

{{class_name_model}}::{{class_name_model}}(const ItemList & items)
  : QAbstractListModel(),
    m_items(items)
{}

{{class_name_model}}::~{{class_name_model}}()
{}

int
{{class_name_model}}::rowCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);
  return m_items.size();
}

QVariant
{{class_name_model}}::data(const QModelIndex & index, int role) const
{
  if (!index.isValid() || index.row() < 0)
    return QVariant();

  if (index.row() >= m_items.count()) {
    qWarning() << "{{class_name_model}}: Index out of bound";
    return QVariant();
  }

  const Item & item = m_items[index.row()];
{% macro _value(member) -%}
item->{{member.name}}()
{%- endmacro %}
  switch (role) {
{% for member in members + schema.computed_members %}
  case {{member.name|upper}}:
    return {% if member.cast_variant -%}
QVariant::fromValue({{ _value(member) }})
{%- else -%}
{{ _value(member) }}
{%- endif %};
{% endfor %}
  default:
    break;
  }

  return QVariant();
}

QHash<int, QByteArray>
{{class_name_model}}::roleNames() const
{
  // Fixme: cache ???
  QHash<int, QByteArray> role_names;{# = {
{% for member in members + schema.computed_members %}
  {{member.name|upper}}, QLatin1Literal("{{member.name}}").latin1(){% if not loop.last %},{% endif %} 
{% endfor %}
  };#}

{% for member in members + schema.computed_members %}
  role_names[{{member.name|upper}}] = QLatin1Literal("{{member.name}}").latin1();
{% endfor %}

  return role_names;
}

void
{{class_name_model}}::clear_items()
{
  beginResetModel();
  m_items.clear();
  endResetModel();
}

void
{{class_name_model}}::set_items(const ItemList & items)
{
  beginResetModel();
  m_items = items;
  endResetModel();
}
