// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __QC_SEXAGESIMAL_ANGLE_H__
#define __QC_SEXAGESIMAL_ANGLE_H__

/**************************************************************************************************/

#include "qtcarto_global.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QC_EXPORT QcGeoSexagesimalAngle
{
 public:
  static double to_decimal(int degrees, int minutes=0, double seconds=0);
  static void to_sexagesimal(double angle, int & degrees, int & minutes, double & seconds);

  inline static bool is_valid_degrees(int degrees) {
    // Fixme: -0 sign, 360 ? modulo ?
    return -360 <= degrees && degrees <= 360;
  }

  inline static bool is_valid_minutes(int degrees) {
    return 0 <= degrees && degrees <= 60;
  }

 public:
  QcGeoSexagesimalAngle(int degrees, int minutes=0, double seconds=0);
  QcGeoSexagesimalAngle(double degrees);
  QcGeoSexagesimalAngle(const QcGeoSexagesimalAngle & other);
  ~QcGeoSexagesimalAngle();

  QcGeoSexagesimalAngle & operator=(const QcGeoSexagesimalAngle & other);

  bool operator==(const QcGeoSexagesimalAngle & other) const;
  inline bool operator!=(const QcGeoSexagesimalAngle & other) const {
    return !operator==(other);
  }

  inline int degrees() const { return m_degrees; }
  inline void set_degrees(int degrees) {
    if (is_valid_degrees(degrees))
      m_degrees = degrees;
  }
  void set_degrees(double degrees);

  inline int minutes() const { return m_degrees; }
  inline void set_minutes(int minutes) {
    if (is_valid_minutes(minutes))
      m_minutes = minutes;
  }

  inline double seconds() const { return m_degrees; }
  inline void set_seconds(double seconds) { m_seconds = seconds; }

  double decimal() const;

 private:
  int m_degrees;
  int m_minutes; // Fixme: unsigned
  double m_seconds;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_SEXAGESIMAL_ANGLE_H__ */
