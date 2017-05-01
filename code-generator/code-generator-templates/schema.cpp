{# -*- mode: fundamental -*- -#}

{%- with class_name = database_schema.name %}
{{class_name}}::{{class_name}}(QcDatabase & database)
  : QcDatabaseSchema(database),
{%- for schema in database_schema %}
    m_{{schema.table_name}}(nullptr){% if not loop.last %},{% endif %}{% endfor %}
{
{%- for schema in database_schema %}
  m_{{schema.table_name}} = &register_table({{schema.cls_name}}Schema::instance());{% endfor %}
}

{{class_name}}::~{{class_name}}()
{}
{%- endwith %}
