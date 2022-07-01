/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "location_service_reply.h"
#include "qtcarto.h"

/**************************************************************************************************/

QcLocationServiceReply::QcLocationServiceReply(QNetworkReply * reply,
                                               const QcLocationServiceQuery & query)
  : QcNetworkReply(reply),
    m_query(query)
{
}

QcLocationServiceReply::~QcLocationServiceReply()
{}

/**************************************************************************************************/

QcLocationServiceReverseReply::QcLocationServiceReverseReply(QNetworkReply * reply,
                                                             const QcLocationServiceReverseQuery & query)
  : QcNetworkReply(reply),
    m_query(query)
{
}

QcLocationServiceReverseReply::~QcLocationServiceReverseReply()
{}

/**************************************************************************************************/


// #include "location_service_reply.moc"
