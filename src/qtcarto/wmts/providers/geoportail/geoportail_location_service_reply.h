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

#ifndef __QC_GEOPORTAIL_LOCATION_SERVICE_REPLY_H__
#define __QC_GEOPORTAIL_LOCATION_SERVICE_REPLY_H__

/**************************************************************************************************/

#include "wmts/location_service_reply.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcGeoportailLocationServiceReply : public QcLocationServiceReply
{
  Q_OBJECT

public:
  explicit QcGeoportailLocationServiceReply(QNetworkReply * reply, const QcLocationServiceQuery & query);
  ~QcGeoportailLocationServiceReply();

  void process_payload();
};

/**************************************************************************************************/

class QcGeoportailLocationServiceReverseReply : public QcLocationServiceReverseReply
{
  Q_OBJECT

public:
  explicit QcGeoportailLocationServiceReverseReply(QNetworkReply * reply, const QcLocationServiceReverseQuery & query);
  ~QcGeoportailLocationServiceReverseReply();

  void process_payload();
};


/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_GEOPORTAIL_LOCATION_SERVICE_REPLY_H__ */
