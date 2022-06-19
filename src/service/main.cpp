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

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

int
main(int argc, char * argv[])
{
  ServiceApplication application(argc, argv);
  return application.exec();
}

// QC_END_NAMESPACE
