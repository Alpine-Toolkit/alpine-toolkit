/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) None Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
****************************************************************************/

#include "satellite_model.h"
#include "alpine_toolkit.h"

#include <QTimer>
#include <QDebug>

SatelliteModel::SatelliteModel(QObject * parent)
  : QAbstractListModel(parent),
    source(nullptr),
    m_componentCompleted(false),
    m_running(false),
    m_runningRequested(false),
    isSingle(false),
    singleRequestServed(false)
{
  source = QGeoSatelliteInfoSource::createDefaultSource(this);
  if (source) {
    source->setUpdateInterval(3000);
    connect(source, SIGNAL(satellitesInViewUpdated(QList<QGeoSatelliteInfo>)),
	    this, SLOT(satellitesInViewUpdated(QList<QGeoSatelliteInfo>)));
    connect(source, SIGNAL(satellitesInUseUpdated(QList<QGeoSatelliteInfo>)),
	    this, SLOT(satellitesInUseUpdated(QList<QGeoSatelliteInfo>)));
    connect(source, SIGNAL(error(QGeoSatelliteInfoSource::Error)),
	    this, SLOT(error(QGeoSatelliteInfoSource::Error)));
  } else {
    qWarning() << "No satellite data source found.";
  }
}

int
SatelliteModel::rowCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);
  return source ? knownSatellites.count() : 0;
}

QVariant
SatelliteModel::data(const QModelIndex & index, int role) const
{
  // qATInfo() << index << role;

  if (!source)
    return QVariant();

  if (!index.isValid() || index.row() < 0)
    return QVariant();

  if (index.row() >= knownSatellites.count()) {
    qWarning() << "SatelliteModel: Index out of bound";
    return QVariant();
  }

  const QGeoSatelliteInfo & info = knownSatellites.at(index.row());
  switch (role) {
  case IdentifierRole:
    return info.satelliteIdentifier();
  case InUseRole:
    return satellitesInUse.contains(info.satelliteIdentifier());
  case SignalStrengthRole:
    return info.signalStrength();
  case ElevationRole:
    if (!info.hasAttribute(QGeoSatelliteInfo::Elevation))
      return QVariant();
    return info.attribute(QGeoSatelliteInfo::Elevation);
  case AzimuthRole:
    if (!info.hasAttribute(QGeoSatelliteInfo::Azimuth))
      return QVariant();
    return info.attribute(QGeoSatelliteInfo::Azimuth);
  default:
    break;
  }

  return QVariant();
}

QHash<int, QByteArray>
SatelliteModel::roleNames() const
{
  QHash<int, QByteArray> roleNames;
  roleNames.insert(IdentifierRole, "satelliteIdentifier");
  roleNames.insert(InUseRole, "isInUse");
  roleNames.insert(SignalStrengthRole, "signalStrength");
  roleNames.insert(ElevationRole, "elevation");
  roleNames.insert(AzimuthRole, "azimuth");
  return roleNames;
}

void
SatelliteModel::componentComplete()
{
  m_componentCompleted = true;
  if (m_runningRequested)
    setRunning(true);
}

bool
SatelliteModel::running() const
{
  return m_running;
}

bool
SatelliteModel::isSingleRequest() const
{
  return isSingle;
}

void
SatelliteModel::setSingleRequest(bool single)
{
  if (running()) {
    qWarning() << "Cannot change single request mode while running";
    return;
  }

  if (single != isSingle) { // flag changed
    isSingle = single;
    emit singleRequestChanged();
  }
}

void
SatelliteModel::setRunning(bool isActive)
{
  if (!source)
    return;

  if (!m_componentCompleted) {
    m_runningRequested = isActive;
    return;
  }

  if (m_running == isActive)
    return;

  m_running = isActive;

  if (m_running) {
    clearModel();
    if (isSingleRequest())
      source->requestUpdate(10000);
    else
      source->startUpdates();

  } else {
    if (!isSingleRequest())
      source->stopUpdates();
  }


  Q_EMIT runningChanged();
}

int
SatelliteModel::entryCount() const
{
  return knownSatellites.count();
}

bool
SatelliteModel::canProvideSatelliteInfo() const
{
  return source != nullptr;
}

void
SatelliteModel::clearModel()
{
  beginResetModel();
  knownSatelliteIds.clear();
  knownSatellites.clear();
  satellitesInUse.clear();
  endResetModel();
}

void
SatelliteModel::error(QGeoSatelliteInfoSource::Error error)
{
  emit errorFound((int)error);
}

QT_BEGIN_NAMESPACE
bool
operator<(const QGeoSatelliteInfo & a, const QGeoSatelliteInfo & b)
{
  return a.satelliteIdentifier() < b.satelliteIdentifier();
}
QT_END_NAMESPACE

void
SatelliteModel::satellitesInViewUpdated(const QList<QGeoSatelliteInfo> & infos)
{
  if (!running())
    return;

  int oldEntryCount = knownSatellites.count();


  QSet<int> satelliteIdsInUpdate;
  foreach (const QGeoSatelliteInfo &info, infos)
    satelliteIdsInUpdate.insert(info.satelliteIdentifier());

  QSet<int> toBeRemoved = knownSatelliteIds - satelliteIdsInUpdate;

  // We reset the model as in reality just about all entry values change
  // and there are generally a lot of inserts and removals each time
  // Hence we don't bother with complex model update logic beyond resetModel()
  beginResetModel();

  knownSatellites = infos;

  // sort them for presentation purposes
  std::sort(knownSatellites.begin(), knownSatellites.end());

  // remove old "InUse" data
  // new satellites are by default not in "InUse"
  // existing satellites keep their "inUse" state
  satellitesInUse -= toBeRemoved;

  knownSatelliteIds = satelliteIdsInUpdate;
  endResetModel();

  if (oldEntryCount != knownSatellites.count())
    emit entryCountChanged();
}

void
SatelliteModel::satellitesInUseUpdated(const QList<QGeoSatelliteInfo> & infos)
{
  if (!running())
    return;

  beginResetModel();

  satellitesInUse.clear();
  foreach (const QGeoSatelliteInfo &info, infos)
    satellitesInUse.insert(info.satelliteIdentifier());

  endResetModel();
}
