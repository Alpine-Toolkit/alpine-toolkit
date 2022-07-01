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

#ifndef __QC_MERCATOR_H__
#define __QC_MERCATOR_H__

/**************************************************************************************************/

#include "earth.h"
#include "coordinate/projection.h"

// #include <QtCore/QMetaType>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QDebug;
class QDataStream;

class QcWgsCoordinate;
class QcWebMercatorCoordinate;
class QcPseudoWebMercatorCoordinate;
class QcNormalisedWebMercatorCoordinate;

/**************************************************************************************************/

/// The QcWebMercatorProjection class implements the Web Mercator projection (EPSG:3857).
class QC_EXPORT QcWebMercatorProjection : public QcProjection
{
 public:
  // argmax(x) = 20037508.342789244 = pi * EQUATORIAL_RADIUS = pi * 6378137
  // argmax(y) = argmax(x)
  // argmax(latitude) is computed for y(latitude max) = pi * EQUATORIAL_RADIUS
  // argmax(latitude) = 2*atan(exp(pi)) - pi/2 = 85.051 128 779 806 6
  //                  = math.degrees(2*math.atan(math.exp(math.pi)) - math.pi/2)
  // It is the latitude at which the full projected map becomes a square.
  static constexpr double LATITUDE_MAX = 85.0511287798060;

 public:
  QcWebMercatorProjection()
    : QcProjection(QStringLiteral("epsg:3857"),
                   QStringLiteral("Web Mercator"),
                   QcVectorDouble(0, 0),
                   // QcVectorDouble(0, 180), // X towards E
                   // QcVectorDouble(0, 90), // Y towards N
                   QcInterval2DDouble(-180, 180,
                                      -LATITUDE_MAX, LATITUDE_MAX),
                   QcInterval2DDouble(-HALF_EQUATORIAL_PERIMETER, HALF_EQUATORIAL_PERIMETER,
                                      -HALF_EQUATORIAL_PERIMETER, HALF_EQUATORIAL_PERIMETER,
                   QStringLiteral("m"),
                   ProjectionSurface::Cylindrical,
                   PreserveBit::PreserveDirection)
    {}
};


/// The QcWebMercatorCoordinate class implements a Web Mercator coordinate (EPSG:3857).
class QC_EXPORT QcWebMercatorCoordinate : public QcGeoCoordinateTemplate<QcWebMercatorProjection>
{
  Q_GADGET;

  Q_PROPERTY(double x READ y WRITE set_x)
  Q_PROPERTY(double y READ x WRITE set_y)
  Q_PROPERTY(bool is_valid READ is_valid)

 public:
  QcWebMercatorCoordinate();
  QcWebMercatorCoordinate(double x, double y);

  QcWgsCoordinate wgs84() const;
  QcPseudoWebMercatorCoordinate pseudo_web_mercator() const;
  QcNormalisedWebMercatorCoordinate normalised_web_mercator() const;
};

// Q_DECLARE_TYPEINFO(QcWebMercatorCoordinate, Q_MOVABLE_TYPE);

/**************************************************************************************************/

/// The QcPseudoMercatorProjection class implements the Pseudo Web Mercator projection.
///
/// This projection is translated so as to map the screen referential:
///
/// \f[
/// \begin{align}
///   x\prime &= x + \frac{\mathtext{EQUATORIAL PERIMETER}}{2}; \\
///   y\prime &= \frac{\mathtext{EQUATORIAL PERIMETER}}{2} - y
/// \end{align}
/// \f]
///
/// The x axis point to the east and the y axis to the south like for the screen referential.
/// And the Alaska (x < 0, y > 0) is below and close to the origin.
class QC_EXPORT QcPseudoMercatorProjection : public QcProjection
{
 public:
  QcPseudoMercatorProjection()
    : QcProjection(QStringLiteral("pseudo-mercator"), // Fxime: name ???
                   QStringLiteral("Pseudo Web Mercator"),
                   QcVectorDouble(0, 0),
                   // QcVectorDouble(0, 180), // X towards E
                   // QcVectorDouble(0, 90), // Y towards N
                   QcInterval2DDouble(-180, 180,
                                      -QcWebMercatorProjection::LATITUDE_MAX, QcWebMercatorProjection::LATITUDE_MAX),
                   QcInterval2DDouble(0, EQUATORIAL_PERIMETER,
                                      0, EQUATORIAL_PERIMETER),
                   QStringLiteral("m"),
                   ProjectionSurface::Cylindrical,
                   PreserveBit::PreserveDirection,
                   false)
    {}
};


/// The QcPseudoWebMercatorCoordinate class implements a Pseudo Web Mercator coordinate.
class QC_EXPORT QcPseudoWebMercatorCoordinate : public QcGeoCoordinateTemplate<QcPseudoMercatorProjection>
{
  Q_GADGET;

  Q_PROPERTY(double x READ y WRITE set_x)
  Q_PROPERTY(double y READ x WRITE set_y)
  Q_PROPERTY(bool is_valid READ is_valid)

 public:
  QcPseudoWebMercatorCoordinate();
  QcPseudoWebMercatorCoordinate(double x, double y);

  QcWgsCoordinate wgs84() const;
  QcWebMercatorCoordinate web_mercator() const;
  QcNormalisedWebMercatorCoordinate normalised_web_mercator() const;
};

// Q_DECLARE_TYPEINFO(QcPseudoWebMercatorCoordinate, Q_MOVABLE_TYPE);

/**************************************************************************************************/

/// The QcNormalisedMercatorProjection class implements a Normalised Web Mercator projection.
///
/// Normalised WebMercator coordinate lies in [0, 1] interval in the web mercator rest frame.
/// This normalised coordinate can be converted to a matrix index by multiplying by 2^level.
class QC_EXPORT QcNormalisedMercatorProjection : public QcProjection
{
 public:
  QcNormalisedMercatorProjection()
    : QcProjection(QStringLiteral("normalised-mercator"),
                   QStringLiteral("Normalised Web Mercator"),
                   QcVectorDouble(0, 0),
                   // QcVectorDouble(0, 180), // X towards E
                   // QcVectorDouble(0, 90), // Y towards N
                   QcInterval2DDouble(-180, 180,
                                      -QcWebMercatorProjection::LATITUDE_MAX, QcWebMercatorProjection::LATITUDE_MAX),
                   QcInterval2DDouble(0, 1, 0, 1),
                   QStringLiteral("m"),
                   ProjectionSurface::Cylindrical,
                   PreserveBit::PreserveDirection,
                   false)
    {}
};


/// The QcNormalisedWebMercatorCoordinate class implements a Normalised Web Mercator coordinate.
class QC_EXPORT QcNormalisedWebMercatorCoordinate : public QcGeoCoordinateTemplate<QcNormalisedMercatorProjection>
{
  Q_GADGET;

  Q_PROPERTY(double x READ y WRITE set_x)
  Q_PROPERTY(double y READ x WRITE set_y)
  Q_PROPERTY(bool is_valid READ is_valid)

 public:
  QcNormalisedWebMercatorCoordinate();
  QcNormalisedWebMercatorCoordinate(double x, double y);

  QcWgsCoordinate wgs84() const;
  QcWebMercatorCoordinate web_mercator() const;
  QcPseudoWebMercatorCoordinate pseudo_web_mercator() const;
};

// Q_DECLARE_TYPEINFO(QcNormalisedWebMercatorCoordinate, Q_MOVABLE_TYPE);

/**************************************************************************************************/

// QC_END_NAMESPACE

// Q_DECLARE_METATYPE(QcWebMercatorCoordinate)
// Q_DECLARE_METATYPE(QcPseudoWebMercatorCoordinate)
// Q_DECLARE_METATYPE(QcNormalisedWebMercatorCoordinate)

/**************************************************************************************************/

#endif /* __QC_MERCATOR_H__ */
