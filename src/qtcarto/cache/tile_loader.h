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

#ifndef __QC_TILE_LOADER_H__
#define __QC_TILE_LOADER_H__

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class TileLoader
{
public:
  TileLoader(const QcPlugin * plugin);

  load(const QcPolygon * polygon);
}

// QC_END_NAMESPACE

#endif /* __QC_TILE_LOADER_H__ */
