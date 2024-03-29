/****************************************************************************
 **
 ** Copyright (C) 2016 The Qt Company Ltd.
 ** Contact: https://www.qt.io/licensing/
 **
 ** This file is part of the QtPositioning module of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial License Usage
 ** Licensees holding valid commercial Qt licenses may use this file in
 ** accordance with the commercial license agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and The Qt Company. For licensing terms
 ** and conditions see https://www.qt.io/terms-conditions. For further
 ** information use the contact form at https://www.qt.io/contact-us.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 3 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL3 included in the
 ** packaging of this file. Please review the following information to
 ** ensure the GNU Lesser General Public License version 3 requirements
 ** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 2.0 or (at your option) the GNU General
 ** Public license version 3 or any later version approved by the KDE Free
 ** Qt Foundation. The licenses are as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
 ** included in the packaging of this file. Please review the following
 ** information to ensure the GNU General Public License requirements will
 ** be met: https://www.gnu.org/licenses/gpl-2.0.html and
 ** https://www.gnu.org/licenses/gpl-3.0.html.
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

/**************************************************************************************************/

#include "geo_coordinate_animation.h"
#include "qtcarto.h"

#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/*!
  \qmltype CoordinateAnimation
  \instantiates QcGeoCoordinateAnimation
  \inherits PropertyAnimation
  \inqmlmodule QtPositioning
  \since 5.3

  \brief A PropertyAnimation for geo coordinate properties.

  A specialized \l{PropertyAnimation} that defines an animation
  between two \l{coordinate}{coordinates}.

  By default, a \l{latitude} of the \l{coordinate} is animated in the direction of shortest
  (geodesic) distance between those coordinates. Since CoordinateAnimation uses Mercator
  map projection, the \l{latitude} animation is always between -90 and 90 degrees.
  The \l{longitude} animation path is not limited and can go over 180 degrees
  in both west and east directions.

  The \l{direction} property can be set to specify the direction in which the \l{longitude}
  animation should occur.

  \sa {Animation and Transitions in Qt Quick}
*/

/**************************************************************************************************/

/*
QVariant
coordinate_interpolator(const QcWgsCoordinate & from, const QcWgsCoordinate & to, qreal progress)
{
  if (from == to) { // ???
    if (progress < 0.5)
      return QVariant::fromValue(from);
    else
      return QVariant::fromValue(to);
  }

  QcWgsCoordinate result = QGeoProjection::coordinateInterpolation(from, to, progress);

  return QVariant::fromValue(result);
}
*/

/**************************************************************************************************/

// Fixme: qt -> wgs84 -> normalised_web_mercator -> qt
// use Qc implementation and cache normalised_web_mercator in wgs84
// or use normalised_web_mercator

QVariant
coordinate_shortest_interpolator(const QcWgsCoordinate & _from, const QcWgsCoordinate & _to, qreal progress)
{
  QcNormalisedWebMercatorCoordinate from = _from.normalised_web_mercator();
  QcNormalisedWebMercatorCoordinate to = _to.normalised_web_mercator();

  double to_x = to.x();
  double to_y = to.y();
  double from_x = from.x();
  double from_y = from.y();
  double delta_x = to_x - from_x;
  double delta_y = to_y - from_y;

  /*
   * a) Two cases : |f - t| <= 1/2 or > 1/2
   * if > 1/2 then it is shorter to cross the date line
   *   b) Two cases
   *    |--f   t<-| (3)
   *    |->t   f--| (4)
   */

  double x;
  double delta_x_abs = qAbs(delta_x);
  if (delta_x_abs > 0.5) { // case b
    double dx = 1 - delta_x_abs;
    if (from_x < to_x) { // case 3 <-|-
      x = from_x - dx * progress;
      if (x < 0.0) // we crossed date line
        x += 1.0;
    } else { // case 4 -|->
      x = from_x + dx * progress;
      if (x > 1.0) // we crossed date line
        x -= 1.0;
    }
  } else
    x = from_x + delta_x * progress;

  double y = from_y + delta_y * progress;

  QcWgsCoordinate coordinate = QcNormalisedWebMercatorCoordinate(x, y).wgs84();
  // qQCInfo() << progress << coordinate;
  return QVariant::fromValue(coordinate);
}

QVariant
coordinate_west_interpolator(const QcWgsCoordinate & from, const QcWgsCoordinate & to, qreal progress)
{
  if (progress == .0)
    return QVariant::fromValue(from);
  else if (progress == 1.)
    return QVariant::fromValue(to);
  else if (from == to)
    return QVariant::fromValue(from);

  double to_x = to.x();
  double to_y = to.y();
  double from_x = from.x();
  double from_y = from.y();
  double delta_x = to_x - from_x;
  double delta_y = to_y - from_y;

  // <-|-
  if (from_x < to_x)
    delta_x = 360. - delta_x;
  double delta_x_abs = qAbs(delta_x);
  double x = from_x - delta_x_abs * progress;
  if (x < -180.) // we crossed date line
    x += 360.;

  double y = from_y + delta_y * progress;

  return QVariant::fromValue(QcWgsCoordinate(x, y));
}

QVariant
coordinate_east_interpolator(const QcWgsCoordinate & from, const QcWgsCoordinate & to, qreal progress)
{
  if (progress == .0)
    return QVariant::fromValue(from);
  else if (progress == 1.)
    return QVariant::fromValue(to);
  else if (from == to)
    return QVariant::fromValue(from);

  double to_x = to.x();
  double to_y = to.y();
  double from_x = from.x();
  double from_y = from.y();
  double delta_x = to_x - from_x;
  double delta_y = to_y - from_y;

  // -|->
  if (to_x < from_x)
    delta_x = 360. + delta_x;
  double delta_x_abs = qAbs(delta_x);
  double x = from_x + delta_x_abs * progress;
  if (x > 180.) // we crossed date line
    x -= 360.;

  double y = from_y + delta_y * progress;

  return QVariant::fromValue(QcWgsCoordinate(x, y));
}

/**************************************************************************************************/

QcGeoCoordinateAnimationPrivate::QcGeoCoordinateAnimationPrivate()
  : m_direction(QcGeoCoordinateAnimation::Shortest)
{
}

/**************************************************************************************************/

QcGeoCoordinateAnimation::QcGeoCoordinateAnimation(QObject * parent)
  : QQuickPropertyAnimation(*(new QcGeoCoordinateAnimationPrivate), parent) // ctor prototype ??? when deleted ???
{
  Q_D(QcGeoCoordinateAnimation);
  d->interpolatorType = qMetaTypeId<QcWgsCoordinate>();
  d->defaultToInterpolatorType = true;
  d->interpolator = QVariantAnimationPrivate::getInterpolator(d->interpolatorType);
}

QcGeoCoordinateAnimation::~QcGeoCoordinateAnimation()
{}

/*!
  \qmlproperty coordinate CoordinateAnimation::from
  This property holds the coordinate where the animation should begin.
*/
QcWgsCoordinate
QcGeoCoordinateAnimation::from() const
{
  Q_D(const QcGeoCoordinateAnimation);
  return d->from.value<QcWgsCoordinate>();
}

void QcGeoCoordinateAnimation::setFrom(const QcWgsCoordinate & from)
{
  QQuickPropertyAnimation::setFrom(QVariant::fromValue(from));
}

/*!
  \qmlproperty coordinate CoordinateAnimation::to
  This property holds the coordinate where the animation should end.
*/
QcWgsCoordinate
QcGeoCoordinateAnimation::to() const
{
  Q_D(const QcGeoCoordinateAnimation);
  return d->to.value<QcWgsCoordinate>();
}

void
QcGeoCoordinateAnimation::setTo(const QcWgsCoordinate & to)
{
  QQuickPropertyAnimation::setTo(QVariant::fromValue(to));
}

/*!
  \qmlproperty enumeration CoordinateAnimation::direction
  This property holds the direction of the \l{longitude} animation of the \l{coordinate}.

  Possible values are:

  \list
  \li CoordinateAnimation.Shortest (default) - the longitude animation goes in the direction
  that produces the shortest animation path.
  \li CoordinateAnimation.West - the longitude animation always goes into western direction
  and may cross the date line.
  \li CoordinateAnimation.East - the longitude animation always goes into eastern direction
  and may cross the date line.
  \endlist
  \since 5.5
*/

QcGeoCoordinateAnimation::Direction
QcGeoCoordinateAnimation::direction() const
{
  Q_D(const QcGeoCoordinateAnimation);
  return d->m_direction;
}

void
QcGeoCoordinateAnimation::setDirection(QcGeoCoordinateAnimation::Direction direction)
{
  // qQCInfo() << direction;
  Q_D(QcGeoCoordinateAnimation);
  if (d->m_direction == direction)
    return;

  // Fixme: <-map- direction is west
  d->m_direction = direction;
  switch (direction) {
    // case West:
  case East:
    d->interpolator = reinterpret_cast<QVariantAnimation::Interpolator>(&coordinate_west_interpolator);
    break;
    // case East:
  case West:
    d->interpolator = reinterpret_cast<QVariantAnimation::Interpolator>(&coordinate_east_interpolator);
    break;
  case Shortest:
  default:
    d->interpolator = reinterpret_cast<QVariantAnimation::Interpolator>(&coordinate_shortest_interpolator);
    break;
  }

  emit directionChanged();
}

// QC_END_NAMESPACE
