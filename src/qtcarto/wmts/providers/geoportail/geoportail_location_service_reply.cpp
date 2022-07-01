/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "geoportail_location_service_reply.h"
#include "qtcarto.h"

/**************************************************************************************************/

QcGeoportailLocationServiceReply::QcGeoportailLocationServiceReply(QNetworkReply * reply,
                                                                   const QcLocationServiceQuery & query)
  : QcLocationServiceReply(reply, query)
{}

QcGeoportailLocationServiceReply::~QcGeoportailLocationServiceReply()
{}

// Handle a successful request : store image data
void
QcGeoportailLocationServiceReply::process_payload()
{
  qQCInfo() << network_reply()->readAll();
}

/**************************************************************************************************/

QcGeoportailLocationServiceReverseReply::QcGeoportailLocationServiceReverseReply(QNetworkReply * reply,
                                                                                 const QcLocationServiceReverseQuery & query)
  : QcLocationServiceReverseReply(reply, query)
{}

QcGeoportailLocationServiceReverseReply::~QcGeoportailLocationServiceReverseReply()
{}

// Handle a successful request : store image data
void
QcGeoportailLocationServiceReverseReply::process_payload()
{
  qQCInfo() << network_reply()->readAll();
}

/**************************************************************************************************/

// #include "geoportail_location_service_reply.moc"
