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
