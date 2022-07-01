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

#ifndef __QC_LOCATION_SERVICE_REPLY_H__
#define __QC_LOCATION_SERVICE_REPLY_H__

/**************************************************************************************************/

#include "wmts/location_service_query.h"
#include "wmts/network_reply.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcLocationServiceReply : public QcNetworkReply
{
  Q_OBJECT

public:
  explicit QcLocationServiceReply(QNetworkReply * reply, const QcLocationServiceQuery & query);
  ~QcLocationServiceReply();

private:
  const QcLocationServiceQuery & m_query;
};

/**************************************************************************************************/

class QcLocationServiceReverseReply : public QcNetworkReply
{
  Q_OBJECT

public:
  explicit QcLocationServiceReverseReply(QNetworkReply * reply, const QcLocationServiceReverseQuery & query);
  ~QcLocationServiceReverseReply();

private:
  const QcLocationServiceReverseQuery & m_query;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_LOCATION_SERVICE_REPLY_H__ */
