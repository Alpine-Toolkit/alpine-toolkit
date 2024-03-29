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

#include "vector.h"
#include "qtcarto.h"

/**************************************************************************************************/

const QString separator = ", ";

// Fixme: duplicated code

#ifndef QT_NO_DEBUG_STREAM
QC_EXPORT QDebug operator<<(QDebug debug, const QcVectorDouble & vector)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace() << QStringLiteral("QcVectorDouble(");
  debug << vector.x();
  debug << separator;
  debug << vector.y();
  debug << ')';

  return debug;
}
#endif

#ifndef QT_NO_DEBUG_STREAM
QC_EXPORT QDebug operator<<(QDebug debug, const QcVector3DDouble & vector)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace() << QStringLiteral("QcVector3DDouble(");
  debug << vector.x();
  debug << separator;
  debug << vector.y();
  debug << separator;
  debug << vector.z();
  debug << ')';

  return debug;
}
#endif

#ifndef QT_NO_DEBUG_STREAM
QC_EXPORT QDebug operator<<(QDebug debug, const QcVector4DDouble & vector)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace() << QStringLiteral("QcVector4DDouble(");
  debug << vector.x();
  debug << separator;
  debug << vector.y();
  debug << separator;
  debug << vector.z();
  debug << separator;
  debug << vector.t();
  debug << ')';

  return debug;
}
#endif
