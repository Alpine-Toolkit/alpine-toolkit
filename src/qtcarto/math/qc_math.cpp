/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "qc_math.h"
#include "qtcarto.h"

/**************************************************************************************************/

// Clamp x in the range [-1.,1].
double
trignometric_clamp(double x)
{
  if (x > 1.)
    return 1.;
  else if (x < -1.)
    return -1.;
  else
    return x;
}
