/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __QC_PROJECTION_HXX__
#define __QC_PROJECTION_HXX__

/**************************************************************************************************/

#include <QDataStream>
#include <QDebug>

/**************************************************************************************************/

// definition of the static member
template <typename Projection>
const Projection QcGeoCoordinateTemplate<Projection>::cls_projection;

template <typename Projection>
QcGeoCoordinateTemplate<Projection>::QcGeoCoordinateTemplate(double x, double y)
  : QcGeoCoordinateTrait()
{
  if (cls_projection.is_valid_xy(x, y)) {
    set_x(x);
    set_y(y);
  } else {
    qQCCritical() << "Invalid coordinate" << cls_projection.srid() << x << y;
    // throw std::invalid_argument("Invalid coordinate");
  }
}

template <typename Projection>
QcGeoCoordinateTemplate<Projection>::QcGeoCoordinateTemplate(const QcVectorDouble & vector)
  : QcGeoCoordinateTemplate(vector.x(), vector.y())
{}

/**************************************************************************************************/

#endif /* __QC_PROJECTION_HXX__ */
