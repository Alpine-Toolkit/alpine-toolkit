// -*- mode: c++ -*-

/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __QC_VECTOR_HXX__
#define __QC_VECTOR_HXX__

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

template <typename T>
QcVector<T>::QcVector()
  : QcVector(0, 0)
{}

template <typename T>
QcVector<T>::QcVector(T x, T y)
  : m_x(x), m_y(y)
{}

template <typename T>
QcVector<T>::QcVector(const QcVector<T> & other)
  : m_x(other.m_x), m_y(other.m_y)
{}

template <typename T>
QcVector<T>::QcVector(const QPoint & other)
  : m_x(other.x()), m_y(other.y())
{}

template <typename T>
QcVector<T>::QcVector(const QPointF & other)
  : m_x(other.x()), m_y(other.y())
{}

template <typename T>
QcVector<T>::QcVector(const QVector2D & other)
  : m_x(other.x()), m_y(other.y())
{}

template <typename T>
QcVector<T>::~QcVector()
{}

template <typename T>
QcVector<T> &
QcVector<T>::operator=(const QcVector<T> & other)
{
  if (this != &other) {
    m_x = other.m_x;
    m_y = other.m_y;
  }

  return *this;
}

template <typename T>
QPointF
QcVector<T>::to_pointf() const
{
  return QPointF(m_x, m_y);
}

template <typename T>
inline T
QcVector<T>::x() const
{
  return m_x;
}

template <typename T>
inline void
QcVector<T>::set_x(T value)
{
  m_x = value;
}

template <typename T>
inline T
QcVector<T>::y() const
{
  return m_y;
}

template <typename T>
inline void QcVector<T>::set_y(T value)
{
  m_y = value;
}

template <typename T>
T &
QcVector<T>::operator[](int i)
{
  if (i == 0)
    return m_x;
  else if (i == 1)
    return m_y;
  else {
    // throw std::invalid_argument("invalid index");
    qQCCritical() << QLatin1String("invalid index");
    return m_x;
  }
}

template <typename T>
T
QcVector<T>::operator[](int i) const
{
  if (i == 0)
    return m_x;
  else if (i == 1)
    return m_y;
  else {
    // throw std::invalid_argument("invalid index");
    qQCCritical() << QLatin1String("invalid index");
    return m_x;
  }
}

template <typename T>
inline T
QcVector<T>::magnitude_square() const
{
  return m_x * m_x + m_y * m_y;
}

template <typename T>
inline T
QcVector<T>::magnitude() const
{
  return sqrt(magnitude_square());
}

template <typename T>
void
QcVector<T>::normalise()
{
  *this /= magnitude();
}

template <typename T>
QcVector<T>
QcVector<T>::normalised() const
{
  return *this / magnitude();
}

template <typename T>
inline bool
QcVector<T>::is_null() const
{
  return m_x == 0 and m_y == 0;
}

template <typename T>
bool
QcVector<T>::operator==(const QcVector<T> & other) const
{
  return (m_x == other.m_x) and (m_y == other.m_y);
}

template <typename T>
inline bool
QcVector<T>::operator!=(const QcVector<T> & other) const
{
  return !operator==(other);
}

template <typename T>
QcVector<T> &
QcVector<T>::operator+=(const QcVector<T> & other)
{
  m_x += other.m_x;
  m_y += other.m_y;
  return *this;
}

template <typename T>
QcVector<T>
operator+(const QcVector<T> & vector1, const QcVector<T> & vector2)
{
  return QcVector<T>(vector1.m_x + vector2.m_x, vector1.m_y + vector2.m_y);
}

template <typename T>
QcVector<T> &
QcVector<T>::operator-=(const QcVector<T> & other) {
  m_x -= other.m_x;
  m_y -= other.m_y;
  return *this;
}

template <typename T>
QcVector<T>
operator-(const QcVector<T> & vector1, const QcVector<T> & vector2)
{
  return QcVector<T>(vector1.m_x - vector2.m_x, vector1.m_y - vector2.m_y);
}

template <typename T>
QcVector<T> &
QcVector<T>::operator*=(T factor)
{
  m_x *= factor;
  m_y *= factor;
  return *this;
}

template <typename T>
QcVector<T>
operator*(const QcVector<T> & vector, T factor)
{
  return QcVector<T>(vector.m_x * factor, vector.m_y * factor);
}

template <typename T>
QcVector<T> &
QcVector<T>::operator/=(T factor)
{
  m_x /= factor;
  m_y /= factor;
  return *this;
}

template <typename T>
QcVector<T>
operator/(const QcVector<T> & vector, T factor)
{
  return QcVector<T>(vector.m_x / factor, vector.m_y / factor);
}

template <typename T>
QcVector<T> &
QcVector<T>::operator*=(const QcVector<T> & other)
{
  m_x *= other.m_x;
  m_y *= other.m_y;
  return *this;
}

template <typename T>
QcVector<T>
operator*(const QcVector<T> & vector1, const QcVector<T> & vector2)
{
  return QcVector<T>(vector1.m_x * vector2.m_x, vector1.m_y * vector2.m_y);
}

template <typename T>
QcVector<T> &
QcVector<T>::operator/=(const QcVector<T> & other)
{
  m_x /= other.m_x;
  m_y /= other.m_y;
  return *this;
}

template <typename T>
QcVector<T>
operator/(const QcVector<T> & vector1, const QcVector<T> & vector2)
{
  return QcVector<T>(vector1.m_x / vector2.m_x, vector1.m_y / vector2.m_y);
}

// Return the orientation in degree
template <typename T>
T
QcVector<T>::orientation() const
{
  /*
   * 2 | 1
   * - + -
   * 4 | 3
   *
   *       | 1    | 2         | 3    | 4         |
   * x     | +    | -         | +    | -         |
   * y     | +    | +         | -    | -         |
   * tan   | +    | -         | -    | +         |
   * atan  | +    | -         | -    | +         |
   * theta | atan | atan + pi | atan | atan - pi |
   */

  if (is_null()) {
    // throw std::invalid_argument("Null Vector");
    qQCCritical() << QLatin1String("Null Vector");
    return 0;
  }

  if (m_x == 0)
    return copysign(90, m_y);
  else if (m_y == 0)
    return m_x >= 0 ? 0 : 180;
  else {
    T _orientation = qRadiansToDegrees(atan(tan()));
    if (m_x < 0) {
      if (m_y > 0)
	_orientation += 180;
      else
	_orientation -= 180;
    }
    return _orientation;
  }
}

// Return a new vector equal to self rotated of angle degree in the counter clockwise direction
template <typename T>
QcVector<T>
QcVector<T>::rotate_counter_clockwise(T angle) const
{
  T radians = qDegreesToRadians(angle);
  T c = cos(radians);
  T s = sin(radians);

  T xp = c * m_x - s * m_y;
  T yp = s * m_x + c * m_y;

  return QcVector<T>(xp, yp);
}

// Return a new vector equal to self rotated of 90 degree in the counter clockwise direction
template <typename T>
QcVector<T>
QcVector<T>::rotate_counter_clockwise_90() const
{
  return QcVector<T>(-m_y, m_x);
}

// Return a new vector equal to  rotated of 90 degree in the clockwise direction
template <typename T>
QcVector<T>
QcVector<T>::rotate_clockwise_90() const {
  return QcVector<T>(m_y, -m_x);
}

// Return a new vector equal to  rotated of 180 degree
// parity
template <typename T>
QcVector<T>
QcVector<T>::rotate_180() const
{
  return QcVector<T> (-m_x, -m_y);
}

template <typename T>
QcVector<T>
QcVector<T>::mirror_x() const
{
  return QcVector<T>(-m_x, m_y);
}

template <typename T>
QcVector<T>
QcVector<T>::mirror_y() const
{
  return QcVector<T>(m_x, -m_y);
}

// Return the tangent
template <typename T>
T
QcVector<T>::tan() const
{
  if (m_x != 0)
    return m_y / m_x;
  else {
    // throw std::invalid_argument("x is null");
    qQCCritical() << QLatin1String("x is null");
    return 0;
  }
}

// Return the inverse tangent
template <typename T>
T
QcVector<T>::inverse_tan() const
{
  if (m_y != 0)
    return m_x / m_y;
  else {
    // throw std::invalid_argument("y is null");
    qQCCritical() << QLatin1String("y is null");
    return 0;
  }
}

// Return the dot product of  with other
template <typename T>
T
QcVector<T>::dot(const QcVector<T> & other) const
{
  return m_x * other.m_x + m_y * other.m_y;
}

// Return the cross product of  with other
template <typename T>
T
QcVector<T>::cross(const QcVector<T> & other) const
{
  return m_x * other.m_y - m_y * other.m_x;
}

// is parallel with other
template <typename T>
bool
QcVector<T>::is_parallel(const QcVector<T> & other) const
{
  // Fixme: round
  return round(cross(other), 7) == 0;
}

// is orthogonal with other
template <typename T>
bool
QcVector<T>::is_orthogonal(const QcVector<T> & other) const
{
  // Fixme: round
  return round(dot(other), 7) == 0;
}

// Return the cosinus of  with direction
template <typename T>
T
QcVector<T>::cos_with(const QcVector<T> & direction) const
{
  T cos = dot(direction) / (direction.magnitude() * magnitude());
  return trignometric_clamp(cos);
}

//  Return the projection of  on direction
template <typename T>
T
QcVector<T>::projection_on(const QcVector<T> & direction) const
{
  return dot(direction) / direction.magnitude();
}

// Return the sinus of  with other
template <typename T>
T
QcVector<T>::sin_with(const QcVector<T> & direction) const
{
  // turn from direction to
  T sin = direction.cross(*this) / (direction.magnitude() * magnitude());
  return trignometric_clamp(sin);
}

// Return the tan of  with other
template <typename T>
T
QcVector<T>::tan_with(const QcVector<T> & direction) const
{
  // Fixme: direction <-> this
  return direction.cross(*this) / direction.dot(*this);
}

// Return the atan of  with other
template <typename T>
T
QcVector<T>::atan_with(const QcVector<T> & direction) const
{
  return atan(tan_with(direction));
}

// Return the deviation of  with other
template <typename T>
T
QcVector<T>::deviation_with(const QcVector<T> & direction) const
{
  return direction.cross(*this) / direction.magnitude();
}

template <typename T>
T
QcVector<T>::radians_with(const QcVector<T> & direction) const
{
  // Fixme: check all cases
  // -> angle_with
  //  Return the angle of on direction

  T angle = acos(cos_with(direction));
  T angle_sign = sign(sin_with(direction));

  return angle_sign * angle;
}

template <typename T>
T
QcVector<T>::orientation_with(const QcVector<T> & direction) const
{
  return qRadiansToDegrees(radians_with(direction));
}

template <typename T>
QcInterval2D<T>
QcVector<T>::to_interval() const
{
  return QcInterval2D<T>(m_x, m_x, m_y, m_y);
}

template <typename T>
QcVector<T>
middle(const QcVector<T> & vector1, const QcVector<T> & vector2)
{
  return (vector1 + vector2) * .5;
}

/**************************************************************************************************/

template <typename T>
QcVector3D<T>::QcVector3D()
  : QcVector3D(0, 0, 0)
{}

template <typename T>
QcVector3D<T>::QcVector3D(T x, T y, T z)
  : QcVector<T>(x, y),
    m_z(z)
{}

template <typename T>
QcVector3D<T>::QcVector3D(const QcVector3D<T> & other)
  : QcVector<T>(other),
    m_z(other.m_z)
{}

template <typename T>
QcVector3D<T>::~QcVector3D()
{}

template <typename T>
QcVector3D<T> &
QcVector3D<T>::operator=(const QcVector3D<T> & other)
{
  if (this != &other) {
    QcVector<T>::operator=(other);
    m_z = other.m_z;
  }

  return *this;
}

template <typename T>
inline T
QcVector3D<T>::z() const
{
  return m_z;
}

template <typename T>
inline void
QcVector3D<T>::set_z(T value)
{
  m_z = value;
}

template <typename T>
T &
QcVector3D<T>::operator[](int i)
{
  if (i == 0)
    return this->x();
  else if (i == 1)
    return this->y();
  else if (i == 2)
    return m_z;
  else {
    // throw std::invalid_argument("invalid index");
    qQCCritical() << QLatin1String("invalid index");
    return m_z;
  }
}

template <typename T>
T
QcVector3D<T>::operator[](int i) const
{
  if (i == 0)
    return this->x();
  else if (i == 1)
    return this->y();
  else if (i == 2)
    return m_z;
  else {
    // throw std::invalid_argument("invalid index");
    qQCCritical() << QLatin1String("invalid index");
    return m_z;
  }
}

template <typename T>
inline T
QcVector3D<T>::magnitude_square() const
{
  return QcVector<T>::magnitude_square() + m_z * m_z;
}

/*
template <typename T>
inline T
QcVector3D<T>::magnitude() const
{
  return sqrt(magnitude_square());
}

template <typename T>
void
QcVector3D<T>::normalise()
{
  *this /= magnitude();
}

template <typename T>
QcVector3D<T>
QcVector3D<T>::normalised() const
{
  return *this / magnitude();
}
*/

template <typename T>
inline bool
QcVector3D<T>::is_null() const
{
  return QcVector<T>::is_null() and m_z == 0;
}

template <typename T>
bool
QcVector3D<T>::operator==(const QcVector3D<T> & other) const
{
  return QcVector<T>::operator==(other) and (m_z == other.m_z);
}

/*
template <typename T>
inline bool
QcVector3D<T>::operator!=(const QcVector3D<T> & other) const
{
  return !operator==(other);
}
*/

template <typename T>
QcVector3D<T> &
QcVector3D<T>::operator+=(const QcVector3D<T> & other)
{
  QcVector<T>::operator+(other);
  m_z += other.m_z;
  return *this;
}

template <typename T>
QcVector3D<T>
operator+(const QcVector3D<T> & vector1, const QcVector3D<T> & vector2)
{
  return QcVector3D<T>(vector1.x() + vector2.x(),
                       vector1.y() + vector2.y(),
                       vector1.m_z + vector2.m_z);
}

template <typename T>
QcVector3D<T> &
QcVector3D<T>::operator-=(const QcVector3D<T> & other) {
  QcVector<T>::operator-=(other);
  m_z -= other.m_z;
  return *this;
}

template <typename T>
QcVector3D<T>
operator-(const QcVector3D<T> & vector1, const QcVector3D<T> & vector2)
{
  return QcVector3D<T>(vector1.x() - vector2.x(),
                       vector1.y() - vector2.y(),
                       vector1.m_z - vector2.m_z
                       );
}

template <typename T>
QcVector3D<T> &
QcVector3D<T>::operator*=(T factor)
{
  QcVector<T>::operator*=(factor);
  m_z *= factor;
  return *this;
}

template <typename T>
QcVector3D<T>
operator*(const QcVector3D<T> & vector, T factor)
{
  return QcVector3D<T>(vector.x() * factor,
                       vector.y() * factor,
                       vector.m_z * factor);
}

template <typename T>
QcVector3D<T> &
QcVector3D<T>::operator/=(T factor)
{
  QcVector<T>::operator/=(factor);
  m_z /= factor;
  return *this;
}

template <typename T>
QcVector3D<T>
operator/(const QcVector3D<T> & vector, T factor)
{
  return QcVector3D<T>(vector.x() / factor,
                       vector.y() / factor,
                       vector.m_z / factor
                       );
}

/*
// Return the orientation in degree
template <typename T>
T
QcVector3D<T>::orientation() const
{
}

// Return a new vector equal to self rotated of angle degree in the counter clockwise direction
template <typename T>
QcVector3D<T>
QcVector3D<T>::rotate_counter_clockwise(T angle) const
{
}

// Return a new vector equal to self rotated of 90 degree in the counter clockwise direction
template <typename T>
QcVector3D<T>
QcVector3D<T>::rotate_counter_clockwise_90() const
{
  return QcVector3D<T>(-m_y, m_x);
}

// Return a new vector equal to  rotated of 90 degree in the clockwise direction
template <typename T>
QcVector3D<T>
QcVector3D<T>::rotate_clockwise_90() const {
  return QcVector3D<T>(m_y, -m_x);
}

// Return a new vector equal to  rotated of 180 degree
// parity
template <typename T>
QcVector3D<T>
QcVector3D<T>::rotate_180() const
{
  return QcVector3D<T> (-this->x(), -this->y(), -m_z);
}

template <typename T>
QcVector3D<T>
QcVector3D<T>::mirror_x() const
{
  return QcVector3D<T>(-m_x, m_y, m_z);
}

template <typename T>
QcVector3D<T>
QcVector3D<T>::mirror_y() const
{
  return QcVector3D<T>(m_x, -m_y, m_z);
}
*/

/*
// Return the tangent
template <typename T>
T
QcVector3D<T>::tan() const
{
  if (m_x != 0)
    return m_y / m_x;
  else
    // throw std::invalid_argument("x is null");
}

// Return the inverse tangent
template <typename T>
T
QcVector3D<T>::inverse_tan() const
{
  if (m_y != 0)
    return m_x / m_y;
  else
    // throw std::invalid_argument("y is null");
}
*/

// Return the dot product of  with other
template <typename T>
T
QcVector3D<T>::dot(const QcVector3D<T> & other) const
{
  return QcVector<T>::dot(other) + m_z * other.m_z;
}

// Return the cross product of  with other
template <typename T>
QcVector3D<T>
QcVector3D<T>::cross(const QcVector3D<T> & other) const
{
  T x = this->x();
  T y = this->y();
  return QcVector3D<T>(y   * other.m_z - m_z * other.y(),
                       m_z * other.x() - x   * other.m_z,
                       x   * other.y() - y   * other.x()
                       );
}

/*
// is parallel with other
template <typename T>
bool
QcVector3D<T>::is_parallel(const QcVector3D<T> & other) const
{
  // Fixme: round
  return round(cross(other), 7) == 0;
}

// is orthogonal with other
template <typename T>
bool
QcVector3D<T>::is_orthogonal(const QcVector3D<T> & other) const
{
  // Fixme: round
  return round(dot(other), 7) == 0;
}
*/

/*
// Return the cosinus of  with direction
template <typename T>
T
QcVector3D<T>::cos_with(const QcVector3D<T> & direction) const
{
  T cos = dot(direction) / (direction.magnitude() * magnitude());
  return trignometric_clamp(cos);
}

//  Return the projection of  on direction
template <typename T>
T
QcVector3D<T>::projection_on(const QcVector3D<T> & direction) const
{
  return dot(direction) / direction.magnitude();
}

// Return the sinus of  with other
template <typename T>
T
QcVector3D<T>::sin_with(const QcVector3D<T> & direction) const
{
  // turn from direction to
  T sin = direction.cross(*this) / (direction.magnitude() * magnitude());
  return trignometric_clamp(sin);
}

// Return the tan of  with other
template <typename T>
T
QcVector3D<T>::tan_with(const QcVector3D<T> & direction) const
{
  // Fixme: direction <-> this
  return direction.cross(*this) / direction.dot(*this);
}

// Return the atan of  with other
template <typename T>
T
QcVector3D<T>::atan_with(const QcVector3D<T> & direction) const
{
  return atan(tan_with(direction));
}

// Return the deviation of  with other
template <typename T>
T
QcVector3D<T>::deviation_with(const QcVector3D<T> & direction) const
{
  return direction.cross(*this) / direction.magnitude();
}

template <typename T>
T
QcVector3D<T>::radians_with(const QcVector3D<T> & direction) const
{
  // Fixme: check all cases
  // -> angle_with
  //  Return the angle of on direction

  T angle = acos(cos_with(direction));
  T angle_sign = sign(sin_with(direction));

  return angle_sign * angle;
}

template <typename T>
T
QcVector3D<T>::orientation_with(const QcVector3D<T> & direction) const
{
  return qRadiansToDegrees(radians_with(direction));
}
*/

template <typename T>
QcInterval3D<T>
QcVector3D<T>::to_interval() const
{
  T x = this->x();
  T y = this->y();
  return QcInterval3D<T>(x, x, y, y, m_z, m_z);
}

/**************************************************************************************************/

template <typename T>
QcVector4D<T>::QcVector4D()
  : QcVector4D(0, 0, 0, 0)
{}

template <typename T>
QcVector4D<T>::QcVector4D(T x, T y, T z, T t)
  : QcVector3D<T>(x, y, z),
    m_t(t)
{}

template <typename T>
QcVector4D<T>::QcVector4D(const QcVector4D<T> & other)
  : QcVector3D<T>(other),
    m_t(other.m_t)
{}

template <typename T>
QcVector4D<T>::~QcVector4D()
{}

template <typename T>
QcVector4D<T> &
QcVector4D<T>::operator=(const QcVector4D<T> & other)
{
  if (this != &other) {
    QcVector3D<T>::operator=(other);
    m_t = other.m_t;
  }

  return *this;
}

template <typename T>
inline T
QcVector4D<T>::t() const
{
  return m_t;
}

template <typename T>
inline void
QcVector4D<T>::set_t(T value)
{
  m_t = value;
}

template <typename T>
T &
QcVector4D<T>::operator[](int i)
{
  if (i == 0)
    return this->x();
  else if (i == 1)
    return this->y();
  else if (i == 2)
    return this->z();
  else if (i == 3)
    return m_t;
  else {
    // throw std::invalid_argument("invalid index");
    qQCCritical() << QLatin1String("invalid index");
    return m_t;
  }
}

template <typename T>
T
QcVector4D<T>::operator[](int i) const
{
  if (i == 0)
    return this->x();
  else if (i == 1)
    return this->y();
  else if (i == 2)
    return this->z();
  else if (i == 3)
    return m_t;
  else {
    // throw std::invalid_argument("invalid index");
    qQCCritical() << QLatin1String("invalid index");
    return m_t;
  }
}

template <typename T>
inline bool
QcVector4D<T>::is_null() const
{
  return QcVector3D<T>::is_null() and m_t == 0;
}

template <typename T>
bool
QcVector4D<T>::operator==(const QcVector4D<T> & other) const
{
  return QcVector3D<T>::operator==(other) and (m_t == other.m_t);
}

/*
template <typename T>
inline bool
QcVector4D<T>::operator!=(const QcVector4D<T> & other) const
{
  return !operator==(other);
}
*/

template <typename T>
QcVector4D<T> &
QcVector4D<T>::operator+=(const QcVector4D<T> & other)
{
  QcVector3D<T>::operator+(other);
  m_t += other.m_t;
  return *this;
}

template <typename T>
QcVector4D<T>
operator+(const QcVector4D<T> & vector1, const QcVector4D<T> & vector2)
{
  return QcVector4D<T>(vector1.x() + vector2.x(),
                       vector1.y() + vector2.y(),
                       vector1.z() + vector2.z(),
                       vector1.m_t + vector2.m_t);
}

template <typename T>
QcVector4D<T> &
QcVector4D<T>::operator-=(const QcVector4D<T> & other) {
  QcVector3D<T>::operator-=(other);
  m_t -= other.m_t;
  return *this;
}

template <typename T>
QcVector4D<T>
operator-(const QcVector4D<T> & vector1, const QcVector4D<T> & vector2)
{
  return QcVector4D<T>(vector1.x() - vector2.x(),
                       vector1.y() - vector2.y(),
                       vector1.z() - vector2.z(),
                       vector1.m_t - vector2.m_t
                       );
}

template <typename T>
QcVector4D<T> &
QcVector4D<T>::operator*=(T factor)
{
  QcVector3D<T>::operator*=(factor);
  m_t *= factor;
  return *this;
}

template <typename T>
QcVector4D<T>
operator*(const QcVector4D<T> & vector, T factor)
{
  return QcVector4D<T>(vector.x() * factor,
                       vector.y() * factor,
                       vector.z() * factor,
                       vector.m_t * factor);
}

template <typename T>
QcVector4D<T> &
QcVector4D<T>::operator/=(T factor)
{
  QcVector3D<T>::operator/=(factor);
  m_t /= factor;
  return *this;
}

template <typename T>
QcVector4D<T>
operator/(const QcVector4D<T> & vector, T factor)
{
  return QcVector4D<T>(vector.x() / factor,
                       vector.y() / factor,
                       vector.z() / factor,
                       vector.m_t / factor
                       );
}

/**************************************************************************************************/

#endif /* __QC_VECTOR_HXX__ */
