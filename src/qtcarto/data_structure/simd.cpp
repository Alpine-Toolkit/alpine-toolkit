/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "simd.h"
#include "qtcarto.h"

/**************************************************************************************************/

#ifndef QT_NO_DEBUG_STREAM
QC_EXPORT QDebug operator<<(QDebug debug, const QcSimdPairDouble & simd)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace() << QStringLiteral("QcSimdDouble(");
  debug << simd.x();
  debug << QStringLiteral(", ");
  debug << simd.y();
  debug << ')';

  return debug;
}
#endif

#ifndef QT_NO_DEBUG_STREAM
QC_EXPORT QDebug operator<<(QDebug debug, const QcSimdTripletDouble & simd)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace() << QStringLiteral("QcSimd3DDouble(");
  debug << simd.x();
  debug << QStringLiteral(", ");
  debug << simd.y();
  debug << QStringLiteral(", ");
  debug << simd.z();
  debug << ')';

  return debug;
}
#endif
