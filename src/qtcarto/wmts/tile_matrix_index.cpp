/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "tile_matrix_index.h"
#include "qtcarto.h"

/**************************************************************************************************/

QcTileMatrixIndex::QcTileMatrixIndex(int x, int y)
  : m_x(x), m_y(y)
{}

QcTileMatrixIndex::QcTileMatrixIndex()
  : QcTileMatrixIndex(0, 0)
{}

QcTileMatrixIndex::QcTileMatrixIndex(const QcTileMatrixIndex & other)
  : QcTileMatrixIndex(other.m_x, other.m_y)
{
}

QcTileMatrixIndex::~QcTileMatrixIndex()
{}

QcTileMatrixIndex &
QcTileMatrixIndex::operator=(const QcTileMatrixIndex & other)
{
  if (this != &other) {
    m_x = other.m_x;
    m_y = other.m_y;
  }

  return *this;
}

bool
QcTileMatrixIndex::operator==(const QcTileMatrixIndex & other) const
{
  return m_x == other.m_x and m_y == other.m_y;
}

#ifndef QT_NO_DEBUG_STREAM
QC_EXPORT QDebug operator<<(QDebug debug, const QcTileMatrixIndex & tile_index)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace() << "QcTileMatrixIndex(";
  debug << tile_index.x();
  debug << ", ";
  debug << tile_index.y();
  debug << ')';

  return debug;
}
#endif
