/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire.
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the QtCarto library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $QTCARTO_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include <QtMath>
#include <QtSensors/QPressureSensor>

#include <QtDebug>

#include "qml_barimeter_altimeter_sensor.h"

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
    m_pressure_sea_level(P0)
{}

QmlBarometerAltimeterReading::~QmlBarometerAltimeterReading()
{}

qreal
QmlBarometerAltimeterReading::pressure() const
{
  return m_pressure;
}

qreal
QmlBarometerAltimeterReading::pressure_sea_level() const
{
  return m_pressure_sea_level;
}

qreal
QmlBarometerAltimeterReading::temperature() const
{
  return m_temperature;
}

qreal
QmlBarometerAltimeterReading::altitude() const
{
  return m_altitude;
}

qreal
QmlBarometerAltimeterReading::altitude_offset() const
{
  return m_altitude_offset;
}

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
  qreal altitude = INVERSE_ALPHA * (1 - qPow(pressure/m_pressure_sea_level, INVERSE_BETA));
  altitude += m_altitude_offset; // Fixme: only display ?
  return altitude;
}

void
QmlBarometerAltimeterReading::set_altitude_offset(qreal offset)
{
  qInfo() << "set_altitude_offset" << offset;
  qreal old_altitude_offset = m_altitude_offset;
  m_altitude_offset = offset;
  Q_EMIT altitudeOffsetChanged();
  m_altitude += offset - old_altitude_offset;
  Q_EMIT altitudeChanged(); // versus readingUpdate ?
}

void
QmlBarometerAltimeterReading::calibrate(qreal altitude)
{
  qInfo() << "calibrate" << altitude;
  altitude -= m_altitude_offset;
  m_pressure_sea_level = m_pressure / qPow(1 - ALPHA*altitude, BETA);
  qInfo() << "pressure_sea_level" << m_pressure_sea_level;
  Q_EMIT pressureSeaLevelChanged();
  m_altitude = altitude;
  Q_EMIT altitudeChanged(); // versus readingUpdate ?
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
