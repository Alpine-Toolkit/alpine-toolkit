{# -*- mode: fundamental -*- -#}
{%- with class_name = class_name + 'Schema' %}
{#- {% include "includes/singleton.h" %} -#}
class {{class_name}} : public QcSchema
{
public:
  enum Fields {
{%- for member in members %}
    {{member.name|upper}}{% if not loop.last %},{% endif %}{% endfor %}
  };

public:
  static {{class_name}} & instance()
  {
    static {{class_name}} m_instance;
    return m_instance;
  }

  // delete copy and move constructors and assign operators
  {{class_name}}(const {{class_name}} &) = delete;              // Copy constructor
  {{class_name}}({{class_name}} &&) = delete;                   // Move constructor
  {{class_name}} & operator=(const {{class_name}} &) = delete;  // Copy assign
  {{class_name}} & operator=({{class_name}} &&) = delete;       // Move assign

protected:
  {{class_name}}();
  ~{{class_name}}();
};
{%- endwith %}

/**************************************************************************************************/

class {{class_name}} : public QObject
{
  Q_OBJECT
{%- for member in members %}
  Q_PROPERTY({{member.type}} {{member.name}} READ {{member.name}} WRITE set_{{member.name}} NOTIFY {{member.name}}Changed){% endfor %}

public:
  static {{class_name}}Schema & schema() { return {{class_name}}Schema::instance(); }

public:
  {{class_name}}();
  {{class_name}}(const {{class_name}} & other);
  {{class_name}}(const QJsonObject & json_object);
  {{class_name}}(const QVariantHash & variant_hash);
  {{class_name}}(const QVariantList & variants);
  {{class_name}}(const QSqlRecord & record);
  {{class_name}}(const QSqlQuery & query);
  ~{{class_name}}();

  {{class_name}} & operator=(const {{class_name}} & other);

  bool operator==(const {{class_name}} & other);
{% for member in members %}
  {{member.getter_type}} {{member.name}}() const { return m_{{member.name}}; }
  void set_{{member.name}}({{member.setter_type}} value);
{% endfor %}
QJsonObject to_json(bool only_changed = false) const;
  QVariantHash to_variant_hash(bool only_changed = false) const;
  QVariantHash to_variant_hash_sql(bool only_changed = false) const;
  QVariantHash to_variant_hash_json(bool only_changed = false) const;
  QVariantList to_variant_list() const;
{% for member in members %}
  bool is_{{member.name}}_modified() const { return m_bits[{{class_name}}Schema::Fields::{{member.name|upper}}]; }{% endfor %}

  QVariant field(int position) const;
  void set_field(int position, const QVariant & value);

signals:
{%- for member in members %}
  void {{member.name}}Changed();{% endfor %}

private:
  QBitArray m_bits;
{%- for member in members %}
  {{member.type}} m_{{member.name}};{% endfor %}
};

{% include "includes/data-stream-operator.h" %}

{% include "includes/debug.h" %}
