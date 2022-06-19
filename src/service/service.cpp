/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "service.h"
#include "alpine_toolkit.h"

#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

Service::Service(QObject * parent)
  : ServiceSource(parent),
    m_timer(this)
{
  qATInfo() << "Alpine Toolkit Service is started";

  connect(&m_timer, &QTimer::timeout, this, &Service::timer_slot);
  m_timer.setInterval(1000);
}

Service::~Service()
{
  qATInfo() << "Alpine Toolkit Service: ~Service";
}

void
Service::ping()
{
  qATInfo() << "Alpine Toolkit Service: received ping";
  emit pong();
}

void
Service::start_timer()
{
  qATInfo() << "Alpine Toolkit Service: start_timer";
  m_timer.start();
}

void
Service::stop_timer()
{
  qATInfo() << "Alpine Toolkit Service: stop_timer";
  m_timer.stop();
}

void
Service::timer_slot()
{
  qATInfo() << "Alpine Toolkit Service: timer slot";
}

void
Service::stop_service()
{
  qATInfo() << "Alpine Toolkit Service: stop_service";
}

// QC_END_NAMESPACE
