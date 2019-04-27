// -*- mode: c++ -*-

/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire.
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine Toolkit software.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
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
