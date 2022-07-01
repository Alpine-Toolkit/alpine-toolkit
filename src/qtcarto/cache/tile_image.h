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

#ifndef __QC_TILE_IMAGE_H__
#define __QC_TILE_IMAGE_H__

/**************************************************************************************************/

#include <QString>
#include <QByteArray>

#include "wmts/tile_spec.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

QString tile_spec_to_filename(const QcTileSpec & tile_spec, const QString & format, const QString & directory);
QcTileSpec filename_to_tile_spec(const QString & filename);

void write_tile_image(const QString & filename, const QByteArray & bytes);
QByteArray read_tile_image(const QString & filename);

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_TILE_IMAGE_H__ */
