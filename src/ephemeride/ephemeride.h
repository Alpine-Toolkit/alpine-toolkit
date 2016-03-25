// -*- mode: c++ -*-

/**************************************************************************************************/

#ifndef __EPHEMERIDE_H__
#define __EPHEMERIDE_H__

/**************************************************************************************************/

#include <QDate>
#include <QGeoCoordinate>
#include <QObject>
#include <QTime>

/**************************************************************************************************/

double compute_julian_day(const QDate & date);

/**************************************************************************************************/

QTime compute_sunrise_utc(double julian_day, double latitude, double longitude);
QTime compute_sunset_utc(double julian_day, double latitude, double longitude);
QTime compute_solar_noon_utc(double julian_day, double longitude);

/**************************************************************************************************/

class Ephemeride : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QDate date READ date WRITE set_date NOTIFY dataChanged)
  Q_PROPERTY(QGeoCoordinate coordinate READ coordinate WRITE set_coordinate NOTIFY dataChanged)
  Q_PROPERTY(QTime sunrise READ sunrise)
  Q_PROPERTY(QTime solar_noon READ solar_noon)
  Q_PROPERTY(QTime sunset READ sunset)

public:
  explicit Ephemeride(QObject *parent = nullptr);

  QDate date() const;
  void set_date(const QDate & date);

  QGeoCoordinate coordinate() const;
  void set_coordinate(const QGeoCoordinate & coordinate);

  QTime sunrise() const;
  QTime solar_noon() const;
  QTime sunset() const;

signals:
  void dataChanged();

private:
  QTime to_local_time(QTime utc_time) const;

private:
  QDate m_date;
  QGeoCoordinate m_coordinate;
  double m_julian_day;
};

/**************************************************************************************************/

#endif /* __EPHEMERIDE_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
