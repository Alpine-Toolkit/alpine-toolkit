{# -*- mode: fundamental -*- -#}

{#  ################################################################################################
 #
 # This file is part of the Alpine Toolkit software.
 # Copyright (C) 2017 Fabrice Salvaire
 # Contact: http://www.fabrice-salvaire.fr
 # SPDX-License-Identifier: GPL-3.0-only
 #
 ############################################################################################### -#}

{% with class_name = database_schema.name %}

class {{class_name}} : public QoDatabaseSchema
{
public:
  {{class_name}}(QoDatabase & database);
  {{class_name}}(const {{class_name}} & other) = delete;
  ~{{class_name}}();

  {{class_name}} & operator=(const {{class_name}} & other) = delete;

{% for schema in database_schema %}
  QoDatabaseTable & {{schema.table_name}}() { return *m_{{schema.table_name}}; }
{% endfor %}

{#
  template<class T> typename T::Ptr query_by_id(int rowid, bool lazy_load = true); {
    typename T::Ptr row = QoDatabaseSchema::query_by_id<T>(rowid, lazy_load);
    register_row<T>(row);
    return row;
  }
-#}

private:
  template<class T> void register_row(typename T::Ptr & row);

private:
{% for schema in database_schema %}
  QoDatabaseTable * m_{{schema.table_name}};
{% endfor %}
{% for schema in database_schema %}
  {{schema.cache_cls_name }} m_{{schema.table_name}}_cache;
{% endfor %}
};

{%- endwith %}{# sapce #}


/**************************************************************************************************/

