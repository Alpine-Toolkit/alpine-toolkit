// -*- mode: c++ -*-

/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the QtCarto library.
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
** $ALPINE_TOOLKIT_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __CLIENT_H__
#define __CLIENT_H__

/**************************************************************************************************/

#include <QProcess>

// Generated at root
#include "rep_service_replica.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class ServiceClient : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool started READ is_started NOTIFY serviceStateChanged)
  Q_PROPERTY(ServiceReplica* replica READ replica)

public:
  // qtcarto/src/tools/platform.h
  ServiceClient(QObject * parent = nullptr); // QSharedPointer<ServiceReplica> ptr
  ~ServiceClient();

  Q_INVOKABLE void start_service(); // static
  Q_INVOKABLE void stop_service();
  bool is_started() const { return m_started; }
  Q_INVOKABLE void foo();

  // QSharedPointer<ServiceReplica> replica() { return m_replica; }
  ServiceReplica * replica() { return m_replica.data(); }

private slots:
  void on_pong();

signals:
  void serviceStateChanged(bool started);

private:
#ifdef ANDROID
  static void call_service_static_method(const char * method);
#endif
  void connect();
  void init_connections();
  void set_service_state(bool state);

private:
#ifndef ANDROID
  static QProcess * m_service_process;
#endif

private:
  bool m_started;
  QRemoteObjectNode m_node;
  QSharedPointer<ServiceReplica> m_replica; // Fixme: QSharedPointer required ???
};

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __CLIENT_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
