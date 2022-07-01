/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
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
  // m_short_name[0].toUpper();
  if (m_short_name.length())
    m_first_letter = m_short_name.normalized(QString::NormalizationForm_D)[0].toUpper();
}
