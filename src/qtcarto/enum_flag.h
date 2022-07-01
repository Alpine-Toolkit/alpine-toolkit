// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __QC_ENUM_FLAG_H__
#define __QC_ENUM_FLAG_H__

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

#define ENUM_FLAGS(T, INT_T) \
  inline T operator & (T x, T y) { return static_cast<T>(static_cast<INT_T>(x) & static_cast<INT_T>(y)); }; \
  inline T operator | (T x, T y) { return static_cast<T>(static_cast<INT_T>(x) | static_cast<INT_T>(y)); }; \
  inline T operator ^ (T x, T y) { return static_cast<T>(static_cast<INT_T>(x) ^ static_cast<INT_T>(y)); }; \
  inline T operator ~ (T x)      { return static_cast<T>(~static_cast<INT_T>(x)); }; \
  inline T & operator &= (T & x, T y) { x = x & y; return x; };         \
  inline T & operator |= (T & x, T y) { x = x | y; return x; };         \
  inline T & operator ^= (T & x, T y) { x = x ^ y; return x; };         \
  inline bool __flag_to_bool (T x) { return static_cast<INT_T>(x) != 0; } \
  inline bool test_bit (T x, T y) { return __flag_to_bool(x & y); }

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_ENUM_FLAG_H__ */
