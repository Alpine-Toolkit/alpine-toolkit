// -*- mode: c++ -*-

#ifndef ALTIMETER_SENSOR_H
#define ALTIMETER_SENSOR_H

#include "qmlsensor.h"

// QT_BEGIN_NAMESPACE

class QPressureSensor;

class QmlBarometerAltimeterSensor : public QTQmlSensor
{
  Q_OBJECT

public:
  explicit QmlBarometerAltimeterSensor(QObject *parent = 0);
  ~QmlBarometerAltimeterSensor();

private:
  QSensor *sensor() const Q_DECL_OVERRIDE;
  QTQmlSensorReading *createReading() const Q_DECL_OVERRIDE;

  QPressureSensor *m_sensor;
};

class QmlBarometerAltimeterReading : public QTQmlSensorReading
{
  Q_OBJECT
  Q_PROPERTY(qreal pressure READ pressure NOTIFY pressureChanged)
  Q_PROPERTY(qreal temperature READ temperature NOTIFY temperatureChanged REVISION 1)

public:
  explicit QmlBarometerAltimeterReading(QPressureSensor *sensor);
  ~QmlBarometerAltimeterReading();

  qreal pressure() const;
  qreal temperature() const;

Q_SIGNALS:
  void pressureChanged();
  Q_REVISION(1) void temperatureChanged();

private:
  QSensorReading *reading() const Q_DECL_OVERRIDE;
  void readingUpdate() Q_DECL_OVERRIDE;

  QPressureSensor *m_sensor;
  qreal m_pressure;
  qreal m_temperature;
};

// QT_END_NAMESPACE

#endif
