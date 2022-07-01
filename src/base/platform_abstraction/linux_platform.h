// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#ifndef LINUX_PLATFORM_H
#define LINUX_PLATFORM_H

/**************************************************************************************************/

#include "platform_abstraction/platform_abstraction.h"

/**************************************************************************************************/

class LinuxPlatform : public PlatformAbstraction
{
  Q_OBJECT

public:
  explicit LinuxPlatform(QObject * parent = nullptr);
  ~LinuxPlatform();

  PlatformType platform_type() const override { return Linux; }
};

/**************************************************************************************************/

#endif // LINUX_PLATFORM_H
