/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include <cstdio>
#include <cstdlib>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QStandardPaths>
#include <QSurfaceFormat>
#include <QtDebug>

/**************************************************************************************************/

#include "configuration/configuration.h"
#include "logging/handler.h"
#include "debug_data/debug_data.h"
#include "platform/platform.h"

#include "declarative_map_item.h"

/**************************************************************************************************/

constexpr char * package = "Local";
constexpr int major = 1;
constexpr int minor = 0;

#define QmlRegisterType(Type) \
  qmlRegisterType<Type>(package, major, minor, #Type)

/**************************************************************************************************/

int
main(int argc, char *argv[])
{
#ifndef ANDROID
  qInstallMessageHandler(message_handler);
#endif

  // QGuiApplication::setApplicationDisplayName(QCoreApplication::translate("main", "Alpine Toolkit "));
  QGuiApplication::setApplicationName("Alpine Toolkit");
  QGuiApplication::setOrganizationName("FabriceSalvaire"); // overridden ???
  // QGuiApplication::setOrganizationDomain("fabrice-salvaire.fr")
  // Fixme:
#ifdef ANDROID
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication application(argc, argv);

  QSurfaceFormat surface_format;
  // surface_format.setSamples(4); // max is 8 ?
  QSurfaceFormat::setDefaultFormat(surface_format);

  QaConfig * config = QaConfig::instance();
  //! config.init();

  // Set environment variable PROJ_LIB for proj4 so as to find (epsg) date files
  setenv("PROJ_LIB", config->application_user_directory().toStdString().c_str(), 1);

  QcDebugData debug_data;
  debug_data.write_json(config->join_application_user_directory(QStringLiteral("debug_data.json")));
  qInfo() << debug_data.to_json();

  QUrl main_page("qrc:/pages/main.qml");

  // to embed QtCarto Module
  QmlRegisterType(QcMapItem);

  QQmlApplicationEngine engine;
  engine.load(main_page);
  if (engine.rootObjects().isEmpty())
    return EXIT_FAILURE;

  for (auto * obj : engine.rootObjects()) {
    QQuickWindow * window = qobject_cast<QQuickWindow *>(obj);
    if (window != NULL) {
      QSurfaceFormat format = window->format();
      qInfo() << "QQuickWindow found" << format;
      // QQuickWindow found QSurfaceFormat(version 2.0, options QFlags(),
      // depthBufferSize 24,
      // redBufferSize 8, greenBufferSize 8, blueBufferSize 8, alphaBufferSize 0,
      // stencilBufferSize 8,
      // samples 4, swapBehavior 2, swapInterval 1, profile  0)
    }
  }

  return application.exec();
}
