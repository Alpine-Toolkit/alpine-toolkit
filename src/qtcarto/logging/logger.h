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
