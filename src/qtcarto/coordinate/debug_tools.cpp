/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "debug_tools.h"
#include "qtcarto.h"

#include "wgs84.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QString
format_interval(const QcInterval2DDouble & interval, const QcProjection * projection)
{
  const QcIntervalDouble & x = interval.x();
  const QcIntervalDouble & y = interval.y();

  QcGeoCoordinate wgs84_inf; // Fixme: radians !
  try {
    QcGeoCoordinate inf(projection, x.inf(), y.inf());
    wgs84_inf = inf.transform(&QcWgsCoordinate::cls_projection); // Fixme: radians !
  } catch(...) {
  }
  QcGeoCoordinate wgs84_sup;
  try {
    QcGeoCoordinate sup(projection, x.sup(), y.sup());
    wgs84_sup = sup.transform(&QcWgsCoordinate::cls_projection);
  } catch(...) {
  }

  QString message =
    '[' + QString::number(x.inf(), 'f', 2) + QStringLiteral(", ") + QString::number(x.sup(), 'f', 2) + QStringLiteral("]") +
    QStringLiteral(" x ") +
    '[' + QString::number(y.inf(), 'f', 2) + QStringLiteral(", ") + QString::number(y.sup(), 'f', 2) + QStringLiteral("]") +
    QStringLiteral("   ")  +
    '[' + QString::number(wgs84_inf.x(), 'f', 2) + QStringLiteral(", ") + QString::number(wgs84_sup.x(), 'f', 2) + QStringLiteral("]") +
    QStringLiteral(" x ")  +
    '[' + QString::number(wgs84_inf.y(), 'f', 2) + QStringLiteral(", ") + QString::number(wgs84_sup.y(), 'f', 2) + QStringLiteral("]");
  return message;
}

/**************************************************************************************************/

// QC_END_NAMESPACE
