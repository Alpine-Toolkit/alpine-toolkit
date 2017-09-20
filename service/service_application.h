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

#ifndef __SERVICE_APPLICATION_H__
#define __SERVICE_APPLICATION_H__

/**************************************************************************************************/

#include <QCoreApplication>
#include <QRemoteObjectHost>

#include "service.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class ServiceApplication : public QCoreApplication
{
  Q_OBJECT

public:
  static Service * service; // Fixme: instance()

public:
  ServiceApplication(int & argc, char ** argv);

private:
  QRemoteObjectHost host_node;
};

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __SERVICE_APPLICATION_H__ */
