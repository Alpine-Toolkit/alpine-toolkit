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

#include "linux_platform.h"
#include "alpine_toolkit.h"

#include <QtDebug>

/**************************************************************************************************/

LinuxPlatform::LinuxPlatform(QObject * parent)
  : PlatformAbstraction(parent)
{
  connect(this, SIGNAL(orientation_lockChanged()), this, SLOT(update_orientation_lock()));
  connect(this, SIGNAL(orientationChanged()), this, SLOT(update_orientation()));
  connect(this, SIGNAL(full_wave_lockChanged()), this, SLOT(update_full_wave_lock()));
  connect(this, SIGNAL(torchChanged()), this, SLOT(update_torch()));
}

LinuxPlatform::~LinuxPlatform()
{}

/**************************************************************************************************/

void
LinuxPlatform::update_orientation_lock()
{
  qATInfo() << "update_orientation_lock" << m_orientation_lock;
}

/**************************************************************************************************/

void
LinuxPlatform::update_orientation()
{
  qATInfo() << "update_orientation" << m_orientation;
}

/**************************************************************************************************/

void
LinuxPlatform::update_full_wave_lock()
{
  qATInfo() << "update_full_wave_lock" << m_full_wave_lock;
}

/**************************************************************************************************/

void
LinuxPlatform::update_torch()
{
  qATInfo() << "update_torch" << m_torch_enabled;
}

/**************************************************************************************************/

void
LinuxPlatform::issue_call(const QString & phone_number)
{
  qATInfo() << "issue_call" << phone_number;
}

void
LinuxPlatform::issue_dial(const QString & phone_number)
{
  qATInfo() << "issue_dial" << phone_number;
}

/**************************************************************************************************/

void
LinuxPlatform::impl_perform_lamp_signal(const QString & encoded_message, int rate_ms)
{
  qATInfo() << "impl_perform_lamp_signal" << encoded_message << rate_ms;
}
