// -*- mode: c++ -*-

/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire.
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the QtCarto library.
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

#ifndef ANDROID_PLATFORM_H
#define ANDROID_PLATFORM_H

/**************************************************************************************************/

#include "platform_abstraction/platform_abstraction.h"

/**************************************************************************************************/

class AndroidPlatform : public PlatformAbstraction
{
  Q_OBJECT

public:
  explicit AndroidPlatform(QObject * parent = nullptr);
  ~AndroidPlatform();

  PlatformType platform_type() const { return Linux; }

  Q_INVOKABLE QStringList need_explain() const;
  Q_INVOKABLE QStringList need_grant() const;
  Q_INVOKABLE void ask_permission(const QString & permission) const;
  Q_INVOKABLE bool is_permission_granted(const QString & permission) const;
  Q_INVOKABLE bool is_permission_denied(const QString & permission) const;

  Q_INVOKABLE QStringList external_storages() const;

  Q_INVOKABLE void issue_call(const QString & phone_number) const;
  Q_INVOKABLE void issue_dial(const QString & phone_number) const;

  Q_INVOKABLE void perform_lamp_signal(const QString & message, int rate_ms = 250) const;
  Q_INVOKABLE void stop_lamp_signal() const;

  Q_INVOKABLE void start_lamp_dimmer(int period, int duty_cycle) const;
  Q_INVOKABLE void stop_lamp_dimmer() const;

  void on_permission_granted(const QString & permission);
  void on_permission_denied(const QString & permission);

private slots:
  void update_orientation_lock();
  void update_orientation();
  void update_full_wave_lock();
  void update_torch();
};

/**************************************************************************************************/

#endif // ANDROID_PLATFORM_H
