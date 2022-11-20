// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __QC_GEOPORTAIL_PLUGIN_H__
#define __QC_GEOPORTAIL_PLUGIN_H__

/**************************************************************************************************/

#include "wmts/providers/geoportail/geoportail_elevation_service_reply.h"
#include "wmts/providers/geoportail/geoportail_license.h"
#include "wmts/providers/geoportail/geoportail_location_service_reply.h"
#include "wmts/wmts_plugin.h"

#include <QAuthenticator>
#include <QHash>
#include <QList>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QcGeoportailPlugin;

/**************************************************************************************************/

// The QcGeoportailLayer class implements a IGN Geoportail WMTS layer.
class QcGeoportailLayer : public QcWmtsPluginLayer
{
 public:
  QcGeoportailLayer(QcGeoportailPlugin * plugin,
                    int map_id,
                    int position,
                    const QString & title,
                    const QString & name,
                    const QString & image_format,
                    const QString & style);
  QcGeoportailLayer(const QcGeoportailLayer & other);
  ~QcGeoportailLayer();

  QcGeoportailLayer & operator=(const QcGeoportailLayer & other);

  const QString & style() const { return m_style; }

  QUrl url(const QcTileSpec & tile_spec) const;

 private:
  QString m_style;
};

/**************************************************************************************************/

/// The QcGeoportailPlugin class implements a IGN Geoportail WMTS plugin.
class QcGeoportailPlugin : public QcWmtsPlugin
{
  Q_OBJECT

 public:
  static const QString PLUGIN_NAME;
  static QcWmtsPlugin * instantiate();

 public:
  QcGeoportailPlugin(const QcGeoportailWmtsLicense & license);
  ~QcGeoportailPlugin();

  const QcGeoportailWmtsLicense & license() const { return m_license; }

  bool has_location_service() override { return true; }
  QSharedPointer<QcLocationServiceReply> geocode_request(const QcLocationServiceQuery & query) override;
  // virtual QSharedPointer<QcLocationServiceReply> inverse_geocode_request(const QcLocationServiceInverseQuery & query) const;

  bool has_coordinate_elevation_service() override { return true; }
  bool has_sampling_elevation_service() override { return true; }
  QSharedPointer<QcElevationServiceReply> coordinate_elevations(const QVector<QcWgsCoordinate> & coordinates) override;
  QSharedPointer<QcLocationServiceReverseReply> reverse_geocode_request(const QcLocationServiceReverseQuery & query) override;

 private Q_SLOTS:
  void on_authentication_request_slot(QNetworkReply * reply, QAuthenticator * authenticator);

 private:
  QcGeoportailWmtsLicense m_license;

  QSharedPointer<QcLocationServiceReply> m_location_reply;
  QSharedPointer<QcLocationServiceReverseReply> m_location_reverse_reply;
  QSharedPointer<QcElevationServiceReply> m_elevation_reply;
};

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_GEOPORTAIL_PLUGIN_H__ */
