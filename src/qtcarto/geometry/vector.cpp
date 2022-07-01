/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
