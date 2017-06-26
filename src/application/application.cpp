/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the QtCarto library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "application.h"

#include <algorithm>
#include <cstdlib>

#include <QFile>
#include <QLocale>
#include <QQmlContext>
#include <QStandardPaths>
#include <QUrl>
#include <QtDebug>
#include <QtQml>
// #include <QByteArray>
// #include <QSqlDatabase>
// #include <QSqlError> // Fixme: ???
// #include <QSqlQuery>

// #include "bleaudb/bleau_database.h"
#include "config.h"
#include "camptocamp/camptocamp_client.h"
#include "camptocamp/camptocamp_document.h"
#include "camptocamp/camptocamp_qml.h"
#include "satellite_model/satellite_model.h"
#include "sensors/qml_barimeter_altimeter_sensor.h"
#include "tools/debug_data.h"

/**************************************************************************************************/

QmlApplication::QmlApplication()
{}

QmlApplication::~QmlApplication()
{}

const QString &
QmlApplication::version() const
{
  return ALPINE_TOOLKIT_VERSION;
}

QUrl
QmlApplication::home_page() const
{
  return QUrl(QLatin1String("http://alpine-toolkit.fabrice-salvaire.fr"));
}

/**************************************************************************************************/

Application * Application::m_instance = nullptr;

Application &
Application::create(int & argc, char ** argv)
{
  setup_gui_application();

  m_instance = new Application(argc, argv);

  return *m_instance;
}

/**************************************************************************************************/

Application::Application(int & argc, char ** argv)
  : m_application(argc, argv),
    m_translator(),
    m_settings(),
    m_config(QcConfig::instance()),
    m_engine(),
    m_qml_application()
{
  load_translation();
  m_config.init(); // Fixme: ???
  write_debug_data();
  register_qml_types();
  set_context_properties();
  load_qml_main();

  // Fixme: don't work
  // m_engine.addImportPath(QLatin1String("qrc:///Widgets"));

  run_before_event_loop();
}

void
Application::setup_gui_application()
{
  // Set QGuiApplication statics
  // Must be called before to instanciate Application

  // QGuiApplication::setApplicationDisplayName(QCoreApplication::translate("main", "Alpine Toolkit "));
  QGuiApplication::setApplicationName("Alpine Toolkit");
  QGuiApplication::setOrganizationName("Alpine Toolkit"); // overridden ???
  // QGuiApplication::setOrganizationDomain("alpine-toolkit.org")
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
}

void
Application::load_translation()
{
  QLocale locale;

  if (m_translator.load(locale, "alpine-toolkit", ".", ":/translations", ".qm")) {
    // :/translations/alpine-toolkit.fr_FR.qml
    qInfo() << "Install translator for locale" << locale.name();
    m_application.installTranslator(&m_translator);
  } else {
    qInfo() << "No translator for locale" << locale.name();
  }
}

void
Application::load_settings()
{
  qInfo() << "Settings file path:" << m_settings.fileName() << m_settings.format();

  // Settings file path: "/home/fabrice/.config/FabriceSalvaire/Alpine Toolkit.conf" 0
  // Settings file path: "/data/data/org.alpine_toolkit/files/.config/FabriceSalvaire/Alpine Toolkit.conf" 0
  // qputenv("QT_LABS_CONTROLS_STYLE", settings.value("style").toByteArray());
}

QString
Application::copy_file_from_asset(const QDir & destination, const QString & filename)
{
  // Unused

  QString relative_source_path(QLatin1String("assets:/data/") + filename);
  QFileInfo file_info(relative_source_path);
  QString source_path = file_info.absoluteFilePath();
  if (!file_info.exists())
    qCritical() << "File" << filename << "not found in asset";

  QString destination_path = destination.filePath(filename);

  bool copy_success = QFile::copy(source_path, destination_path);
  if (copy_success) {
    qInfo() << "Copy" << source_path << "to" << destination_path;
    return destination_path;
  } else {
    qCritical() << "Failed to copy" << source_path << "to" << destination_path;
    return QString();
  }
}

void
Application::write_debug_data() const
{
  QcDebugData debug_data;
  debug_data.write_json(m_config.join_application_user_directory(QLatin1Literal("debug_data.json")));
  qInfo() << debug_data.to_json();
}

void
Application::register_qml_types()
{
  const char * package = "Local";
  int major = 1;
  int minor = 0;

#define QmlRegisterType(Type) \
  qmlRegisterType<Type>(package, major, minor, #Type)

#define QmlRegisterType2(Type, Name) \
  qmlRegisterType<Type>(package, major, minor, #Name)

#define QmlRegisterUncreatableType(Type) \
  qmlRegisterUncreatableType<Type>(package, major, minor, #Type, QLatin1String("Cannot create" #Type))

#define QmlRegisterUncreatableType2(Type, Name) \
  qmlRegisterUncreatableType<Type>(package, major, minor, #Name, QLatin1String("Cannot create" #Type))

  // qmlRegisterType<AndroidActivity >(package, major, minor, "AndroidActivity");

  // qmlRegisterSingletonType  <QmlSensorGlobal             >(package, major, minor, "QmlSensors", global_object_50);
  // qmlRegisterUncreatableType<QmlSensorRange              >(package, major, minor, "Range",                QLatin1String("Cannot create Range"));
  // qmlRegisterUncreatableType<QmlSensorOutputRange        >(package, major, minor, "OutputRange",          QLatin1String("Cannot create OutputRange"));
  // qmlRegisterUncreatableType<QmlSensor                   >(package, major, minor, "Sensor",               QLatin1String("Cannot create Sensor"));
  // qmlRegisterUncreatableType<QmlSensorReading            >(package, major, minor, "SensorReading",        QLatin1String("Cannot create SensorReading"));

  QmlRegisterUncreatableType(QmlApplication);

  QmlRegisterType2(QmlBarometerAltimeterSensor, BarometerAltimeterSensor);
  QmlRegisterUncreatableType2(QmlBarometerAltimeterReading, BarometerAltimeterReading);

  QmlRegisterType(SatelliteModel);

  QmlRegisterType(Refuge);
  QmlRegisterUncreatableType(RefugeModel);
  QmlRegisterUncreatableType(RefugeSchemaManager);

  // QmlRegisterType(Ephemeride);

  QmlRegisterType(C2cSearchSettings);
  // qRegisterMetaType(C2cSearchSettings);

  QmlRegisterUncreatableType(C2cDocument);
  QmlRegisterUncreatableType(C2cImage);
  QmlRegisterUncreatableType(C2cRoute);
  QmlRegisterUncreatableType(C2cShortRoute);
  QmlRegisterUncreatableType(C2cSearchResult);
}

void
Application::set_context_properties()
{
  QQmlContext * context = m_engine.rootContext();

  context->setContextProperty(QLatin1String("application"), &m_qml_application);

#ifdef ANDROID
  int on_android = 1;
  context->setContextProperty(QLatin1String("android_activity"), &m_android_activity);
#else
  int on_android = 0;
#endif
  context->setContextProperty(QLatin1String("on_android"), on_android);

  context->setContextProperty(QLatin1String("service"), &m_service_client);
  context->setContextProperty(QLatin1Literal("ephemeride"), &m_ephemeride);

  QString ffcam_refuge_json = ":/data/ffcam-refuges.json";
  m_refuge_schema_manager.load_json(ffcam_refuge_json);
  context->setContextProperty(QLatin1Literal("refuge_schema_manager"), &m_refuge_schema_manager);

  // Create Bleau Model
  // BleauDB * bleaudb = new BleauDB();
  // QString bleau_json_path = ":/data/bleau.json";
  // load_json_bleaudb(bleau_json_path, *bleaudb);
  // QList<QObject *> massifs_; // QObject* is required
  // for (BleauMassif & massif : bleaudb->massifs())
  //   massifs_.append(&massif);
  // std::sort(massifs_.begin(), massifs_.end(),
  //           // qLess<T>()
  //           [](QObject * a, QObject * b) { return qobject_cast<BleauMassif *>(a)->name() < qobject_cast<BleauMassif *>(b)->name(); }
  //           );
  // context->setContextProperty("massif_model", QVariant::fromValue(massifs_));

  // Create Camptocamp client
  QDir offline_storage_path = QDir(context->engine()->offlineStoragePath()); // same as application_user_directory
  QString c2c_api_cache_path = offline_storage_path.absoluteFilePath(QLatin1String("c2c-cache.sqlite"));
  QString c2c_media_cache_path = offline_storage_path.absoluteFilePath(QLatin1String("media"));
  qInfo() << "Camptocamp Cache" << c2c_api_cache_path << c2c_media_cache_path;
  C2cQmlClient * c2c_client = new C2cQmlClient(c2c_api_cache_path, c2c_media_cache_path);
  context->setContextProperty(QLatin1String("c2c_client"), c2c_client);
}

void
Application::set_offline_storage_path()
{
  qInfo() << "offlineStoragePath" << m_engine.offlineStoragePath();
  // /home/fabrice/.local/share/FabriceSalvaire/Alpine Toolkit/QML/OfflineStorage
  m_engine.setOfflineStoragePath(m_config.application_user_directory());
}

void
Application::load_qml_main()
{
  m_engine.load(QUrl("qrc:/qml/main.qml"));

  QList<QObject *> root_objects = m_engine.rootObjects();
  if (root_objects.size() == 1) {
    QObject * application_window = root_objects[0];
    m_can_start = true;

#ifndef ANDROID
    // Set application window size on desktop
    //  use 1900x1200 aspect ratio
    int device_pixel_scale = 3;
    int width = 1200;
    int height = 1900;
    application_window->setProperty("width", width / device_pixel_scale);
    application_window->setProperty("height", height / device_pixel_scale);
#else
    Q_UNUSED(application_window);
#endif
  }
}

int
Application::exec()
{
  if (m_can_start)
    return m_application.exec();
  else
    return EXIT_FAILURE;
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
