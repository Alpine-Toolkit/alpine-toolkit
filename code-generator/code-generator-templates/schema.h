{# -*- mode: fundamental -*- -#}

{%- with class_name = database_schema.name %}
class {{class_name}} : public QcDatabaseSchema
{
public:
  {{class_name}}(QcDatabase & database);
  {{class_name}}(const {{class_name}} & other) = delete;
  ~{{class_name}}();

  {{class_name}} & operator=(const {{class_name}} & other) = delete;
{# #}
{%- for schema in database_schema %}
  QcDatabaseTable & {{schema.table_name}}() { return *m_{{schema.table_name}}; }{% endfor %}

private:
{%- for schema in database_schema %}
  QcDatabaseTable * m_{{schema.table_name}};{% endfor %}
};
{%- endwith %}
