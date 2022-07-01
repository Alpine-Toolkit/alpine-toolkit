
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

#ifndef __QC_PATH_NODE_H__
#define __QC_PATH_NODE_H__

/**************************************************************************************************/

#include "map/decorated_path.h"
#include "map/viewport.h"

#include <QSGOpacityNode>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

struct PathVertex;

/**************************************************************************************************/

class QcPathNode : public QSGOpacityNode
{
public:
  QcPathNode(const QcViewport * viewport);

  void update(const QcDecoratedPathDouble * path);

private:
  void set_path_points(PathVertex * path_points,
                       int i,
                       QcVectorDouble & point0,
                       QcVectorDouble & point1,
                       QcVectorDouble & point2,
                       QcVectorDouble & point3,
                       double line_width,
                       double half_width,
                       const QColor & colour);

private:
  const QcViewport * m_viewport; // Fixme: &
  QSGGeometryNode * m_path_geometry_node;
  QSGGeometryNode * m_polygon_geometry_node;
  QSGGeometryNode * m_point_geometry_node;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_PATH_NODE_H__ */
