/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "wmts/wmts_network_reply.h"
#include "qtcarto.h"

/**************************************************************************************************/

QcWmtsNetworkReply::QcWmtsNetworkReply(QNetworkReply * reply,
                                       const QcTileSpec & tile_spec,
                                       const QString & format)
  : QcWmtsReply(reply, tile_spec),
    m_format(format)
{}

QcWmtsNetworkReply::~QcWmtsNetworkReply()
{}

/// Handle a successful request : store image data
void
QcWmtsNetworkReply::process_payload()
{
  set_image_data(network_reply()->readAll());
  set_image_format(m_format);
}
