/**************************************************************************************************/

#include <cmath>
#include <QtMath>
#include <QtDebug>

#include "ephemeride.h"

/**************************************************************************************************/

/*
 * The code is derived from the NOAA Sunrise/Sunset and Solar Position Calculators
 * http://www.esrl.noaa.gov/gmd/grad/solcalc
 *
 * The calculations are based on equations from Astronomical Algorithms, by Jean Meeus.
 *
 * The sunrise and sunset results are theoretically accurate to within
 * a minute for locations between +/- 72° latitude, and within 10
 * minutes outside of those latitudes. However, due to variations in
 * atmospheric composition, temperature, pressure and conditions,
 * observed values may vary from calculations.
 *
 * It can report values between the years -2000 and +3000.
 *
 */

/**************************************************************************************************/

constexpr double JULIAN_YEAR = 365.25; // days
constexpr double MINUTES_IN_DAY = 24*60; // 1440 minutes

/**************************************************************************************************/

/*
 * The Julian Day Count is a uniform count of days from a remote epoch in the past
 *  -4712     January   1, 12 hours Greenwich Mean Time (Julian proleptic Calendar)
 * = 4713 BCE January   1, 12 hours GMT (Julian proleptic Calendar)
 * = 4714 BCE November 24, 12 hours GMT (Gregorian proleptic Calendar)
 * At this instant, the Julian Day Number is 0.
 *
 * http://aa.usno.navy.mil/faq/docs/JD_Formula.php
 * http://quasar.as.utexas.edu/BillInfo/JulianDatesG.html
 *
 */
double
compute_julian_day(const QDate & date)
{
  int year = date.year();
  int month = date.month();
  int day = date.day();

  if (month <= 2) {
    year -= 1;
    month += 12;
  }

  double a = floor(year/100);
  double b = floor(a/4);
  double c = 2 - a + b;
  double d = floor(365.25*(year + 4716));
  double e = floor(30.6001*(month + 1));
  double julian_day = c + d + e + day - 1524.5;

  return julian_day;
}

double
compute_julian_century(double julian_day)
{
  return (julian_day - 2451545.0) / 36525.0;
}

/**************************************************************************************************/

QTime
minutes_to_time(double minutes)
{
  if ((minutes >= 0) && (minutes < MINUTES_IN_DAY)) {
    double float_hour = minutes / 60.0;
    double float_minute = 60.0 * (float_hour - floor(float_hour));
    double float_second = 60.0 * (float_minute - floor(float_minute));

    double hour = floor(float_hour);
    double minute = floor(float_minute);
    double second = floor(float_second + 0.5);

    if (second > 59) {
      second = 0;
      minute += 1;
    }

    // round seconds
    if (second >= 30)
      minute += 1;
    second = 0;

    if (minute > 59) {
      minute = 0;
      hour += 1;
    }

    return QTime(hour, minute, second);
  } else {
    qWarning() << minutes;
    return QTime();
  }
}

/**************************************************************************************************/

double
compute_geometric_mean_longitude_sun(double t)
{
  double l0 = 280.46646 + t * (36000.76983 + t * 0.0003032);

  while (l0 > 360.0) { // modulo ?
    l0 -= 360.0;
  }
  while (l0 < 0.0) {
    l0 += 360.0;
  }

  return l0; // in degrees
}

double
compute_geometric_mean_anomaly_sun(double t)
{
  return 357.52911 + t * (35999.05029 - 0.0001537 * t); // in degrees
}

double
compute_earth_orbit_eccentricity(double t)
{
  return 0.016708634 - t * (0.000042037 + 0.0000001267 * t); // unitless
}

double
compute_mean_obliquity_of_ecliptic(double t)
{
  double seconds = 21.448 - t * (46.8150 + t * (0.00059 - t * 0.001813));
  double e0 = 23.0 + (26.0 + (seconds / 60.0)) / 60.0;

  return e0; // in degrees
}

/**************************************************************************************************/

double
compute_sun_equation_of_center(double t)
{
  double m = compute_geometric_mean_anomaly_sun(t);
  double mrad = qDegreesToRadians(m);
  double sinm = sin(mrad);
  double sin2m = sin(2*mrad); // mrad + mrad ???
  double sin3m = sin(3*mrad);
  double c = sinm * (1.914602 - t * (0.004817 + 0.000014 * t)) + sin2m * (0.019993 - 0.000101 * t) + sin3m * 0.000289;

  return c; // in degrees
}

double
compute_sun_true_longitude(double t)
{
  double l0 = compute_geometric_mean_longitude_sun(t);
  double c = compute_sun_equation_of_center(t);

  return l0 + c; // in degrees
}

double
compute_sun_true_anomaly(double t)
{
  double m = compute_geometric_mean_anomaly_sun(t);
  double c = compute_sun_equation_of_center(t);

  return m + c; // in degrees
}

/*
double
compute_sun_radius_vector(double t)
{
  double v = compute_sun_true_anomaly(t);
  double e = compute_earth_orbit_eccentricity(t);
  double r = (1.000001018 * (1 - e * e)) / (1 + e * cos(qDegreesToRadians(v)));

  return r; // in AUs
}
*/

double
compute_sun_apparent_longitude(double t)
{
  double o = compute_sun_true_longitude(t);
  double omega = 125.04 - 1934.136 * t;
  double lambda = o - 0.00569 - 0.00478 * sin(qDegreesToRadians(omega));

  return lambda; // in degrees
}

double
compute_obliquity_correction(double t)
{
  double e0 = compute_mean_obliquity_of_ecliptic(t);
  double omega = 125.04 - 1934.136 * t;
  double e = e0 + 0.00256 * cos(qDegreesToRadians(omega));

  return e; // in degrees
}

double
compute_sun_declination(double t)
{
  double e = compute_obliquity_correction(t);
  double lambda = compute_sun_apparent_longitude(t);

  double sint = sin(qDegreesToRadians(e)) * sin(qDegreesToRadians(lambda));
  double theta = qRadiansToDegrees(asin(sint));

  return theta; // in degrees
}

double
compute_equation_of_time(double t)
{
  double epsilon = compute_obliquity_correction(t);
  double l0 = compute_geometric_mean_longitude_sun(t);
  double e = compute_earth_orbit_eccentricity(t);
  double m = compute_geometric_mean_anomaly_sun(t);

  double y = tan(qDegreesToRadians(epsilon)/2.0);
  y *= y;

  double l0_rad = qDegreesToRadians(l0);
  double sin2l0 = sin(2.0 * l0_rad);
  double sin4l0 = sin(4.0 * l0_rad);
  double cos2l0 = cos(2.0 * l0_rad);
  double m_rad = qDegreesToRadians(m);
  double sinm   = sin(m_rad);
  double sin2m  = sin(2.0 * m_rad);

  double etime = y * sin2l0 - 2.0 * e * sinm + 4.0 * e * y * sinm * cos2l0 - 0.5 * y * y * sin4l0 - 1.25 * e * e * sin2m;
  return qRadiansToDegrees(etime) * 4.0; // in minutes of time
}

double
compute_hour_angle_sunrise(double latitude, double solar_declination)
{
  double latitude_rad = qDegreesToRadians(latitude);
  double solar_declination_rad = qDegreesToRadians(solar_declination);

  // For sunrise and sunset calculations, we assume 0.833° of atmospheric refraction.
  double hour_angle_arg = (cos(qDegreesToRadians(90.833)) /
			   ( cos(latitude_rad) * cos(solar_declination_rad))
			   - tan(latitude_rad) * tan(solar_declination_rad));
  double ha = acos(hour_angle_arg);

  return ha; // in radians (for sunset, use -HA)
}

/**************************************************************************************************/

double
compute_sunrise_set_minutes_utc(bool rise, double julian_day, double latitude, double longitude)
{
  double t = compute_julian_century(julian_day);
  double equation_of_time = compute_equation_of_time(t);
  double solar_declination = compute_sun_declination(t);
  double hour_angle = compute_hour_angle_sunrise(latitude, solar_declination);

  if (!rise)
    hour_angle = -hour_angle;

  double delta = longitude + qRadiansToDegrees(hour_angle);
  double time_utc = 720 - (4.0 * delta) - equation_of_time;

  return time_utc; // in minutes
}

double
compute_solar_noon_utc_minutes(double julian_day, double longitude)
{
  double t_noon = compute_julian_century(julian_day - longitude/360.0);
  double equation_of_time = compute_equation_of_time(t_noon);
  double solar_noon_offset = 720.0 - (longitude * 4) - equation_of_time; // in minutes

  double new_t = compute_julian_century(julian_day + solar_noon_offset/MINUTES_IN_DAY);
  equation_of_time = compute_equation_of_time(new_t);
  double solar_noon = 720.0 - (longitude * 4) - equation_of_time; // in minutes

  // solar_noon += (timezone*60.0);
  // if (dst)
  //   solNoonLocal += 60.0;
  // while (solNoonLocal < 0.0) {
  //   solNoonLocal += MINUTES_IN_DAY;
  // }
  // while (solNoonLocal >= MINUTES_IN_DAY) {
  //   solNoonLocal -= MINUTES_IN_DAY;
  // }

  return solar_noon;
}

/**************************************************************************************************/

QTime
compute_sunrise_utc(double julian_day, double latitude, double longitude)
{
  return minutes_to_time(compute_sunrise_set_minutes_utc(true, julian_day, latitude, longitude));
}

QTime
compute_sunset_utc(double julian_day, double latitude, double longitude)
{
  return minutes_to_time(compute_sunrise_set_minutes_utc(false, julian_day, latitude, longitude));
}

QTime
compute_solar_noon_utc(double julian_day, double longitude)
{
  return minutes_to_time(compute_solar_noon_utc_minutes(julian_day, longitude));
}

/**************************************************************************************************/

Ephemeride::Ephemeride(QObject *parent)
  : QObject(parent),
    m_date(), m_coordinate()
{}

void
Ephemeride::set_date(const QDate & date)
{
  m_date = date;
  m_julian_day = compute_julian_day(date);
  emit dataChanged();
}

QDate
Ephemeride::date() const
{
  return m_date;
}

void
Ephemeride::set_coordinate(const QGeoCoordinate & coordinate)
{
  m_coordinate = coordinate;
  emit dataChanged();
}

QGeoCoordinate
Ephemeride::coordinate() const
{
  return m_coordinate;
}

QTime
Ephemeride::to_local_time(QTime utc_time) const
{
  return QDateTime(m_date, utc_time, Qt::UTC).toLocalTime().time();
}

QTime
Ephemeride::sunrise() const
{
  return to_local_time(compute_sunrise_utc(m_julian_day, m_coordinate.latitude(), m_coordinate.longitude()));
}

QTime
Ephemeride::solar_noon() const
{
  return to_local_time(compute_solar_noon_utc(m_julian_day, m_coordinate.longitude()));
}

QTime
Ephemeride::sunset() const
{
  return to_local_time(compute_sunset_utc(m_julian_day, m_coordinate.latitude(), m_coordinate.longitude()));
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
