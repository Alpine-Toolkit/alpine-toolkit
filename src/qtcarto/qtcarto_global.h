// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

#ifndef QTCARTO_GLOBAL_H
#define QTCARTO_GLOBAL_H

/**************************************************************************************************/

#include <QtCore/qglobal.h>

/**************************************************************************************************/

// QtCarto Version
#define QTCARTO_VERSION_MAJOR 1
#define QTCARTO_VERSION_MINOR 0
#define QTCARTO_VERSION_PATCH 0

// Can be used like #if (QTCARTO_VERSION >= QTCARTO_VERSION_CHECK(1, 1, 0))
#define QTCARTO_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))
// QTCARTO_VERSION is (major << 16) + (minor << 8) + patch.
#define QTCARTO_VERSION QTCARTO_VERSION_CHECK(QTCARTO_VERSION_MAJOR, QTCARTO_VERSION_MINOR, QTCARTO_VERSION_PATCH)

#if defined(QTCARTO_LIBRARY)
#  define QC_EXPORT Q_DECL_EXPORT
#else
#  define QC_EXPORT Q_DECL_IMPORT
#endif

// cf. qglobal.h
#define QTCARTO_USE_NAMESPACE using namespace ::QTCARTO_NAMESPACE;
#define QTCARTO_BEGIN_NAMESPACE namespace QTARTO_NAMESPACE {
#define QTCARTO_END_NAMESPACE }

#endif // QTCARTO_GLOBAL_H
