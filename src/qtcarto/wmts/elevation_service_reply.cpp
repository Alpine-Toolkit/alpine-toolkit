/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "elevation_service_reply.h"
#include "qtcarto.h"

/**************************************************************************************************/

QcElevationServiceReply::QcElevationServiceReply(QNetworkReply * reply,
                                   const QVector<QcWgsCoordinate> & coordinates)
  : QcNetworkReply(reply),
    m_coordinates(coordinates)
{
}

QcElevationServiceReply::~QcElevationServiceReply()
{}

/**************************************************************************************************/

// #include "elevation_service_reply.moc"
