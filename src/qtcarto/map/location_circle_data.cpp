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

#include "location_circle_data.h"
#include "qtcarto.h"

#include <QtDebug>

/**************************************************************************************************/

QcLocationCircleData::QcLocationCircleData(QObject * parent)
  : QObject(parent),
    m_visible(false),
    m_coordinate(),
    m_bearing(),
    m_horizontal_precision()
{}

QcLocationCircleData::QcLocationCircleData(const QcLocationCircleData & other, QObject * parent)
  : QObject(parent),
    m_visible(other.m_visible),
    m_coordinate(other.m_coordinate),
    m_bearing(other.m_bearing),
    m_horizontal_precision(other.m_horizontal_precision)
{}

QcLocationCircleData::~QcLocationCircleData()
{}

QcLocationCircleData &
QcLocationCircleData::operator=(const QcLocationCircleData & other)
{
  if (this != &other) {
    m_visible = other.m_visible;
    m_coordinate = other.m_coordinate;
    m_bearing = other.m_bearing;
    m_horizontal_precision = other.m_horizontal_precision;
  }

  return *this;
}

void
QcLocationCircleData::set_visible(bool visible)
{
  if (visible != m_visible) {
    qQCInfo() << "visible changed" << visible;
    m_visible = visible;
    emit visible_changed();
  }
}

void
QcLocationCircleData::set_coordinate(const QcWgsCoordinate & coordinate)
{
  if (coordinate != m_coordinate) {
    qQCInfo() << "coordinate changed" << coordinate;
    m_coordinate = coordinate;
    emit coordinate_changed();
  }
}

void
QcLocationCircleData::set_bearing(double bearing)
{
  if (qAbs(bearing - m_bearing) > 1.) {
    // qQCInfo() << "bearing changed" << bearing;
    m_bearing = bearing;
    emit bearing_changed();
  }
}

void
QcLocationCircleData::set_horizontal_precision(double horizontal_precision)
{
  if (horizontal_precision != m_horizontal_precision) {
    qQCInfo() << "horizontal precision changed" << horizontal_precision;
    m_horizontal_precision = horizontal_precision;
    emit horizontal_precision_changed();
  }
}

/**************************************************************************************************/

// QC_END_NAMESPACE
