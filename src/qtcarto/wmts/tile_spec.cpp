/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) None Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
****************************************************************************/

/**************************************************************************************************/

#include "tile_spec.h"
#include "qtcarto.h"

#include <QtCore/QDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

QcTileSpec::QcTileSpec()
  : QcTileMatrixIndex(),
    m_plugin(), m_map_id(-1), m_level(-1)
{}

QcTileSpec::QcTileSpec(const QString & plugin, int map_id, int level, int x, int y)
  : QcTileMatrixIndex(x, y),
    m_plugin(plugin), m_map_id(map_id), m_level(level)
{}

QcTileSpec::QcTileSpec(const QcTileSpec & other)
  : QcTileMatrixIndex(other),
    m_plugin(other.m_plugin), m_map_id(other.m_map_id), m_level(other.m_level)
{}

QcTileSpec::~QcTileSpec()
{}

QcTileSpec &
QcTileSpec::operator=(const QcTileSpec & other)
{
  if (this != &other) {
    QcTileMatrixIndex::operator=(other);
    m_plugin = other.m_plugin;
    m_map_id = other.m_map_id;
    m_level = other.m_level;
  }

  return *this;
}

bool
QcTileSpec::operator==(const QcTileSpec & rhs) const
{
  return (QcTileMatrixIndex::operator==(rhs)
	  and m_plugin == rhs.m_plugin
	  and m_map_id == rhs.m_map_id
	  and m_level == rhs.m_level);
}

/*
bool QcTileSpec::operator<(const QcTileSpec & rhs) const
{
  if (plugin_ < rhs.plugin_)
    return true;
  if (plugin_ > rhs.plugin_)
    return false;

  if (mapId_ < rhs.mapId_)
    return true;
  if (mapId_ > rhs.mapId_)
    return false;

  if (zoom_ < rhs.zoom_)
    return true;
  if (zoom_ > rhs.zoom_)
    return false;

  if (x_ < rhs.x_)
    return true;
  if (x_ > rhs.x_)
    return false;

  if (y_ < rhs.y_)
    return true;
  if (y_ > rhs.y_)
    return false;

  return (version_ < rhs.version_);
}
*/

unsigned int
qHash(const QcTileSpec & tile_spec)
{
  // 31 is coded on 5-bit
  unsigned int result = (qHash(tile_spec.plugin()) * 13) % 31;
  result += ((tile_spec.map_id() * 17) % 31) << 5;
  result += ((tile_spec.level() * 19) % 31) << 10;
  result += ((tile_spec.x() * 23) % 31) << 15;
  result += ((tile_spec.y() * 29) % 31) << 20;
  // QString filename = tile_spec.plugin();
  // filename += QStringLiteral("-");
  // filename += QString::number(tile_spec.map_id());
  // filename += QStringLiteral("-");
  // filename += QString::number(tile_spec.level());
  // filename += QStringLiteral("-");
  // filename += QString::number(tile_spec.x());
  // filename += QStringLiteral("-");
  // filename += QString::number(tile_spec.y());
  // unsigned int result = qHash(filename);
  return result;
}

QDebug
operator<<(QDebug debug, const QcTileSpec & tile_spec)
{
  // Fixme: litteral, arg OR s <<
  QString s = tile_spec.plugin();
  s += QStringLiteral("-");
  s += QString::number(tile_spec.map_id());
  s += QStringLiteral("-");
  s += QString::number(tile_spec.level());
  s += QStringLiteral("-");
  s += QString::number(tile_spec.x());
  s += QStringLiteral("-");
  s += QString::number(tile_spec.y());
  debug << s;
  return debug;
}

// QC_END_NAMESPACE
