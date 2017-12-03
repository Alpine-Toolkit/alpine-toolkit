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

#include "refuge_schema.h"
#include "alpine_toolkit.h"

#include<QtDebug>

/**************************************************************************************************/

void
Refuge::post_init()
{
  set_first_letter();

  QObject::connect(this, &Refuge::short_nameChanged, this, &Refuge::set_first_letter);
}

bool
Refuge::operator<(const Refuge & other) const
{
  // qATInfo() << m_short_name << other.m_short_name;

  // Fixme: segfault
  // return m_short_name.localeAwareCompare(other.m_short_name);

  auto a = m_short_name.normalized(QString::NormalizationForm_D);
  auto b = other.m_short_name.normalized(QString::NormalizationForm_D);
  return a < b;
}

void
Refuge::set_first_letter()
{
  // Fixme: to function
  m_first_letter = m_short_name.normalized(QString::NormalizationForm_D)[0].toUpper();
  // m_short_name[0].toUpper();
}
