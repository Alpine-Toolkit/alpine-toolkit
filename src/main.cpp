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
#include <QFile>
#include <QFileInfo>
#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QSqlDatabase>
#include <QStandardPaths>
#include <QTranslator>
#include <QtDebug>
#include <QtQml>

/**************************************************************************************************/

#include "ephemeride/ephemeride.h"
#include "refuge/refuge.h"
#include "satellite_model/satellite_model.h"
#include "sensors/qml_barimeter_altimeter_sensor.h"
#include "sql_model/SqlQueryModel.h"

#ifdef ANDROID
#include "android_activity/android_activity.h"
#endif

/**************************************************************************************************/

void
load_translation(QGuiApplication & application, QTranslator & translator)
{
  QLocale locale;

  if (translator.load(locale, "alpha-ursae-minoris", ".", ":/translations", ".qm")) {
    // :/translations/alpha-ursae-minoris.fr_FR.qml
    qInfo() << "Install translator for locale" << locale.name();
    application.installTranslator(&translator);
  } else {
    qInfo() << "No translator for locale" << locale.name();
  }
}

/**************************************************************************************************/

// QQuickView class provides a window for displaying a Qt Quick user interface
// QQuickView view;
// QSurfaceFormat format = view.format();
// format.setSamples(16);
// view.setFormat(format);
// view.setSource(QUrl("qrc:///..."));
// view.show();

/**************************************************************************************************/

void
register_qml_types()
{
  const char * package = "Local";
  int major = 1;
  int minor = 0;

  // qmlRegisterType<AndroidActivity >(package, major, minor, "AndroidActivity");

  // qmlRegisterSingletonType  <QmlSensorGlobal             >(package, major, minor, "QmlSensors", global_object_50);
  // qmlRegisterUncreatableType<QmlSensorRange              >(package, major, minor, "Range",                QLatin1String("Cannot create Range"));
  // qmlRegisterUncreatableType<QmlSensorOutputRange        >(package, major, minor, "OutputRange",          QLatin1String("Cannot create OutputRange"));
  // qmlRegisterUncreatableType<QmlSensor                   >(package, major, minor, "Sensor",               QLatin1String("Cannot create Sensor"));
  // qmlRegisterUncreatableType<QmlSensorReading            >(package, major, minor, "SensorReading",        QLatin1String("Cannot create SensorReading"));
  qmlRegisterType<QmlBarometerAltimeterSensor >(package, major, minor, "BarimeterAltimeterSensor");
  qmlRegisterUncreatableType<QmlBarometerAltimeterReading >(package, major, minor, "BarimeterAltimeterReading", QLatin1String("Cannot create PressureReading"));

  qmlRegisterType<SatelliteModel>(package, major, minor, "SatelliteModel");

  // qmlRegisterType<Refuge>(package, major, minor, "Refuge");
  // qmlRegisterType<RefugeModel>(package, major, minor, "RefugeModel");

  // qmlRegisterType<Ephemeride>(package, major, minor, "Ephemeride");
}

/**************************************************************************************************/

void
set_context_properties(QQmlContext * context)
{
#ifdef ANDROID
  int on_android = 1;
  AndroidActivity * android_activity = new AndroidActivity(); // parent ?
  context->setContextProperty(QLatin1String("android_activity"), android_activity); // QLatin1String() ???
#else
  int on_android = 0;
#endif
  context->setContextProperty(QLatin1String("on_android"), on_android);

  Ephemeride * ephemeride = new Ephemeride(); // parent ?
  context->setContextProperty(QLatin1String("ephemeride"), ephemeride);

  QList<Refuge> * refuges = new QList<Refuge>();
  load_refuge_json(":/data/ffcam-refuges.json", *refuges);
  // for (const Refuge & refuge : refuges) {
  //   qInfo() << refuge.name();
  // }
  QList<QObject *> refuges_; // QObject* is required
  for (Refuge & refuge : *refuges)
    refuges_.append(&refuge);
  context->setContextProperty("refuge_model", QVariant::fromValue(refuges_));

  // RefugeModel * refuge_model = new RefugeModel(*refuges);
  // context->setContextProperty("refuge_model", refuge_model);
}

/**************************************************************************************************/

QDir
create_user_application_directory()
{
  // on Android
  //   DataLocation = /data/data/org.alpha_ursae_minoris
  //   GenericDataLocation = <USER> = /storage/emulated/0 = user land root
  // on Linux
  //   GenericDataLocation = /home/fabrice/.local/share
  QString generic_data_location_path = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
  qInfo() << "GenericDataLocation:" << generic_data_location_path;
  // /storage/emulated/0/Android/data/org.xxx/files Alarms Download Notifications cache

  QString application_user_directory_path = QDir(generic_data_location_path).filePath("alpha-ursae-minoris");
  QDir application_user_directory(application_user_directory_path);
  if (! application_user_directory.exists()) {
    if (!application_user_directory.mkpath(application_user_directory.absolutePath())) {
      qWarning() << "Cannot create application user directory";
    }
  }

  return application_user_directory;
}

/**************************************************************************************************/

void
run_before_event_loop(const QDir & application_user_directory)
{
  QFile output_file(application_user_directory.filePath("out.txt"));
  if (!output_file.open(QIODevice::WriteOnly | QIODevice::Text))
    qWarning() << "couldn't write to file";
  QTextStream out(&output_file);
  out << "The magic number is: " << 49 << "\n";

  QFile input_file("assets:/file1.txt");
  if (!input_file.open(QIODevice::ReadOnly | QIODevice::Text))
    qWarning() << "couldn't read to file";
  while (!input_file.atEnd()) {
    QByteArray line = input_file.readLine();
    qInfo() << line;
  }
}

/**************************************************************************************************/

// constexpr int EXIT_FAILURE = -1; // also defined in <cstdlib>

int
main(int argc, char *argv[])
{
  // QGuiApplication::setApplicationDisplayName(QCoreApplication::translate("main", "α Ursae Minoris"));
  QGuiApplication::setApplicationName("α Ursae Minoris");
  QGuiApplication::setOrganizationName("FabriceSalvaire"); // overridden ???
  // QGuiApplication::setOrganizationDomain("fabrice-salvaire.fr")
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication application(argc, argv);

  QTranslator translator;
  load_translation(application, translator);

  QSettings settings;
  qInfo() << "Settings file path:" << settings.fileName() << settings.format();
  // Settings file path: "/home/fabrice/.config/FabriceSalvaire/α Ursae Minoris.conf" 0
  // Settings file path: "/data/data/org.alpha_ursae_minoris/files/.config/FabriceSalvaire/α Ursae Minoris.conf" 0
  // qputenv("QT_LABS_CONTROLS_STYLE", settings.value("style").toByteArray());

  QDir application_user_directory = create_user_application_directory();

  register_qml_types();

  QQmlApplicationEngine engine;
  QQmlContext * root_context = engine.rootContext();
  set_context_properties(root_context);

  QString sqlite_path_src_relative("assets:/data/ffcam-refuges.sqlite");
  QFileInfo sqlite_file_info(sqlite_path_src_relative);
  QString sqlite_path_src = sqlite_file_info.absoluteFilePath();
  if (!sqlite_file_info.exists())
    qInfo() << sqlite_path_src << "not found";
  QString sqlite_path_dst = application_user_directory.filePath("ffcam-refuges.sqlite");
  qInfo() << sqlite_path_src << sqlite_path_dst;
  bool copy_success = QFile::copy(sqlite_path_src, sqlite_path_dst);
  qInfo() << "copy:" << copy_success;
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(sqlite_path_dst);
  if (!db.open())
    qInfo() << "database not open"; // db.lastError();
  SqlQueryModel * sql_model = new SqlQueryModel();
  sql_model->set_query("SELECT * FROM refuges", db);
  root_context->setContextProperty("sql_model", sql_model);

  engine.load(QUrl("qrc:/pages/main.qml"));
  if (engine.rootObjects().isEmpty())
    return EXIT_FAILURE;

  run_before_event_loop(application_user_directory);

  return application.exec();
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
