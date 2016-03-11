// -*- mode: c++ -*-

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
  Q_PROPERTY(qreal altitude READ altitude WRITE calibrate NOTIFY altitudeChanged)
  Q_PROPERTY(qreal altitude_offset READ altitude_offset WRITE set_altitude_offset NOTIFY altitudeOffsetChanged)

public:
  explicit QmlBarometerAltimeterSensor(QObject * parent = 0);
  ~QmlBarometerAltimeterSensor();

  qreal altitude() const;
  qreal altitude_offset() const;

  void set_altitude_offset(qreal offset);
  void calibrate(qreal altitude);

Q_SIGNALS:
  void altitudeChanged();
  void altitudeOffsetChanged();

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
  Q_PROPERTY(qreal pressure_sea_level READ pressure_sea_level NOTIFY pressureSeaLevelChanged)
  Q_PROPERTY(qreal temperature READ temperature NOTIFY temperatureChanged REVISION 1)
  Q_PROPERTY(qreal altitude READ altitude WRITE calibrate NOTIFY altitudeChanged)
  Q_PROPERTY(qreal altitude_offset READ altitude_offset WRITE set_altitude_offset NOTIFY altitudeOffsetChanged)

public:
  explicit QmlBarometerAltimeterReading(QPressureSensor * sensor);
  ~QmlBarometerAltimeterReading();

  qreal pressure() const;
  qreal pressure_sea_level() const;
  qreal temperature() const;
  qreal altitude() const;
  qreal altitude_offset() const;

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
  qreal m_pressure_sea_level;
};

/**************************************************************************************************/

// QT_END_NAMESPACE

#endif

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
