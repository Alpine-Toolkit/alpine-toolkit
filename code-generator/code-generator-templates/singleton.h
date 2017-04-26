class {{class_name}}
{
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
