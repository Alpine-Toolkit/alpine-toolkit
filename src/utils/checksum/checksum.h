// -*- mode: c++ -*-
/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
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
