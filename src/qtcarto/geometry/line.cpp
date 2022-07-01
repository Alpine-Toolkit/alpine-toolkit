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

#include "line.h"
#include "qtcarto.h"

/**************************************************************************************************/

#ifndef QT_NO_DEBUG_STREAM
QC_EXPORT QDebug operator<<(QDebug debug, const QcLineDouble & line)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace() << "QcLineDouble(";
  debug << line.point();
  debug << ", ";
  debug << line.vector();
  debug << ')';

  return debug;
}
#endif

/**************************************************************************************************/

// QC_END_NAMESPACE
