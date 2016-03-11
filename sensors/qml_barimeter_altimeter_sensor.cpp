#include "qml_barimeter_altimeter_sensor.h"
#include <QtSensors/QPressureSensor>

QmlBarometerAltimeterSensor::QmlBarometerAltimeterSensor(QObject *parent)
  : QTQmlSensor(parent)
  , m_sensor(new QPressureSensor(this))
{
}

QmlBarometerAltimeterSensor::~QmlBarometerAltimeterSensor()
{
}

QTQmlSensorReading *QmlBarometerAltimeterSensor::createReading() const
{
  return new QmlBarometerAltimeterReading(m_sensor);
}

QSensor *QmlBarometerAltimeterSensor::sensor() const
{
  return m_sensor;
}

QmlBarometerAltimeterReading::QmlBarometerAltimeterReading(QPressureSensor *sensor)
  : QTQmlSensorReading(sensor)
  , m_sensor(sensor)
  , m_pressure(0)
  , m_temperature(0)
{
}

QmlBarometerAltimeterReading::~QmlBarometerAltimeterReading()
{
}

qreal QmlBarometerAltimeterReading::pressure() const
{
  return m_pressure;
}

qreal QmlBarometerAltimeterReading::temperature() const
{
  return m_temperature;
}

QSensorReading *QmlBarometerAltimeterReading::reading() const
{
  return m_sensor->reading();
}

void QmlBarometerAltimeterReading::readingUpdate()
{
  qreal pressure = m_sensor->reading()->pressure();
  if (m_pressure != pressure) {
    m_pressure = pressure;
    Q_EMIT pressureChanged();
  }

  qreal temperature = m_sensor->reading()->temperature();
  if (m_temperature != temperature) {
    m_temperature = temperature;
    Q_EMIT temperatureChanged();
  }
}
