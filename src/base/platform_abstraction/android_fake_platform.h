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

#ifndef ANDROID_FAKE_PLATFORM_H
#define ANDROID_FAKE_PLATFORM_H

/**************************************************************************************************/

#include "platform_abstraction/platform_abstraction.h"

/**************************************************************************************************/

class AndroidFakePlatform : public PlatformAbstraction
{
  Q_OBJECT

public:
  explicit AndroidFakePlatform(QObject * parent = nullptr);
  ~AndroidFakePlatform();

  PlatformType platform_type() const override { return AndroidFake; }
};

/**************************************************************************************************/

#endif // ANDROID_FAKE_PLATFORM_H
