// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
