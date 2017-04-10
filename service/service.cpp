/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
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
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include "service.h"

#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

Service::Service(QObject * parent)
  : ServiceSource(parent),
    m_timer(this)
{
  qInfo() << "Alpine Toolkit Service Source is started";

  connect(&m_timer, &QTimer::timeout, this, &Service::timer_slot);
  m_timer.setInterval(1000);
}

Service::~Service()
{
  qInfo() << "Service::~Service";
}

void
Service::ping()
{
  qInfo() << "Alpine Toolkit Service: received ping";
  emit pong();
}

void
Service::start_timer()
{
  qInfo() << "Alpine Toolkit Service: start_timer";
  m_timer.start();
}

void
Service::stop_timer()
{
  qInfo() << "Alpine Toolkit Service: stop_timer";
  m_timer.stop();
}

void
Service::timer_slot()
{
  qInfo() << "Service::timer_slot";
}

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
