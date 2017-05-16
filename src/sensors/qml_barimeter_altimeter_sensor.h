// -*- mode: c++ -*-

/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire.
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
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef ALTIMETER_SENSOR_H
#define ALTIMETER_SENSOR_H

/**************************************************************************************************/

#include "qmlsensor.h"

// QT_BEGIN_NAMESPACE

class QPressureSensor;
class QmlBarometerAltimeterReading;

/**************************************************************************************************/

class QmlBarometerAltimeterSensor : public QTQmlSensor
{
  Q_OBJECT

public:
  explicit QmlBarometerAltimeterSensor(QObject * parent = 0);
  ~QmlBarometerAltimeterSensor();

private:
  QSensor * sensor() const Q_DECL_OVERRIDE;
  QTQmlSensorReading * createReading() const Q_DECL_OVERRIDE;

  QPressureSensor * m_sensor;
};

/**************************************************************************************************/

class QmlBarometerAltimeterReading : public QTQmlSensorReading
{
  Q_OBJECT
  Q_PROPERTY(qreal pressure READ pressure NOTIFY pressureChanged)
  Q_PROPERTY(qreal sea_level_pressure READ sea_level_pressure WRITE set_sea_level_pressure NOTIFY pressureSeaLevelChanged)
  Q_PROPERTY(qreal temperature READ temperature NOTIFY temperatureChanged REVISION 1)
  Q_PROPERTY(qreal altitude READ altitude WRITE calibrate NOTIFY altitudeChanged)
  Q_PROPERTY(qreal altitude_offset READ altitude_offset WRITE set_altitude_offset NOTIFY altitudeOffsetChanged)

public:
  explicit QmlBarometerAltimeterReading(QPressureSensor * sensor);
  ~QmlBarometerAltimeterReading();

  qreal pressure() const { return m_pressure; }
  qreal sea_level_pressure() const { return m_sea_level_pressure; }
  qreal temperature() const { return m_temperature; }
  qreal altitude() const { return m_altitude; }
  qreal altitude_offset() const { return m_altitude_offset; }

  void set_sea_level_pressure(qreal sea_level_pressure);
  void set_altitude_offset(qreal offset);
  void calibrate(qreal altitude);

Q_SIGNALS:
  void pressureChanged();
  void pressureSeaLevelChanged();
  Q_REVISION(1) void temperatureChanged();
  void altitudeChanged();
  void altitudeOffsetChanged();

private:
  QSensorReading * reading() const Q_DECL_OVERRIDE;
  void readingUpdate() Q_DECL_OVERRIDE;
  qreal pressure_to_altitude(qreal pressure) const;

private:
  QPressureSensor * m_sensor;
  qreal m_pressure;
  qreal m_temperature;
  qreal m_altitude;
  qreal m_altitude_offset;
  qreal m_sea_level_pressure;
};

/**************************************************************************************************/

// QT_END_NAMESPACE

#endif

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
