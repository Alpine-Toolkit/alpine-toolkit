/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "service_application.h"
#include "alpine_toolkit.h"

#include "definitions.h"

#include <QtDebug>

/**************************************************************************************************/

Service * ServiceApplication::service = nullptr;

ServiceApplication::ServiceApplication(int & argc, char ** argv)
  : QCoreApplication(argc, argv),
    host_node(QUrl(QStringLiteral(SERVICE_URL)))
{
  qATInfo() << "Start Apline Tookit Service";

  service = new Service();
  host_node.enableRemoting(service);
}

// QC_END_NAMESPACE
