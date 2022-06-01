/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $ALPINE_TOOLKIT_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include "checksum.h"
// #include "alpine_toolkit.h"

/**************************************************************************************************/

Checksum::Checksum(QVector<unsigned int> input)
  : m_input(input)
{}

Checksum::~Checksum()
{}

/**************************************************************************************************/

// Damm, H. Michael (2004). Total anti-symmetrische Quasigruppen. Philipps-Universität Marburg. urn:nbn:de:hebis:04-z2004-05162.
// http://archiv.ub.uni-marburg.de/diss/z2004/0516/pdf/dhmd.pdf

static const unsigned int table[10][10] = {
  // Ordnung 10: Computer-Suche, erkennt alle phonetischen Fehler
  {0, 3, 1, 7, 5, 9, 8, 6, 4, 2},
  {7, 0, 9, 2, 1, 5, 4, 8, 6, 3},
  {4, 2, 0, 6, 8, 7, 1, 3, 5, 9},
  {1, 7, 5, 0, 9, 8, 3, 4, 2, 6},
  {6, 1, 2, 3, 0, 4, 5, 9, 7, 8},
  {3, 6, 7, 4, 2, 0, 9, 5, 8, 1},
  {5, 8, 6, 9, 7, 2, 0, 1, 3, 4},
  {8, 9, 4, 5, 3, 6, 2, 0, 1, 7},
  {9, 4, 3, 8, 6, 1, 7, 2, 0, 5},
  {2, 5, 8, 1, 4, 3, 6, 7, 9, 0},
};

static const unsigned int alt_table[10][10] = {
  // Ordnung 10: Diagonalmethode für Ordnung 10
  {0, 2, 3, 4, 5, 6, 7, 8, 9, 1},
  {2, 0, 4, 1, 7, 9, 5, 3, 8, 6},
  {3, 7, 0, 5, 2, 8, 1, 6, 4, 9},
  {4, 1, 8, 0, 6, 3, 9, 2, 7, 5},
  {5, 6, 2, 9, 0, 7, 4, 1, 3, 8},
  {6, 9, 7, 3, 1, 0, 8, 5, 2, 4},
  {7, 5, 1, 8, 4, 2, 0, 9, 6, 3},
  {8, 4, 6, 2, 9, 5, 3, 0, 1, 7},
  {9, 8, 5, 7, 3, 1, 6, 4, 0, 2},
  {1, 3, 9, 6, 8, 4, 2, 7, 5, 0},
};

unsigned int
Checksum::compute_damm(QVector<unsigned int> input, bool use_alt_table) const
{
  unsigned int interim = 0;
  for (auto digit : input)
    if (use_alt_table)
      interim = alt_table[interim][digit];
    else
      interim = table[interim][digit];

  return interim;
}

bool
Checksum::check_damm(unsigned int checksum, bool use_alt_table) const
{
  QVector<unsigned int> input = m_input;
  input.append(checksum);

  unsigned int interim = compute_damm(input, use_alt_table);

  return interim == 0;
}
