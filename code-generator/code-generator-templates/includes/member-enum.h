  enum FieldPosition {
{%- for member in members %}
    {{member.name|upper}}{% if not loop.last %},{% endif %}{% endfor %}
  };