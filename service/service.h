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

#ifndef __SERVICE_H__
#define __SERVICE_H__

/**************************************************************************************************/

#include <QTimer>

#include "rep_service_source.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class Service : public ServiceSource
{
  Q_OBJECT

public:
  Service(QObject * parent = nullptr);
  ~Service();

public slots:
  void ping() override;
  void start_timer() override;
  void stop_timer() override;
  void stop_service();

private slots:
  void timer_slot();

private:
  QTimer m_timer;
};

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __SERVICE_H__ */
