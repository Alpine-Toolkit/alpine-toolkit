// -*- mode: c++ -*-

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

#ifndef SATELLITEMODEL_H
#define SATELLITEMODEL_H

#include <QAbstractListModel>
#include <QSet>
#include <QtQml/qqml.h>
#include <QtQml/QQmlParserStatus>
#include <QtPositioning/QGeoSatelliteInfoSource>

QT_FORWARD_DECLARE_CLASS(QTimer)
QT_FORWARD_DECLARE_CLASS(QGeoSatelliteInfoSource)

class SatelliteModel : public QAbstractListModel, public QQmlParserStatus
{
  Q_OBJECT
  Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
  Q_PROPERTY(bool satelliteInfoAvailable READ canProvideSatelliteInfo NOTIFY canProvideSatelliteInfoChanged)
  Q_PROPERTY(int entryCount READ entryCount NOTIFY entryCountChanged)
  Q_PROPERTY(bool singleRequestMode READ isSingleRequest WRITE setSingleRequest NOTIFY singleRequestChanged)
  Q_INTERFACES(QQmlParserStatus)

public:
  explicit SatelliteModel(QObject * parent = 0);

  enum Roles {
    IdentifierRole = Qt::UserRole + 1,
    InUseRole,
    SignalStrengthRole,
    ElevationRole,
    AzimuthRole
  };
  Q_ENUMS(Roles)

  // From QAbstractListModel
  int rowCount(const QModelIndex & parent) const;
  QVariant data(const QModelIndex & index, int role) const;
  QHash<int, QByteArray> roleNames() const;

  // From QQmlParserStatus
  void classBegin() {}
  void componentComplete();

  bool running() const;
  void setRunning(bool isActive);

  bool isSingleRequest() const;
  void setSingleRequest(bool single);

  int entryCount() const;

  bool canProvideSatelliteInfo() const;

signals:
  void runningChanged();
  void entryCountChanged();
  void errorFound(int code);
  void canProvideSatelliteInfoChanged();
  void singleRequestChanged();

public slots:
  void clearModel();

private slots:
  void error(QGeoSatelliteInfoSource::Error);
  void satellitesInViewUpdated(const QList<QGeoSatelliteInfo> & infos);
  void satellitesInUseUpdated(const QList<QGeoSatelliteInfo> & infos);

private:
  QGeoSatelliteInfoSource * source;
  bool m_componentCompleted;
  bool m_running;
  bool m_runningRequested;
  QList <QGeoSatelliteInfo> knownSatellites;
  QSet<int> knownSatelliteIds;
  QSet<int> satellitesInUse;
  QTimer * timer;
  bool isSingle;
  bool singleRequestServed;
};

QML_DECLARE_TYPE(SatelliteModel)

#endif // SATELLITEMODEL_H
