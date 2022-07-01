/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "osm.h"
#include "qtcarto.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QcOsmElment::QcOsmElment()
  : m_id(),
  m_version(),
  m_changeset(),
  m_visible(),
  m_uid(),
  m_user(),
  m_timestamp()
{}

QcOsmElment::QcOsmElment(int id, int version, int changeset, bool visible, int uid, QString user, QDateTime timestamp)
  : m_id(id),
  m_version(version),
  m_changeset(changeset),
  m_visible(visible),
  m_uid(uid),
  m_user(user),
  m_timestamp(timestamp)
{}

QcOsmElment::QcOsmElment(const QcOsmElment & other)
  : m_id(other.m_id),
  m_version(other.m_version),
  m_changeset(other.m_changeset),
  m_visible(other.m_visible),
  m_uid(other.m_uid),
  m_user(other.m_user),
  m_timestamp(other.m_timestamp)
{}

QcOsmElment::~QcOsmElment()
{}

/**************************************************************************************************/

QcOsmNode::QcOsmNode()
  : QcOsmElment(),
  m_coordinate()
{}

QcOsmNode::QcOsmNode(int id, int version, int changeset, bool visible, int uid, QString user, QDateTime timestamp,
                     const QcWgsCoordinate & coordinate)
  : QcOsmElment(id, version, changeset, visible, uid, user, timestamp),
  m_coordinate(coordinate)
{}

QcOsmNode::QcOsmNode(const QcOsmNode & other)
  : QcOsmElment(other),
  m_coordinate(other.m_coordinate)
{}

/**************************************************************************************************/

QcOsmWay::QcOsmWay()
  : QcOsmElment(),
  m_nodes()
{}

QcOsmWay::QcOsmWay(int id, int version, int changeset, bool visible, int uid, QString user, QDateTime timestamp,
                   const QList<QcOsmNode *> & nodes)
  : QcOsmElment(id, version, changeset, visible, uid, user, timestamp),
  m_nodes(nodes)
{}

QcOsmWay::QcOsmWay(const QcOsmWay & other)
  : QcOsmElment(other),
  m_nodes(other.m_nodes)
{}

/**************************************************************************************************/

QcOsmMember::QcOsmMember()
  : m_type(),
  m_id(),
  m_role()
{}

QcOsmMember::QcOsmMember(Type type, int id, QString role)
  : m_type(type),
  m_id(id),
  m_role(role)
{}

QcOsmMember::QcOsmMember(const QcOsmMember & other)
  : m_type(other.m_type),
  m_id(other.m_id),
  m_role(other.m_role)
{}

QcOsmMember::~QcOsmMember()
{}

/**************************************************************************************************/

QcOsmRelation::QcOsmRelation()
  : QcOsmElment(),
  m_members()
{}

QcOsmRelation::QcOsmRelation(int id, int version, int changeset, bool visible, int uid, QString user, QDateTime timestamp,
                   const QList<QcOsmMember> & members)
  : QcOsmElment(id, version, changeset, visible, uid, user, timestamp),
  m_members(members)
{}

QcOsmRelation::QcOsmRelation(const QcOsmRelation & other)
  : QcOsmElment(other),
  m_members(other.m_members)
{}

/**************************************************************************************************/

// QC_END_NAMESPACE
