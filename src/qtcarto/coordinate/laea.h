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

#ifndef __QC_LAEA_H__
#define __QC_LAEA_H__

/**************************************************************************************************/

#include "earth.h"
#include "coordinate/projection.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcWgsCoordinate;

/**************************************************************************************************/

/*! Lambert Azimuthal Equal-Area (LAEA) Projection
 *
 */

/*!
 * http://epsg.io/3571
 *
 * Unit: metre
 * Geodetic CRS: WGS 84
 * Datum: World Geodetic System 1984
 * Ellipsoid: WGS 84
 * Prime meridian: Greenwich
 * Data source: OGP
 * Scope: Arctic research.
 * Remarks: For studies of Bering Sea area.
 * Area of use: Northern hemisphere - north of 45°N, including Arctic.
 * Coordinate system: Cartesian 2D CS for north polar azimuthal lonO 180°E. Axes: X,Y. Orientations: X along 90°W, Y along 0°E meridians. UoM: m.
 * Center coordinates 0.00 2768558.07
 * Projected bounds:
 *   8533.49 -4889327.36
 *   -974.38 -558277.56
 * WGS84 bounds:
 *   -180.0 45.0
 *    180.0 90.0
 *
 * Northern hemisphere - north of 45°N, including Arctic.
 */
class QC_EXPORT QcLaeaProjection_3571 : public QcProjection // LaeaProjection
{
 public:
  QcLaeaProjection_3571()
    : QcProjection(QStringLiteral("epsg:3571"),
                   QStringLiteral("North Pole LAEA Bering Sea"),
                   QcVectorDouble(180, 90),
                   // QcVector2DDouble(90, 0), // X along 90°W
                   // QcVector2DDouble(0, 0), // Y along 0°E
                   QcInterval2DDouble(-180, 180,
                                      45, 90),
                   QcInterval2DDouble(-HALF_EQUATORIAL_PERIMETER, HALF_EQUATORIAL_PERIMETER,
                                      -HALF_EQUATORIAL_PERIMETER, HALF_EQUATORIAL_PERIMETER),
                   QStringLiteral("m"),
                   ProjectionSurface::Azimuthal,
                   PreserveBit::PreserveArea)
    {}
};

/**************************************************************************************************/

/*
class QC_EXPORT QcLaeaCoordinate_3571 : public QcGeoCoordinateTemplate<QcLaeaProjection_3571>
{
  Q_GADGET;

  Q_PROPERTY(double x READ y WRITE set_x)
  Q_PROPERTY(double y READ x WRITE set_y)
  Q_PROPERTY(bool is_valid READ is_valid)

 public:
  QcLaeaProjection_3571();
  QcLaeaProjection_3571(double x, double y);
};
*/

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_LAEA_H__ */
