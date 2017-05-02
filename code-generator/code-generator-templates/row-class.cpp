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
    QcSchemaField field(QLatin1String("{{field.name}}"),
                        QLatin1String("{{field.qt_type}}"),
                        QLatin1String("{{field.sql_type}}"),
                        QLatin1String("{{field.sql_name}}"),
                        QLatin1String("{{field.json_name}}"),
                        QLatin1String("{{field.title}}"),
                        QLatin1String("{{field.description}}"));
    // Optional parameters
    {% if field.primary_key %}field.set_primary_key(true);{% endif %}
    {% if field.autoincrement %}field.set_autoincrement(true);{% endif %}
    {% if not field.nullable %}field.set_nullable(false);{% endif %}
    {% if field.unique %}field.set_unique(true);{% endif %}
    {% if field.default %}field.set_default_value({{field.default}});{% endif %}
    add_field(field);
  }{% endfor %}
}

{{ dtor_impl(class_name + "Schema") }}

/**************************************************************************************************/

{% set base_class = "QcRowWithId<" + class_name + "Schema>" -%}
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

{{ data_streamer_impl(class_name, members, member_types) }}

{{ debug_streamer_impl(class_name, members) }}
