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

#ifndef __QC_GRID_NODE_H__
#define __QC_GRID_NODE_H__

/**************************************************************************************************/

#include <QSGGeometry>

/**************************************************************************************************/

#include "map/viewport.h"
#include "map/wmts/tile_matrix_set.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcGridNode : public QSGGeometryNode
{
public:
  QcGridNode(const QcTileMatrixSet & tile_matrix_set, const QcViewport * viewport);

  void update();

private:
  const QcTileMatrixSet & m_tile_matrix_set;
  const QcViewport * m_viewport;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_GRID_NODE_H__ */
