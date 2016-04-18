/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the QtCarto library.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include <QtTest/QtTest>
#include <QtDebug>

#include <QDateTime>

/**************************************************************************************************/

#include "ephemeride/ephemeride.h"

/***************************************************************************************************/

class TestEphemeride: public QObject
{
  Q_OBJECT

private slots:
  void test_compute_julian_day_data();
  void test_compute_julian_day();
  void test_compute_sunrise_set_data();
  void test_compute_sunrise_set();
  void test_Ephemeride();
};

void
TestEphemeride::test_compute_julian_day_data()
{
  QTest::addColumn<QDate>("date");
  QTest::addColumn<double>("julian_day");

  QTest::newRow("date1") << QDate(2016 , 1,  1) << 2457388.5;
  QTest::newRow("date2") << QDate(2016 , 2,  1) << 2457419.5;
  QTest::newRow("date3") << QDate(2016 , 3,  1) << 2457448.5;
  QTest::newRow("date4") << QDate(2016 ,12, 31) << 2457753.5;
}

void
TestEphemeride::test_compute_julian_day()
{
  QFETCH(QDate, date);
  QFETCH(double, julian_day);

  QVERIFY(qFuzzyCompare(compute_julian_day(date), julian_day));
}

void
TestEphemeride::test_compute_sunrise_set_data()
{
  QTest::addColumn<QDate>("date");
  QTest::addColumn<QTime>("sunrise");
  QTest::addColumn<QTime>("noon");
  QTest::addColumn<QTime>("sunset");

  // DST off
  QTest::newRow("date1") << QDate(2016 ,  1,  1) << QTime(8, 43) << QTime(12, 53) << QTime(17, 02); // solcalc report 17:03  -1 ???
  QTest::newRow("date1") << QDate(2016 ,  3,  1) << QTime(7, 31) << QTime(13, 02) << QTime(18, 32); // 18:33
  QTest::newRow("date1") << QDate(2016 ,  6,  1) << QTime(4, 50) << QTime(12, 47) << QTime(20, 44); // 20:45
  QTest::newRow("date1") << QDate(2016 ,  9,  1) << QTime(6,  6) << QTime(12, 49) << QTime(19, 33); // 19:31
  QTest::newRow("date1") << QDate(2016 , 12,  1) << QTime(8, 21) << QTime(12, 39) << QTime(16, 55); // 8:22
}

QTime
to_local_time(const QTime & utc_time, int timezone = 1)
{
  return QTime(utc_time.hour() + timezone, utc_time.minute(), utc_time.second());
}

void
TestEphemeride::test_compute_sunrise_set()
{
  QFETCH(QDate, date);
  QFETCH(QTime, sunrise);
  QFETCH(QTime, noon);
  QFETCH(QTime, sunset);

  double latitude = 48.87; // for Paris
  double longitude = 2.67;

  double julian_day = compute_julian_day(date);

  QTime _sunrise = to_local_time(compute_sunrise_utc(julian_day, latitude, longitude));
  QTime _sunset = to_local_time(compute_sunset_utc(julian_day, latitude, longitude));
  QTime _noon = to_local_time(compute_solar_noon_utc(julian_day, longitude));
  qInfo() << _sunrise << _noon << _sunset;
  QVERIFY(_sunrise == sunrise);
  QVERIFY(_noon == noon);
  QVERIFY(_sunset == sunset);

  // QDateTime sunrise_date(date, _sunrise, Qt::UTC);
  // qInfo() << sunrise_date << sunrise_date.toLocalTime();
}

void
TestEphemeride::test_Ephemeride()
{
  Ephemeride ephemeride;
  ephemeride.set_date(QDate(2016, 1, 1));
  ephemeride.set_coordinate(QGeoCoordinate(48.87, 2.67));
  qInfo() << ephemeride.sunrise() << ephemeride.solar_noon() << ephemeride.sunset();
}

/***************************************************************************************************/

QTEST_MAIN(TestEphemeride)
#include "test_ephemeride.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
