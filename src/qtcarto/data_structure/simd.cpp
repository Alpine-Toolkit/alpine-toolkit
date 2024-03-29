/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $QTCARTO_END_LICENSE$
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
