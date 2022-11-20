/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "wmts_reply.h"
#include "qtcarto.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/// Constructs a tiled map reply object based on \a request, with parent \a parent.
QcWmtsReply::QcWmtsReply(QNetworkReply * reply, const QcTileSpec & tile_spec)
  : QcNetworkReply(reply),
    m_tile_spec(tile_spec)
{}

/// Destroys this tiled map reply object.
QcWmtsReply::~QcWmtsReply()
{}

/**************************************************************************************************/

// QC_END_NAMESPACE
