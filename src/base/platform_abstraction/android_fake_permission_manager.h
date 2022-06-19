// -*- mode: c++ -*-

/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef ANDROID_FAKE_PERMISSION_MANAGER_H
#define ANDROID_FAKE_PERMISSION_MANAGER_H

#include "platform_abstraction/permission_manager.h"

/**************************************************************************************************/

class AndroidFakePermissionManager : public PermissionManager
{
  Q_OBJECT

public:
  AndroidFakePermissionManager();
  ~AndroidFakePermissionManager();

  // Q_INVOKABLE QStringList external_storages() const override { return QStringList(); }

  Q_INVOKABLE bool require_write_permission(const QString & path) const override;

private:
  bool need_explain(const QString & permission);
  bool is_permission_granted(const QString & permission) const;
  void request_permission(const QString & permission);

private:
  QHash<QString, bool> m_permission_status;
};

/**************************************************************************************************/

#endif // ANDROID_FAKE_PERMISSION_MANAGER_H
