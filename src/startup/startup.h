// -*- mode: c++ -*-

/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
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
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __STARTUP_H__
#define __STARTUP_H__

/**************************************************************************************************/

#include <QApplication>
#include <QDir>
#include <QGuiApplication>
#include <QQmlContext>
#include <QTranslator>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

QDir create_user_application_directory();
QString copy_file_from_asset(const QDir & destination, const QString & filename);
void load_sqlite(const QDir & application_user_directory);
void load_translation(QGuiApplication & application, QTranslator & translator);
void register_qml_types();
void run_before_event_loop(const QDir & application_user_directory);
void set_context_properties(QQmlContext * context);

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __STARTUP_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
