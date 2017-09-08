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

  PlatformType platform_type() const { return Linux; }

  Q_INVOKABLE void issue_call(const QString & phone_number);
  Q_INVOKABLE void issue_dial(const QString & phone_number);

  void impl_perform_lamp_signal(const QString & encoded_message, int rate_ms);

private slots:
  void update_orientation_lock();
  void update_orientation();
  void update_full_wave_lock();
  void update_torch();
};

/**************************************************************************************************/

#endif // LINUX_PLATFORM_H
