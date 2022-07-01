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

#ifndef __QC_TILE_SPEC_H__
#define __QC_TILE_SPEC_H__

/**************************************************************************************************/

#include <QSharedDataPointer>
#include <QString>
#include <QtCore/QMetaType>

#include "qtcarto_global.h"
#include "wmts/tile_matrix_index.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QC_EXPORT QcTileSpec : public QcTileMatrixIndex
{
 public:
  QcTileSpec();
  QcTileSpec(const QcTileSpec & other);
  QcTileSpec(const QString & plugin, int map_id, int level, int x, int y);
  ~QcTileSpec();

  QcTileSpec & operator=(const QcTileSpec & other);

  inline const QString & plugin() const {
    return m_plugin;
  }
  void set_plugin(const QString & plugin) {
    m_plugin = plugin;
  }

  int level() const {
    return m_level;
  }
  inline void set_level(int level) {
    m_level = level;
  }

  int map_id() const {
    return m_map_id;
  }
  void set_map_id(int map_id) {
    m_map_id = map_id;
  }

  bool operator==(const QcTileSpec & rhs) const;
  // bool operator<(const QcTileSpec & rhs) const;

 private:
  QString m_plugin;
  int m_map_id;
  int m_level;
};

QC_EXPORT unsigned int qHash(const QcTileSpec & tile_spec);

QC_EXPORT QDebug operator<<(QDebug, const QcTileSpec & tile_spec);

typedef QSet<QcTileSpec> QcTileSpecSet;

// QC_END_NAMESPACE

Q_DECLARE_METATYPE(QcTileSpec)
// Q_DECLARE_METATYPE(QcTileSpecSet)

#endif /* __QC_TILE_SPEC_H__ */
