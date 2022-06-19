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
