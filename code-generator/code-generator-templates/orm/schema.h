{# -*- mode: fundamental -*- -#}

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

