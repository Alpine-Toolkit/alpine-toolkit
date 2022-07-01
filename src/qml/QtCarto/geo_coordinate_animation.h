// -*- mode: c++ -*-

/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtPositioning module of the Qt Toolkit.
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) None Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
****************************************************************************/

// cf. qtlocation/src/imports/positioning/qquickgeocoordinateanimation_p.h

/**************************************************************************************************/

#ifndef __GEO_COORDINATE_ANIMATION_H__
#define __GEO_COORDINATE_ANIMATION_H__

/**************************************************************************************************/

// #include <QGeoCoordinate>
#include "coordinate/mercator.h"
#include "coordinate/wgs84.h"

// Fixme: Use QtQuick Private API !!!
#include <private/qquickanimation_p.h>
#include <private/qquickanimation_p_p.h>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QVariant coordinate_east_interpolator(const QcWgsCoordinate & from, const QcWgsCoordinate & to, qreal progress);
QVariant coordinate_west_interpolator(const QcWgsCoordinate & from, const QcWgsCoordinate & to, qreal progress);

QVariant coordinate_shortest_interpolator(const QcWgsCoordinate & from, const QcWgsCoordinate & to, qreal progress);

/**************************************************************************************************/

class QcGeoCoordinateAnimationPrivate;

class QcGeoCoordinateAnimation : public QQuickPropertyAnimation
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(QcGeoCoordinateAnimation)
  Q_PROPERTY(QcWgsCoordinate from READ from WRITE setFrom)
  Q_PROPERTY(QcWgsCoordinate to READ to WRITE setTo)
  Q_PROPERTY(Direction direction READ direction WRITE setDirection NOTIFY directionChanged)

public:
  enum Direction {
    Shortest,
    West,
    East
  };
  Q_ENUM(Direction)

  QcGeoCoordinateAnimation(QObject * parent = 0);
  ~QcGeoCoordinateAnimation();

  QcWgsCoordinate from() const;
  void setFrom(const QcWgsCoordinate &);

  QcWgsCoordinate to() const;
  void setTo(const QcWgsCoordinate &);

  Direction direction() const;
  void setDirection(Direction direction);

signals:
  void directionChanged();
};

class QcGeoCoordinateAnimationPrivate : public QQuickPropertyAnimationPrivate
{
  Q_DECLARE_PUBLIC(QcGeoCoordinateAnimation)

public:
  QcGeoCoordinateAnimationPrivate();
  QcGeoCoordinateAnimation::Direction m_direction;
};

// QVariant coordinate_interpolator(const QcWgsCoordinate & from, const QcWgsCoordinate & to, qreal progress);

// QC_END_NAMESPACE

QML_DECLARE_TYPE(QcGeoCoordinateAnimation)

#endif // __GEO_COORDINATE_ANIMATION_H__
