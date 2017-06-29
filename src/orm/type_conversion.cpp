/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
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

#include "orm/type_conversion.h"

#include "geo_data_format/wkb.h"

/**************************************************************************************************/

namespace orm_type_conversion {

  QStringList
  load_string_list(const QJsonArray & json_array)
  {
    QStringList string_list;
    for (const auto & json_value : json_array)
      string_list << json_value.toString();
    return string_list;
  }

  QJsonArray
  dump_string_list(const QStringList & string_list)
  {
    QJsonArray json_array;
    for (const auto & string : string_list)
      json_array << string;
    return json_array;
  }

/**************************************************************************************************/

  QGeoCoordinate
  load_json_coordinate(const QJsonObject & json_object)
  {
    double longitude = json_object[QLatin1Literal("longitude")].toDouble();
    double latitude = json_object[QLatin1Literal("latitude")].toDouble();
    return QGeoCoordinate(latitude, longitude);
  }

  QJsonObject
  dump_json_coordinate(const QGeoCoordinate & coordinate)
  {
    QJsonObject json_object;
    json_object[QLatin1Literal("longitude")] = coordinate.longitude();
    json_object[QLatin1Literal("latitude")] = coordinate.latitude();

    return json_object;
  }

  QGeoCoordinate
  load_sql_coordinate(const QVariant & variant) {
    QString encoded_coordinate = variant.toString();
    int position = encoded_coordinate.indexOf(',');
    if (position > 0) {
      double longitude = encoded_coordinate.left(position).toDouble();
      double latitude = encoded_coordinate.mid(position +1).toDouble();
      return QGeoCoordinate(latitude, longitude);
    } else
      return QGeoCoordinate();
  }
  QString
  dump_sql_coordinate(const QGeoCoordinate & coordinate) {
    // return QString("%1|%2").arg(coordinate.longitude()).arg(coordinate.latitude());
    // Point(,)
    return QString("%1,%2").arg(QString::number(coordinate.longitude())).arg(QString::number(coordinate.latitude()));
  }

  QGeoCoordinate
  load_wkb_point(const QVariant & variant) {
    QcWkbPoint point(variant.toByteArray());
    double longitude = point.x();
    double latitude = point.y();
    return QGeoCoordinate(latitude, longitude);
  }

  QByteArray
  dump_wkb_point(const QGeoCoordinate & coordinate) {
    QcWkbPoint point(coordinate.longitude(), coordinate.latitude());
    return point.to_wkb();
  }
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
