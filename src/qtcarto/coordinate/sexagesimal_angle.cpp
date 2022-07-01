/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "sexagesimal_angle.h"
#include "qtcarto.h"

#include <cmath>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

double
QcGeoSexagesimalAngle::to_decimal(int degrees, int minutes, double seconds)
{
  return degrees + (minutes + seconds / 60.) / 60.;
}

void
QcGeoSexagesimalAngle::to_sexagesimal(double angle, int & degrees, int & minutes, double & seconds)
{
  double _degrees, _minutes, f;
  f = modf(angle, &_degrees);
  f = modf(f * 60, &_minutes);
  seconds = f * 60;

  degrees = int(_degrees);
  minutes = int(_minutes);
}

QcGeoSexagesimalAngle::QcGeoSexagesimalAngle(double degrees)
  : m_degrees(0), m_minutes(0), m_seconds(qQNaN())
{
  to_sexagesimal(degrees, m_degrees, m_minutes, m_seconds);
}

QcGeoSexagesimalAngle::QcGeoSexagesimalAngle(int degrees, int minutes, double seconds)
  : m_degrees(0), m_minutes(0), m_seconds(qQNaN())
{
  if (is_valid_degrees(degrees) and is_valid_minutes(minutes)) {
    m_degrees = degrees;
    m_minutes = minutes;
    m_seconds = seconds;
  }
}

QcGeoSexagesimalAngle::QcGeoSexagesimalAngle(const QcGeoSexagesimalAngle & other)
  : m_degrees(other.m_degrees), m_minutes(other.m_minutes), m_seconds(other.m_seconds)
{}

QcGeoSexagesimalAngle::~QcGeoSexagesimalAngle()
{}

// Fixme: default
QcGeoSexagesimalAngle &
QcGeoSexagesimalAngle::operator=(const QcGeoSexagesimalAngle & other)
{
  if (this != &other) {
    m_degrees = other.m_degrees;
    m_minutes = other.m_minutes;
    m_seconds = other.m_seconds;
  }

  return *this;
}

bool
QcGeoSexagesimalAngle::operator==(const QcGeoSexagesimalAngle & other) const
{
  bool degrees_equal = m_minutes == other.m_degrees;
  bool minutes_equal = m_minutes == other.m_minutes;
  bool seconds_equal = qFuzzyCompare(m_seconds, other.m_seconds);

  return (degrees_equal and minutes_equal and seconds_equal);
}

void
QcGeoSexagesimalAngle::set_degrees(double degrees)
{
  to_sexagesimal(degrees, m_degrees, m_minutes, m_seconds);
}

double
QcGeoSexagesimalAngle::decimal() const {
  return to_decimal(m_degrees, m_minutes, m_seconds);
}

/**************************************************************************************************/

// QC_END_NAMESPACE
