/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#include "qml_barimeter_altimeter_sensor.h"
#include "alpine_toolkit.h"

#include <QtDebug>
#include <QtGlobal>
#include <QtMath>
#include <QtSensors/QPressureSensor>

/**************************************************************************************************/

QmlBarometerAltimeterSensor::QmlBarometerAltimeterSensor(QObject *parent)
  : QTQmlSensor(parent),
    m_sensor(new QPressureSensor(this))
{}

QmlBarometerAltimeterSensor::~QmlBarometerAltimeterSensor()
{}

QTQmlSensorReading *
QmlBarometerAltimeterSensor::createReading() const
{
  return new QmlBarometerAltimeterReading(m_sensor);
}

QSensor *
QmlBarometerAltimeterSensor::sensor() const
{
  return m_sensor;
}

/**************************************************************************************************/

// Freescale Semiconductor AN4528 (document has errors)
//
// Equation 1 is used for computing atmospheric pressure (P, in Pa) at a
// different altitude (h, in m) below 11 km.
//
// P = P0 * (1 - (L0 * h)/T0)^((g0 * M)/(R * L0))   Eqn. 1
//
// where:
//
// Symbol | Value     | Unit        | Description
// P0     | 101325    | Pa          | Sea-level standard atmospheric pressure
// L0     | 0.0065    | K/m         | Temperature lapse rate from sea level to 11 km
// T0     | 288.15    | K           | Sea-level standard temperature
// g0     | 9.80665   | m/s^2       | Sea-level gravitational acceleration
// M      | 0.0289644 | kg/mol      | Mean-molecular weight of air
// R      | 8.31432   | N·m/(K·mol) | Universal gas constant
//
// By inserting these parameters into Equation 1, we get the simplified
// Equation 2 for atmospheric-pressure calculation based on known
// altitude.
//
// P = P0 * (1 - h/44330.77)^5.255876   Eqn. 2
//
// Equation 3 is used for altitude calculation based on known atmospheric
// pressure after the conversion to Equation 2.
//
// h = 44330.77 * (1 - (P/P0)^0.190263)   Eqn. 3
//
// According to Equation 3, we can determine the altitude value with an
// accurate atmospheric-pressure measurement.

constexpr qreal P0 = 101325;    // kPa         | Sea-level standard atmospheric pressure
constexpr qreal L0 = 0.0065;    // K/m         | Temperature lapse rate from sea level to 11 km
constexpr qreal T0 = 288.15;    // K           | Sea-level standard temperature
constexpr qreal g0 = 9.80665;   // m/s^2       | Sea-level gravitational acceleration
constexpr qreal M  = 0.0289644; // kg/mol      | Mean-molecular weight of air
constexpr qreal R  = 8.31432;   // N·m/(K·mol) | Universal gas constant

// P = P0 * (1 - alpha * h)**beta
// h = 1 / alpha * (1 - (P/P0)**(1/beta))
// P0 = P / (1 - alpha * h)**beta

constexpr qreal ALPHA = L0 / T0;
constexpr qreal INVERSE_ALPHA = T0 / L0;
constexpr qreal BETA = (g0 * M)/(R * L0);
constexpr qreal INVERSE_BETA = (R * L0)/(g0 * M);

/**************************************************************************************************/

QmlBarometerAltimeterReading::QmlBarometerAltimeterReading(QPressureSensor *sensor)
  : QTQmlSensorReading(sensor),
    m_sensor(sensor),
    m_pressure(0),
    m_temperature(0),
    m_altitude(0),
    m_altitude_offset(0),
    m_sea_level_pressure(P0)
{}

QmlBarometerAltimeterReading::~QmlBarometerAltimeterReading()
{}

QSensorReading *
QmlBarometerAltimeterReading::reading() const
{
  return m_sensor->reading();
}

void
QmlBarometerAltimeterReading::readingUpdate()
{
  qreal pressure = m_sensor->reading()->pressure();
  if (m_pressure != pressure) {
    m_pressure = pressure;
    Q_EMIT pressureChanged();
    m_altitude = pressure_to_altitude(pressure);
    Q_EMIT altitudeChanged();
  }

  qreal temperature = m_sensor->reading()->temperature();
  if (m_temperature != temperature) {
    m_temperature = temperature;
    Q_EMIT temperatureChanged();
  }
}

qreal
QmlBarometerAltimeterReading::pressure_to_altitude(qreal pressure) const
{
  qreal altitude = INVERSE_ALPHA * (1 - qPow(pressure/m_sea_level_pressure, INVERSE_BETA));
  altitude += m_altitude_offset; // Fixme: only display ?
  return altitude;
}

void
QmlBarometerAltimeterReading::set_altitude_offset(qreal offset)
{
  qATInfo() << "set_altitude_offset" << offset;
  qreal old_altitude_offset = m_altitude_offset;
  m_altitude_offset = offset;
  Q_EMIT altitudeOffsetChanged();
  m_altitude += offset - old_altitude_offset;
  Q_EMIT altitudeChanged(); // versus readingUpdate ?
}

void
QmlBarometerAltimeterReading::set_sea_level_pressure(qreal sea_level_pressure)
{
  qATInfo() << "set_sea_level_pressure" << sea_level_pressure << m_sea_level_pressure;
  if (!qFuzzyCompare(sea_level_pressure, m_sea_level_pressure)) {
    qATInfo() << "set_sea_level_pressure yes";
    m_sea_level_pressure = sea_level_pressure;
    Q_EMIT pressureSeaLevelChanged();
    m_altitude = pressure_to_altitude(m_pressure);
    Q_EMIT altitudeChanged(); // versus readingUpdate ?
  }
}

void
QmlBarometerAltimeterReading::calibrate(qreal altitude)
{
  if (!qFuzzyCompare(altitude, m_altitude)) {
    qATInfo() << "calibrate" << altitude;
    altitude -= m_altitude_offset;
    m_sea_level_pressure = m_pressure / qPow(1 - ALPHA*altitude, BETA);
    qATInfo() << "sea_level_pressure" << m_sea_level_pressure;
    Q_EMIT pressureSeaLevelChanged();
    m_altitude = altitude;
    Q_EMIT altitudeChanged(); // versus readingUpdate ?
  }
}
