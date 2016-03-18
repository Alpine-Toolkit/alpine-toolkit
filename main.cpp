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

#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QTranslator>
#include <QtQml>

#include <QtDebug>

/**************************************************************************************************/

#include "sensors/qml_barimeter_altimeter_sensor.h"

/**************************************************************************************************/

int
main(int argc, char *argv[])
{
  QGuiApplication::setApplicationDisplayName(QCoreApplication::translate("main", "α Ursae Minoris"));
  QGuiApplication::setOrganizationName("QtProject");
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication application(argc, argv);

  QTranslator translator;
  QLocale locale;
  if (translator.load(locale, "alpha-ursae-minoris", ".", ":/translations", ".qm")) {
    // :/translations/alpha-ursae-minoris.fr_FR.qml
    qInfo() << "Install translator for" << locale.name();
    application.installTranslator(&translator);
  } else {
    qInfo() << "No translator for" << locale.name();
  }

  QSettings settings;
  qputenv("QT_LABS_CONTROLS_STYLE", settings.value("style").toByteArray());

  // QQuickView class provides a window for displaying a Qt Quick user interface
  // QQuickView view;
  // QSurfaceFormat format = view.format();
  // format.setSamples(16);
  // view.setFormat(format);
  // view.setSource(QUrl("qrc:///..."));
  // view.show();

  // Register QML Types
  const char * package = "QtCarto";
  int major = 1;
  int minor = 0;
  // qmlRegisterSingletonType  <QmlSensorGlobal             >(package, major, minor, "QmlSensors", global_object_50);
  // qmlRegisterUncreatableType<QmlSensorRange              >(package, major, minor, "Range",                QLatin1String("Cannot create Range"));
  // qmlRegisterUncreatableType<QmlSensorOutputRange        >(package, major, minor, "OutputRange",          QLatin1String("Cannot create OutputRange"));
  // qmlRegisterUncreatableType<QmlSensor                   >(package, major, minor, "Sensor",               QLatin1String("Cannot create Sensor"));
  // qmlRegisterUncreatableType<QmlSensorReading            >(package, major, minor, "SensorReading",        QLatin1String("Cannot create SensorReading"));
  qmlRegisterType<QmlBarometerAltimeterSensor >(package, major, minor, "BarimeterAltimeterSensor");
  qmlRegisterUncreatableType<QmlBarometerAltimeterReading >(package, major, minor, "BarimeterAltimeterReading", QLatin1String("Cannot create PressureReading"));

  QQmlApplicationEngine engine;
  engine.load(QUrl("qrc:///main.qml"));
  if (engine.rootObjects().isEmpty())
    return -1;

  return application.exec();
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
