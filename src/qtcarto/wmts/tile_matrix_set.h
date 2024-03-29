// -*- mode: c++ -*-

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

#ifndef __QC_TILE_MATRIX_SET_H__
#define __QC_TILE_MATRIX_SET_H__

/**************************************************************************************************/

#include "qtcarto_global.h"
#include "coordinate/projection.h"
#include "coordinate/wgs84.h"
#include "earth.h"
#include "geometry/vector.h"
#include "wmts/tile_matrix_index.h"

#include <QtCore/QMetaType>
#include <QDebug>
#include <QString>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcTileMatrix;
class QcTileMatrixSet;

/**************************************************************************************************/

/*
class QC_EXPORT QcTileMatrixSetIterator
{
 public:
  QcTileMatrixSetIterator (const QcTileMatrixSet * tile_matrix_set, int position);

  inline bool operator!= (const QcTileMatrixSetIterator & other) const {
    return m_position != other.m_position;
  }

  inline const QcTileMatrixSetIterator & operator++ () {
    ++m_position;
    return *this;
  }

  const QcTileMatrix & operator* () const;

 private:
  int m_position;
  const QcTileMatrixSet * m_tile_matrix_set;
};
*/

/**************************************************************************************************/

class QC_EXPORT QcTileMatrixSet
{
 public:
  static double resolution_for_level(double map_size, int tile_size, int zoom_level);

 public:
  QcTileMatrixSet(const QcProjection * projection,
                  const QcVectorDouble & origin,
                  const QcVectorDouble & scale,
                  const QcWgsCoordinate & default_center,
                  int number_of_level, // Fixme: can be an interval instead
                  int tile_size);

  inline const QcProjection & projection() const { return *m_projection; }

  const QcVectorDouble & origin() const { return m_origin; }
  const QcVectorDouble & scale() const { return m_scale; }

  inline const QcWgsCoordinate & default_center() const { return m_default_center; }

  inline int number_of_levels() const { return m_number_of_levels; }

  // unit [px]
  inline int tile_size() const { return m_tile_size; }

  // unit [m/px]
  inline double root_resolution() const { return m_root_resolution; }

  // Return the resolution of the given level [m/px].
  inline double level_resolution(int level) const {
    return m_root_resolution / double(1 << level);
  }

  // Return the smallest available resolution.
  inline double smallest_resolution() const {
    return level_resolution(m_number_of_levels -1);
  }

  // Return the closest level for the given resolution.
  int closest_level(double resolution) const;

  inline const QcTileMatrix & operator[](int level) const {
    return m_tile_matrix_set[level];
  };

  const QVector<QcTileMatrix> levels() const { return m_tile_matrix_set; }

  /*
  QcTileMatrixSetIterator begin() const {
    return QcTileMatrixSetIterator(this,  0);
  }

  QcTileMatrixSetIterator end() const {
    return QcTileMatrixSetIterator(this, m_number_of_levels);
  }
  */

 private:
  const QcProjection * m_projection;
  QcVectorDouble m_origin;
  QcVectorDouble m_scale;
  QcWgsCoordinate m_default_center;
  // Bounds of the CRS, in projected coordinates
  int m_number_of_levels; // Fixme: could be a subset
  int m_tile_size;
  double m_root_resolution;
  QVector<QcTileMatrix> m_tile_matrix_set;
};

/**************************************************************************************************/

class QC_EXPORT QcTileMatrix
{
 public:
  QcTileMatrix();
  QcTileMatrix(QcTileMatrixSet * tile_matrix_set, int level);
  QcTileMatrix(const QcTileMatrix & other);

  inline const QcTileMatrixSet & tile_matrix_set() const { return *m_tile_matrix_set; }

  // pyramid level
  inline int level() const { return m_level; }

  // Size of the mosaic, unit [tile]
  inline int mosaic_size() const { return m_mosaic_size; }

  inline double resolution() const { return m_resolution; }

  inline double tile_length_m() const { return m_tile_length_m; }

  // unit [px]
  inline int tile_size() const { return m_tile_matrix_set->tile_size(); }

  QcTileMatrixIndex to_matrix_index(const QcVectorDouble & coordinate) const;
  // QcTileMatrixIndex to_matrix_index(const QcVectorDouble & coordinate) const; // normalised

 private:
  QcTileMatrixIndex _to_matrix_index_check(const QcVectorDouble & coordinate) const;

 private:
  QcTileMatrixSet * m_tile_matrix_set;
  int m_level;
  int m_mosaic_size;
  double m_resolution;
  double m_tile_length_m;
};

/**************************************************************************************************/

class QC_EXPORT QcMercatorTileMatrixSet : public QcTileMatrixSet
{
 public:
  QcMercatorTileMatrixSet(int number_of_level, int tile_size)
    : QcTileMatrixSet(QcProjection::by_srid(QStringLiteral("epsg:3857")),
                      QcVectorDouble(-HALF_EQUATORIAL_PERIMETER, HALF_EQUATORIAL_PERIMETER), // Fixme: use projection
                      QcVectorDouble(1., -1.),
                      QcWgsCoordinate(.0, .0), // Fixme: use projection
                      number_of_level,
                      tile_size
                      )
    {}
};

/**************************************************************************************************/

// QT_END_NAMESPACE

/**************************************************************************************************/

#endif // __QC_TILE_MATRIX_SET_H__
