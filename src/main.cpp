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

#include <cstdlib>

#include <QDir>
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QTranslator>
#include <QtDebug>
#include <QtQml>

/**************************************************************************************************/

#include "startup/startup.h"

/**************************************************************************************************/

// constexpr int EXIT_FAILURE = -1; // also defined in <cstdlib>

int
main(int argc, char *argv[])
{
  // QGuiApplication::setApplicationDisplayName(QCoreApplication::translate("main", "Alpine Toolkit "));
  QGuiApplication::setApplicationName("Alpine Toolkit");
  QGuiApplication::setOrganizationName("FabriceSalvaire"); // overridden ???
  // QGuiApplication::setOrganizationDomain("fabrice-salvaire.fr")
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  // QGuiApplication application(argc, argv);
  QApplication application(argc, argv); // for charts

  QTranslator translator;
  load_translation(application, translator);

  QSettings settings;
  qInfo() << "Settings file path:" << settings.fileName() << settings.format();
  // Settings file path: "/home/fabrice/.config/FabriceSalvaire/Alpine Toolkit.conf" 0
  // Settings file path: "/data/data/org.alpine_toolkit/files/.config/FabriceSalvaire/Alpine Toolkit.conf" 0
  // qputenv("QT_LABS_CONTROLS_STYLE", settings.value("style").toByteArray());

  QDir application_user_directory = create_user_application_directory();

  register_qml_types();

  QQmlApplicationEngine engine;
  qInfo() << "offlineStoragePath" << engine.offlineStoragePath();
  // /home/fabrice/.local/share/FabriceSalvaire/Alpine Toolkit/QML/OfflineStorage
  engine.setOfflineStoragePath(application_user_directory.path());
  QQmlContext * root_context = engine.rootContext();
  set_context_properties(root_context);

  engine.load(QUrl("qrc:/pages/main.qml"));
  if (engine.rootObjects().isEmpty())
    return EXIT_FAILURE;

  // run_before_event_loop(application_user_directory);

  return application.exec();
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
