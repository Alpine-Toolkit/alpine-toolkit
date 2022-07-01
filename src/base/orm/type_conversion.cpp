/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#include "orm/type_conversion.h"
#include "alpine_toolkit.h"

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
    double longitude = json_object[QStringLiteral("longitude")].toDouble();
    double latitude = json_object[QStringLiteral("latitude")].toDouble();
    return QGeoCoordinate(latitude, longitude);
  }

  QJsonObject
  dump_json_coordinate(const QGeoCoordinate & coordinate)
  {
    QJsonObject json_object;
    json_object[QStringLiteral("longitude")] = coordinate.longitude();
    json_object[QStringLiteral("latitude")] = coordinate.latitude();

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
