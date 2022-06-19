// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __LOGGER_H__
#define __LOGGER_H__

/**************************************************************************************************/

#include <QLoggingCategory>
#include <QMessageLogContext>
#include <QString>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

// https://doc.qt.io/qt-6/qloggingcategory.html#Q_DECLARE_LOGGING_CATEGORY
// Declares a logging category name.
// The macro can be used to declare a common logging category shared in different parts of the program.
Q_DECLARE_LOGGING_CATEGORY(at_logger)
// cf. Q_LOGGING_CATEGORY in logger.cpp

/**************************************************************************************************/

#define qATCritical() qCCritical(at_logger)
#define qATDebug()    qCDebug(at_logger)
#define qATInfo()     qCInfo(at_logger)
#define qATWarning()  qCWarning(at_logger)

/**************************************************************************************************/

// QC_END_NAMESPACE

#endif /* __LOGGER_H__ */
