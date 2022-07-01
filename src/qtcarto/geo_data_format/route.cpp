/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "route.h"
#include "qtcarto.h"

/**************************************************************************************************/

QcRouteMetaData::QcRouteMetaData()
  : m_name(),
    m_comment(),
    m_description(),
    m_source(),
    m_link(),
    m_number(),
    m_type()
{}

QcRouteMetaData::QcRouteMetaData(const QcRouteMetaData & other)
  : m_name(other.m_name),
    m_comment(other.m_comment),
    m_description(other.m_description),
    m_source(other.m_source),
    m_link(other.m_link),
    m_number(other.m_number),
    m_type(other.m_type)
{}

QcRouteMetaData::~QcRouteMetaData()
{}

QcRouteMetaData &
QcRouteMetaData::operator=(const QcRouteMetaData & other)
{
  if (this != &other) {
    m_name = other.m_name;
    m_comment = other.m_comment;
    m_description = other.m_description;
    m_source = other.m_source;
    m_link = other.m_link;
    m_number = other.m_number;
    m_type = other.m_type;
  }

  return *this;
}

/**************************************************************************************************/

QcRoute::QcRoute()
  : QcRouteMetaData(),
    m_waypoints()
{}

QcRoute::QcRoute(const QcRoute & other)
  : QcRouteMetaData(other),
    m_waypoints(other.m_waypoints)
{}

QcRoute::~QcRoute()
{}

QcRoute &
QcRoute::operator=(const QcRoute & other)
{
  if (this != &other) {
    QcRouteMetaData::operator=(other);
    m_waypoints = other.m_waypoints;
  }

  return *this;
}

void
QcRoute::add_waypoint(const QcWayPoint & waypoint)
{
  m_waypoints.append(waypoint);
}

/**************************************************************************************************/

QcTrack::QcTrack()
  : QcRouteMetaData(),
    m_segments()
{}

QcTrack::QcTrack(const QcTrack & other)
  : QcRouteMetaData(other),
    m_segments(other.m_segments)
{}

QcTrack::~QcTrack()
{}

QcTrack &
QcTrack::operator=(const QcTrack & other)
{
  if (this != &other) {
    QcRouteMetaData::operator=(other);
    m_segments = other.m_segments;
  }

  return *this;
}

void
QcTrack::add_segment(const QcWayPointList & segment)
{
  m_segments.append(segment);
}

/**************************************************************************************************/

// QC_END_NAMESPACE
