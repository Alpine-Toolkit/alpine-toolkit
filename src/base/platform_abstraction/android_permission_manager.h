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

#ifndef ANDROID_PERMISSION_MANAGER_H
#define ANDROID_PERMISSION_MANAGER_H

#include <QtAndroid>

#include "platform_abstraction/permission_manager.h"

/**************************************************************************************************/

class AndroidPermissionManager : public PermissionManager
{
  Q_OBJECT

public:
  AndroidPermissionManager();
  ~AndroidPermissionManager();

  Q_INVOKABLE bool require_write_permission(const QString & path) const override;

// public:
//   void on_permission_granted(const QString & permission);
//   void on_permission_denied(const QString & permission);

private:
  bool need_explain(const QString & permission) override;

  bool is_permission_granted(const QString & permission) const override;
  bool is_permission_denied(const QString & permission) const;

  void request_permission(const QString & permission) override;

  void permission_callback(const QtAndroid::PermissionResultMap & map);

  QString to_android_permission(const QString & permission) const;
  QString from_android_permission(const QString & permission) const;

private:
  QHash<QString, bool> m_need_explain_cache;
};

/**************************************************************************************************/

#endif // ANDROID_PERMISSION_MANAGER_H
