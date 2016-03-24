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

#include <QFile>
#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QStandardPaths>
#include <QTranslator>
#include <QtDebug>
#include <QtQml>

/**************************************************************************************************/

#include "sensors/qml_barimeter_altimeter_sensor.h"
#include "satellite_model.h"
#include "ephemeride/ephemeride.h"

#ifdef ANDROID
#include "android_activity.h"
#endif

/**************************************************************************************************/

int
main(int argc, char *argv[])
{
  QGuiApplication::setApplicationDisplayName(QCoreApplication::translate("main", "α Ursae Minoris"));
  QGuiApplication::setApplicationName("α Ursae Minoris");
  QGuiApplication::setOrganizationName("FabriceSalvaire"); // overridden ???
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
  const char * package = "Local";
  int major = 1;
  int minor = 0;

  // qmlRegisterSingletonType  <QmlSensorGlobal             >(package, major, minor, "QmlSensors", global_object_50);
  // qmlRegisterUncreatableType<QmlSensorRange              >(package, major, minor, "Range",                QLatin1String("Cannot create Range"));
  // qmlRegisterUncreatableType<QmlSensorOutputRange        >(package, major, minor, "OutputRange",          QLatin1String("Cannot create OutputRange"));
  // qmlRegisterUncreatableType<QmlSensor                   >(package, major, minor, "Sensor",               QLatin1String("Cannot create Sensor"));
  // qmlRegisterUncreatableType<QmlSensorReading            >(package, major, minor, "SensorReading",        QLatin1String("Cannot create SensorReading"));
  qmlRegisterType<QmlBarometerAltimeterSensor >(package, major, minor, "BarimeterAltimeterSensor");
  qmlRegisterUncreatableType<QmlBarometerAltimeterReading >(package, major, minor, "BarimeterAltimeterReading", QLatin1String("Cannot create PressureReading"));

  qmlRegisterType<SatelliteModel>(package, major, minor, "SatelliteModel");

  // qmlRegisterType<Ephemeride>(package, major, minor, "Ephemeride");
  // qmlRegisterType<AndroidActivity >(package, major, minor, "AndroidActivity");

  QQmlApplicationEngine engine;

#ifdef ANDROID
  int on_android = 1;
  AndroidActivity * android_activity = new AndroidActivity(); // parent ?
  engine.rootContext()->setContextProperty(QLatin1String("android_activity"), android_activity);
#else
  int on_android = 0;
#endif
  engine.rootContext()->setContextProperty(QLatin1String("on_android"), on_android);

  Ephemeride * ephemeride = new Ephemeride(); // parent ?
  engine.rootContext()->setContextProperty(QLatin1String("ephemeride"), ephemeride);

  engine.load(QUrl("qrc:///main.qml"));
  if (engine.rootObjects().isEmpty())
    return -1;

  QString directory = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
  qInfo() << "DataLocation" << directory;
  // DataLocation = /data/data/org.alpha_ursae_minoris
  // GenericDataLocation = <USER> = /storage/emulated/0" // root
  // /storage/emulated/0/Android/data/org.xxx/files Alarms Download Notifications cache
  QFile file(directory + "/out.txt");
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    qWarning() << "couldn't write to file";
  QTextStream out(&file);
  out << "The magic number is: " << 49 << "\n";

  return application.exec();
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
