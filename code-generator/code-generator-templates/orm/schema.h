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

{% with class_name = database_schema.name %}

class {{class_name}} : public QcDatabaseSchema
{
public:
  {{class_name}}(QcDatabase & database);
  {{class_name}}(const {{class_name}} & other) = delete;
  ~{{class_name}}();

  {{class_name}} & operator=(const {{class_name}} & other) = delete;

{% for schema in database_schema %}
  QcDatabaseTable & {{schema.table_name}}() { return *m_{{schema.table_name}}; }
{% endfor %}

{#
  template<class T> typename T::Ptr query_by_id(int rowid, bool lazy_load = true); {
    typename T::Ptr row = QcDatabaseSchema::query_by_id<T>(rowid, lazy_load);
    register_row<T>(row);
    return row;
  }
-#}

private:
  template<class T> void register_row(typename T::Ptr & row);

private:
{% for schema in database_schema %}
  QcDatabaseTable * m_{{schema.table_name}};
{% endfor %}
{% for schema in database_schema %}
  {{schema.cache_cls_name }} m_{{schema.table_name}}_cache;
{% endfor %}
};

{%- endwith %}{# sapce #}


/**************************************************************************************************/

