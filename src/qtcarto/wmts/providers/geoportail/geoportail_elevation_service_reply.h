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

#ifndef __QC_GEOPORTAIL_ELEVATION_REPLY_H__
#define __QC_GEOPORTAIL_ELEVATION_REPLY_H__

/**************************************************************************************************/

#include "wmts/elevation_service_reply.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QcGeoportailElevationServiceReply : public QcElevationServiceReply
{
  Q_OBJECT

public:
  explicit QcGeoportailElevationServiceReply(QNetworkReply * reply,
                                             const QVector<QcWgsCoordinate> & coordinates);
  ~QcGeoportailElevationServiceReply();

  void process_payload();
};

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_GEOPORTAIL_ELEVATION_REPLY_H__ */
