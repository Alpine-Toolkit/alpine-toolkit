// -*- mode: c++ -*-

/**************************************************************************************************/

#include <QObject>

#include "a.h"
#include "b.h"

#include "c.h"
#include "d.h"

/**************************************************************************************************/

#define FOO true

/**************************************************************************************************/

#ifdef FOO
const int a = 1;
#else
const int b = 1;
#endif

/**************************************************************************************************/

namespace foo {

struct Struct1 {
  int member1;
  int member12;
};

class Foo : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int param1 READ param1);

public:
  Foo();
  Foo(int param1, int param2);
  Foo(int param1, int param2, int param3, int param4, int param5, int param6);
  Foo(int param1, int param2, int param3)
    : QObject(),
      m_param1(param1),
      m_param2(param2),
      m_param3(param3)
  {}
  ~Foo();

  int param1() const {}
  int param1(int param1) { m_param1 = param1; }
  int param1() const { return m_param1; }

  int param1() const
  {
    return m_param1;
  }

  int method1(int param1, int param2);

  enum Enum {
    Enum1,
    Enum2,
  };

  enum Enum {
    Enum1,
    Enum2,
    Enum3,
    Enum4,
    Enum5,
    Enum6,
  };

private:
  int m_param1;
  int m_param2;
  int m_param3;
};

Foo::Foo(int param1, int param2, int param3, int param4, int param5, int param6)
{
  m_param1 = param1;
}

int
Foo::method1(int param1, int param2)
  : m_param1(param1),
    m_param2(param2)
{
  m_param1 = param1;
}

int
Foo::method1(int param1, int param2)
{}

} // namespace foo

/**************************************************************************************************/
