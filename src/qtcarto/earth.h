// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

#ifndef __QC_EARTH_H__
#define __QC_EARTH_H__

/**************************************************************************************************/

#include <cmath>

#include "qtcarto_global.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

// Equatorial radius (half major axis) of the ellipsoid
constexpr double EQUATORIAL_RADIUS = 6378137.0; // [m] WGS84
constexpr double EQUATORIAL_DIAMETER = 2. * EQUATORIAL_RADIUS; // [m]
constexpr double HALF_EQUATORIAL_PERIMETER = M_PI * EQUATORIAL_RADIUS; // [m] 20037508.342789244
constexpr double EQUATORIAL_PERIMETER = 2. * HALF_EQUATORIAL_PERIMETER; // [m]
constexpr double INVERSE_EQUATORIAL_PERIMETER = 1. / EQUATORIAL_PERIMETER; // [m]

// QT_END_NAMESPACE

/**************************************************************************************************/

#endif // __QC_EARTH_H__
