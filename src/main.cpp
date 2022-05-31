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

#include "application/application.h"
#include "logging/handler.h"
#include "alpine_toolkit.h"

#include <QDate>

/**************************************************************************************************/

int
main(int argc, char *argv[])
{
  // Fixme: Don't work on Android ???
  //  no logging ???
  // #ifndef ANDROID
  qInstallMessageHandler(message_handler);
  // #endif

  Application & application = Application::create(argc, argv);

  // Fixme: not displayed
  qATInfo() << "Start event loop...";
  return application.exec();

  /*
  if (QDate::currentDate() < QDate(2017, 9, 1))
    return application.exec();
  else {
    qATInfo() << "Out of date";
    return -1;
  }
  */
}
