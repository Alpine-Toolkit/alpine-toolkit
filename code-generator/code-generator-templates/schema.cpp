{# -*- mode: fundamental -*- #}

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
