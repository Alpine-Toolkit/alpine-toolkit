/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "map_area.h"
#include "qtcarto.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

QcMapArea::QcMapArea()
  : m_polygon()
{}

QcMapArea::~QcMapArea()
{}

void
QcMapArea::clear()
{
  m_polygon.clear();
}

void
QcMapArea::add_vertex(QcVectorDouble vertex)
{
  // Fixme: check self intersection
  m_polygon.add_vertex(vertex);
}

// QC_END_NAMESPACE
