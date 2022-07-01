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

#ifndef __QC_LOCATION_CIRCLE_NODE_H__
#define __QC_LOCATION_CIRCLE_NODE_H__

/**************************************************************************************************/

#include "map/location_circle_data.h"
#include "map/viewport.h"

#include <QSGOpacityNode>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/// The QcLocationCircleNode class implements a location circle node
class QcLocationCircleNode : public QSGOpacityNode
{
public:
  QcLocationCircleNode(const QcViewport * viewport);

  void update(const QcLocationCircleData & location_circle_data);

private:
  const QcViewport * m_viewport; // Fixme: &
  QSGGeometryNode * m_geometry_node;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_LOCATION_CIRCLE_NODE_H__ */
