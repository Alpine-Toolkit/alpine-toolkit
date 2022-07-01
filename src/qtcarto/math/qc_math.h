/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __QC_MATH_H__
#define __QC_MATH_H__

/**************************************************************************************************/

#include <cmath>

/**************************************************************************************************/

#ifndef M_PI
// constepxr double
#define M_PI 3.14159265358979323846
#endif

#ifndef M_2PI
// constepxr double
#define M_2PI 2 * M_PI
#endif

#ifndef M_HALF_PI
// constepxr double
#define M_HALF_PI M_PI / 2.
#endif

/**************************************************************************************************/

// Fixme: static ?
inline static double
haversine(double theta)
{
  return .5*(1 - cos(theta)); // = sin(theta / 2)**2
}

/**************************************************************************************************/

inline static
double
middle(double a, double b)
{
  return .5*(a + b);
}

/**************************************************************************************************/

// Fixme: sign_of ?
inline static
double
sign(double x)
{
  return copysign(1., x);
}

/**************************************************************************************************/

inline static
double
epsilon_float(double a, double b, double epsilon = 1e-3)
{
  return fabs(a-b) <= epsilon;
}

/**************************************************************************************************/

// Clamp x in the range [-1.,1].
double trignometric_clamp(double x);

/**************************************************************************************************/

inline static
bool
is_in_trignometric_range(double x)
{
  return -1. <= x and x <= 1.;
}

/**************************************************************************************************/

inline static
int
smallest_power_of_two(double x)
{
  return static_cast<int>(log(x)/log(2));
}

/**************************************************************************************************/

#endif // __QC_MATH_H__
