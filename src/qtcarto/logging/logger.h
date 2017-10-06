// -*- mode: c++ -*-

/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the QtCarto library.
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

#ifndef __QC_LOGGER_H__
#define __QC_LOGGER_H__

/**************************************************************************************************/

#include <QLoggingCategory>
#include <QMessageLogContext>
#include <QString>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

Q_DECLARE_LOGGING_CATEGORY(qc_logger)

#define qQCCritical() qCCritical(qc_logger)
#define qQCDebug()    qCDebug(qc_logger)
#define qQCInfo()     qCInfo(qc_logger)
#define qQCWarning()  qCWarning(qc_logger)

#define qQCCriticalf(...) qCCritical(qc_logger, __VA_ARGS__)
#define qQCDebugf(...)    qCDebug(qc_logger, __VA_ARGS__)
#define qQCInfof(...)     qCInfo(qc_logger, __VA_ARGS__)
#define qQCWarningf(...)  qCWarning(qc_logger, __VA_ARGS__)

/**************************************************************************************************/

// QC_END_NAMESPACE

#endif /* __QC_LOGGER_H__ */
