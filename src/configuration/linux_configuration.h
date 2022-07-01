// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

#ifndef LINUX_CONFIGURATION_H
#define LINUX_CONFIGURATION_H

/**************************************************************************************************/

#include "configuration/configuration.h"

/**************************************************************************************************/

class QaLinuxConfig : public QaConfig
{
  Q_OBJECT

public:
  QaLinuxConfig();  // Fixme: can't be private
  ~QaLinuxConfig();
};

/**************************************************************************************************/

#endif // LINUX_CONFIGURATION_H
