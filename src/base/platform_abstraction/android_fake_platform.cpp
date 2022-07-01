/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#include "android_fake_platform.h"
// #include "alpine_toolkit.h"

#include "android_fake_permission_manager.h"

#include <QtDebug>

/**************************************************************************************************/

AndroidFakePlatform::AndroidFakePlatform(QObject * parent)
  : PlatformAbstraction(parent)
{
  m_permission_manager = new AndroidFakePermissionManager();
}

AndroidFakePlatform::~AndroidFakePlatform()
{}
