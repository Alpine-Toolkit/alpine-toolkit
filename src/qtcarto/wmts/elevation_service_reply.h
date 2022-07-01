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

#ifndef __QC_ELEVATION_SERVICE_REPLY_H__
#define __QC_ELEVATION_SERVICE_REPLY_H__

/**************************************************************************************************/

#include "coordinate/mercator.h"
#include "coordinate/wgs84.h"
#include "wmts/network_reply.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QcElevationServiceReply : public QcNetworkReply
{
  Q_OBJECT

public:
  explicit QcElevationServiceReply(QNetworkReply * reply, const QVector<QcWgsCoordinate> & coordinates);
  ~QcElevationServiceReply();

  const QVector<QcWgsElevationCoordinate> & elevations() const { return m_elevations; }

protected:
  QVector<QcWgsElevationCoordinate> & elevations() { return m_elevations; }

private:
  const QVector<QcWgsCoordinate> & m_coordinates;
  QVector<QcWgsElevationCoordinate> m_elevations;
};

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_ELEVATION_SERVICE_REPLY_H__ */
