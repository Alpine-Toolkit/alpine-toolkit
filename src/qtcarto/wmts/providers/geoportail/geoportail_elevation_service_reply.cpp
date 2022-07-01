/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "geoportail_elevation_service_reply.h"
#include "qtcarto.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

/**************************************************************************************************/

QcGeoportailElevationServiceReply::QcGeoportailElevationServiceReply(QNetworkReply * reply,
                                                                     const QVector<QcWgsCoordinate> & coordinates)
  : QcElevationServiceReply(reply, coordinates)
{}

QcGeoportailElevationServiceReply::~QcGeoportailElevationServiceReply()
{}

// Handle a successful request : store image data
void
QcGeoportailElevationServiceReply::process_payload()
{
  QString ELEVATIONS = "elevations";
  QByteArray json_data = network_reply()->readAll();
  // { "elevations": [ { "lon": 0.23, "lat": 48.05, "z": 112.73, "acc": 2.5}, ... ] }
  // qQCInfo() << json_data;
  QJsonDocument json_document(QJsonDocument::fromJson(json_data));
  const QJsonObject & json_root_object = json_document.object();
  if (json_root_object.contains(ELEVATIONS)) {
    QJsonArray json_array = json_root_object[ELEVATIONS].toArray();
    for (const auto & json_ref : json_array) {
      const QJsonObject & json_object = json_ref.toObject();
      double longitude = json_object["lon"].toDouble();
      double latitude = json_object["lat"].toDouble();
      double elevation = json_object["z"].toDouble();
      // double elevation_accuracy = json_object["acc"].toDouble(); // unused
      elevations() << QcWgsElevationCoordinate(longitude, latitude, elevation);
    }
  }
  qQCInfo() << elevations();
}

/**************************************************************************************************/

// #include "geoportail_elevation_service_reply.moc"
