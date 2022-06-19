/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "logger.h"

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

// https://doc.qt.io/qt-6/qloggingcategory.html#Q_LOGGING_CATEGORY
// Defines a logging category name, and makes it configurable under the string identifier.
// By default, all message types are enabled.
Q_LOGGING_CATEGORY(at_logger, "alpine-toolkit")

/**************************************************************************************************/

// QC_END_NAMESPACE
