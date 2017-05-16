{# -*- mode: fundamental -*- #}

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

{% with class_name = database_schema.name -%}

{{class_name}}::{{class_name}}(QcDatabase & database)
  : QcDatabaseSchema(database),
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
  qInfo() << "Register in cache" << row;
  m_{{schema.table_name}}_cache.add(row);
}
{% endfor %}

{%- endwith %}

/**************************************************************************************************/

