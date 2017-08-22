// -*- mode: c++ -*-
/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire
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
 * $QTCARTO_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef __CHECKSUM_H__
#define __CHECKSUM_H__

/**************************************************************************************************/

#include <QVector>

/**************************************************************************************************/

class Checksum
{
public:
  Checksum(QVector<unsigned int> input);
  ~Checksum();

  unsigned int damm(bool use_alt_table = false) const { return compute_damm(m_input, use_alt_table); }
  bool check_damm(unsigned int checksum, bool use_alt_table = false) const;

  // Verhoeff
  // Luhn weaker than Damm and Verhoeff Algorithm https://en.wikipedia.org/wiki/Luhn_algorithm

private:
  unsigned int compute_damm(QVector<unsigned int> input, bool use_alt_table = false) const;

private:
  QVector<unsigned int> m_input;
};

/**************************************************************************************************/

#endif /* __CHECKSUM_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
