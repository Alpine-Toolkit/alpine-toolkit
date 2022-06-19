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

#ifndef __HANDLER_H__
#define __HANDLER_H__

/**************************************************************************************************/

#include <QMessageLogContext>
#include <QString>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

void message_handler(QtMsgType type, const QMessageLogContext & context, const QString & message);

// QC_END_NAMESPACE

#endif /* __HANDLER_H__ */
