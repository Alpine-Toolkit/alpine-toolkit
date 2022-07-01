// -*- mode: c++ -*-
/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#ifndef __JSON_HELPER_H__
#define __JSON_HELPER_H__

/**************************************************************************************************/

#include <QDateTime>
#include <QGeoCoordinate>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QStringList>
#include <QUrl>
#include <QVariant>

/**************************************************************************************************/

namespace orm_type_conversion {

  // String List

  QStringList load_string_list(const QJsonArray & json_array);
  inline QStringList load_string_list(const QJsonValue & json_value) {
    return load_string_list(json_value.toArray());
  }

  QJsonArray dump_string_list(const QStringList & string_list);

  // Date

  inline QDate load_date(const QJsonValue & json_value) {
    // return json_value.toVariant().toDateTime();
    return QDate::fromString(json_value.toString());
  }
  inline QString dump_date(const QDate & date) {
    return date.toString(Qt::ISODate);
  }

  // DateTime

  inline QDateTime load_datetime(const QJsonValue & json_value) {
    // return json_value.toVariant().toDateTime();
    return QDateTime::fromString(json_value.toString());
  }
  inline QString dump_datetime(const QDateTime & datetime) {
    return datetime.toString(Qt::ISODate);
  }

  inline QDateTime load_sql_datetime(const QVariant & variant) {
    // return json_value.toVariant().toDateTime();
    return QDateTime::fromString(variant.toString());
  }
  inline QString dump_sql_datetime(const QDateTime & datetime) {
    return datetime.toString(Qt::ISODate);
  }

  // Unix Timestamp

  inline QDateTime load_sql_datetime_as_epoch(const QVariant & variant) {
    QDateTime datetime;
    datetime.setSecsSinceEpoch(variant.toInt());
    return datetime;
  }
  inline qint64 dump_sql_datetime_as_epoch(const QDateTime & datetime) {
    return datetime.toSecsSinceEpoch();
  }

  // Url

  inline QString dump_url(const QUrl & url) {
    return url.toString();
  }

  // GeoCoordinate

  QGeoCoordinate load_json_coordinate(const QJsonObject & json_object);
  inline QGeoCoordinate load_json_coordinate(const QJsonValue & json_value) {
    return load_json_coordinate(json_value.toObject());
  }

  QJsonObject dump_json_coordinate(const QGeoCoordinate & coordinate);

  QGeoCoordinate load_sql_coordinate(const QVariant & variant);
  QString dump_sql_coordinate(const QGeoCoordinate & coordinate);

  QGeoCoordinate load_wkb_point(const QVariant & variant);
  QByteArray dump_wkb_point(const QGeoCoordinate & coordinate);
}

/**************************************************************************************************/

#endif /* __JSON_HELPER_H__ */
