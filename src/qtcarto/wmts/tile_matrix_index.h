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

#ifndef TILE_MATRIX_INDEX_H
#define TILE_MATRIX_INDEX_H

/**************************************************************************************************/

#include <QDebug>

#include "qtcarto_global.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/// The QcTileMatrixIndex class implements a tile matrix index.
/// A tile matrix index is a pair (x, y).
class QC_EXPORT QcTileMatrixIndex
{
 public:
  QcTileMatrixIndex();
  QcTileMatrixIndex(int x, int y);
  QcTileMatrixIndex(const QcTileMatrixIndex & other);
  ~QcTileMatrixIndex();

  QcTileMatrixIndex &operator=(const QcTileMatrixIndex & other);

  bool operator==(const QcTileMatrixIndex & other) const;
  // Fixme: auto generated
  inline bool operator!=(const QcTileMatrixIndex & other) const {
    return !operator==(other);
  }

  inline void set_x(int x) {
    m_x = x;
  }
  inline int x() const {
    return m_x;
  }

  inline void set_y(int y) {
    m_y = y;
  }
  inline int y() const {
    return m_y;
  }

 private:
  int m_x; // column
  int m_y; // row
};

#ifndef QT_NO_DEBUG_STREAM
QC_EXPORT QDebug operator<<(QDebug debug, const QcTileMatrixIndex & tile_index);
#endif

/**************************************************************************************************/

#endif // TILE_MATRIX_INDEX_H
