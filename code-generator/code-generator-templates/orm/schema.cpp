{# -*- mode: fundamental -*- #}

{#  ################################################################################################
 #
 # This file is part of the Alpine Toolkit software.
 # Copyright (C) 2017 Fabrice Salvaire
 # Contact: http://www.fabrice-salvaire.fr
 # SPDX-License-Identifier: GPL-3.0-only
 #
 ############################################################################################### -#}

{% with class_name = database_schema.name -%}

{{class_name}}::{{class_name}}(QoDatabase & database)
  : QoDatabaseSchema(database),
{% for schema in database_schema %}
    m_{{schema.table_name}}(nullptr),
{% endfor %}
{% for schema in database_schema %}
    m_{{schema.table_name}}_cache(){% if not loop.last %},{% endif %} 
{% endfor %}{# space #}
{
{% for schema in database_schema %}
  m_{{schema.table_name}} = &register_table({{schema.cls_name}}Schema::instance());
{% endfor %}
}

{{class_name}}::~{{class_name}}()
{}

{% for schema in database_schema %}
template<>
void
{{class_name}}::register_row<{{schema.cls_name}}>({{schema.ptr_cls_name}} & row)
{
  qATInfo() << "Register in cache" << row;
  m_{{schema.table_name}}_cache.add(row);
}
{% endfor %}

{%- endwith %}

/**************************************************************************************************/

