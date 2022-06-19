/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "alpine_toolkit.h"
#include "application/application.h"
#include "logging/handler.h"

#include <QDate>

/**************************************************************************************************/

int
main(int argc, char * argv[])
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
