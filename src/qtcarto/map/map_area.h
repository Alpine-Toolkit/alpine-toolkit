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

#ifndef __QC_MAP_AREA_H__
#define __QC_MAP_AREA_H__

/**************************************************************************************************/

#include "math/polygon.h"
#include "math/vector.h"

// #include "geo_coordinate.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/// Unused code
class QcMapArea
{
public:
  QcMapArea();
  ~QcMapArea();

  void clear();
  void add_vertex(QcVectorDouble vertex);

private:
  QcPolygon m_polygon;
};

// QC_END_NAMESPACE

#endif /* __QC_MAP_AREA_H__ */
