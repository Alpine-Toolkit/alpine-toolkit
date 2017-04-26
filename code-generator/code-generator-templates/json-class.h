{%- with class_name = class_name + 'Schema' %}
{% include "singleton.h" %}
{%- endwith %}

/**************************************************************************************************/

class {{class_name}} : public QObject
{
  Q_OBJECT
{%- for member in members %}
  Q_PROPERTY(QString {{member.name}} READ {{member.name}} WRITE set_{{member.name}} NOTIFY {{member.name}}Changed){% endfor %}

public:
  enum FieldPosition {
{%- for member in members %}
    {{member.name|upper}}{% if not loop.last %},{% endif %}{% endfor %}
  };

public:
  {{class_name}}();
  {{class_name}}(const {{class_name}} & other);
  {{class_name}}(const QJsonObject & json_object);
  ~{{class_name}}();

  {{class_name}} & operator=(const {{class_name}} & other);

{%- for member in members %}
  const QString & {{member.name}}() const { return m_{{member.name}}; }
  void set_{{member.name}}(const QString & value);
{% endfor %}
  QJsonObject to_json(bool only_changed = False) const;

signals:
{%- for member in members %}
  void {{member.name}}Changed();{% endfor %}

private:
  QBitArray m_bits;
{%- for member in members %}
  QString m_{{member.name}};{% endfor %}
};

{% include "data-stream-operator.h" %}

{% include "debug.h" %}
