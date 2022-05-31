// -*- mode: c++ -*-

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
