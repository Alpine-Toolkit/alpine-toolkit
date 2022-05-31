/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine Toolkit software.
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
#include "alpine_toolkit.h"

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
// #include <QSurfaceFormat>

// #include "bleaudb/bleau_database.h"
#include "camptocamp/camptocamp_client.h"
#include "camptocamp/camptocamp_document.h"
#include "camptocamp/camptocamp_qml.h"
#include "platform_abstraction/platform_abstraction.h"
#include "satellite_model/satellite_model.h"
#include "sensors/qml_barimeter_altimeter_sensor.h"
#include "tools/debug_data.h"

#include "declarative_map_item.h"
#include "map_gesture_area.h"

// Fixme:
#include "coordinate/wgs84.h"
#include "geometry/vector.h"
#include "map/location_circle_data.h"
#include "map/map_event_router.h"
#include "map/map_path_editor.h"
#include "map/path_property.h"

/**************************************************************************************************/

QmlApplication::QmlApplication(Application * application)
  : QObject(),
    m_application(application)
    // m_network_configuration_manager()
{
  // m_wifi_state = get_wifi_state();

  // connect(&m_network_configuration_manager, SIGNAL(onlineStateChanged(bool)), this, SLOT(onlineStateChanged(bool)));
  // Fixme: look at https://doc.qt.io/qt-5/qnetworksession.html
  // connect(&m_network_configuration_manager, &QNetworkConfigurationManager::onlineStateChanged,
  //         this, &QmlApplication::onlineStateChanged);
  // connect(&m_network_configuration_manager, &QNetworkConfigurationManager::configurationChanged,
  //         this, &QmlApplication::network_configuration_changed);
}

QmlApplication::~QmlApplication()
{}

QString
QmlApplication::version() const
{
  return m_application->version().toString();
}

QUrl
QmlApplication::home_page() const
{
  return ALPINE_TOOLKIT_URL;
}

/*
void
QmlApplication::network_configuration_changed(const QNetworkConfiguration & config) // unused
{
  qATInfo() << "Network Configuration Changed";
  bool wifi_state = get_wifi_state();
  if (wifi_state != m_wifi_state) {
    m_wifi_state = wifi_state;
    emit wifiStateChanged(wifi_state);
  }
}

bool
QmlApplication::get_wifi_state()
{
  QList<QNetworkConfiguration> network_configurations = m_network_configuration_manager.allConfigurations(QNetworkConfiguration::Active);
  for (const auto & network_configuration : network_configurations) {
    qATInfo() << "Network Configuration" << network_configuration.name() << network_configuration.bearerType() << network_configuration.state();
    auto bearer_type = network_configuration.bearerType();
    if (bearer_type == QNetworkConfiguration::BearerWLAN or
        bearer_type == QNetworkConfiguration::BearerEthernet) {
      qATInfo() << "Wifi is Up";
      return true;
    }
  }

  qATInfo() << "Wifi is Down";
  return false;
}

bool
QmlApplication::is_online() const
{
  return m_network_configuration_manager.isOnline();
}
*/

QaConfig *
QmlApplication::config()
{
  // return QaConfig::instance();
  return m_application->config();
}

QString
QmlApplication::encode_morse(const QString & message, bool use_bit)
{
  return m_application->encode_morse(message, use_bit);
}

QString
QmlApplication::decode_morse(const QString & message)
{
  bool succeed = false;
  QString decoded_message = m_application->decode_morse(message, succeed);
  decoded_message += succeed ? QLatin1String("@T") : QLatin1String("@F");
  return decoded_message;
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
  : QObject(),
    m_application(argc, argv),
    m_translator(),
    m_platform_abstraction(PlatformAbstraction::instance()),
    m_config(QaConfig::instance()),
    m_engine(),
    m_qml_application(this)
{
  qATInfo() << "Create Application for Platform" << m_platform_abstraction->platform_name();

  set_env_variables();
  load_translation();
  register_qml_types();
  set_context_properties();
  load_qml_main();

  // defined in test.cpp
  qATInfo() << "run_before_event_loop";
  run_before_event_loop();

  m_startup_timer = new QTimer(this);
  connect(m_startup_timer, &QTimer::timeout, this, &Application::post_init);
  m_startup_timer->start();

  qATInfo() << "Application ctor done";
}

Application::~Application()
{
  if (m_platform_abstraction)
    delete m_platform_abstraction;

  if (m_morse_code_engine)
    delete m_morse_code_engine;
}

void
Application::setup_gui_application()
{
  // Set QGuiApplication statics
  // Must be called before to instanciate Application

  // QGuiApplication::setApplicationDisplayName(QCoreApplication::translate("main", "Alpine Toolkit "));
  QGuiApplication::setApplicationName(APPLICATION_NAME);
  QGuiApplication::setOrganizationName(ORGANISATION_NAME); // overridden ???
  // QGuiApplication::setOrganizationDomain("alpine-toolkit.org")

  // Qt6: High-DPI scaling is always enabled.
  // QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  // QSurfaceFormat surface_format;
  // surface_format.setSamples(4); // max is 8 ?
  // QSurfaceFormat::setDefaultFormat(surface_format);
}

void
Application::set_env_variables()
{}

void
Application::load_translation()
{
  QLocale locale;

  if (m_translator.load(locale, "alpine-toolkit", ".", ":/translations", ".qm")) {
    // :/translations/alpine-toolkit.fr_FR.qml
    qATInfo() << "Install translator for locale" << locale.name();
    m_application.installTranslator(&m_translator);
  } else {
    qATInfo() << "No translator for locale" << locale.name();
  }
}

/*
QString
Application::copy_file_from_asset(const QDir & destination, const QString & filename)
{
  // Unused, done in android/src/org/alpine_toolkit/AssetHelper.java

  QString relative_source_path(QLatin1String("assets:/data/") + filename);
  QFileInfo file_info(relative_source_path);
  QString source_path = file_info.absoluteFilePath();
  if (!file_info.exists())
    qATCritical() << "File" << filename << "not found in asset";

  QString destination_path = destination.filePath(filename);

  bool copy_success = QFile::copy(source_path, destination_path);
  if (copy_success) {
    qATInfo() << "Copy" << source_path << "to" << destination_path;
    return destination_path;
  } else {
    qATCritical() << "Failed to copy" << source_path << "to" << destination_path;
    return QString();
  }
}
*/

void
Application::write_debug_data() const
{
  QcDebugData debug_data;
  debug_data.write_json(m_config->join_application_user_directory(QStringLiteral("debug_data.json")));
  qATInfo() << debug_data.to_json();
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

  qRegisterMetaType<QcVectorDouble>();
  // Qt6: registration of comparators, and cQDebug and QDataStream streaming operators is done automatically
  // QMetaType::registerEqualsComparator<QcVectorDouble>();

  qRegisterMetaType<QcWgsCoordinate>();
  // QMetaType::registerEqualsComparator<QcWgsCoordinate>();
  // qRegisterAnimationInterpolator<QGeoCoordinate>(q_coordinateInterpolator);

  qRegisterMetaType<QcMapEvent>();
  qRegisterMetaType<QcMapScale>();
  qRegisterMetaType<QcWmtsPluginData>();
  qRegisterMetaType<QcWmtsPluginLayerData>();

  QmlRegisterUncreatableType(QcLocationCircleData);

  QmlRegisterUncreatableType(QcMapPathEditor);

  QmlRegisterUncreatableType(QcPathProperty);

  // QDeclarativeGeoMap
  QmlRegisterType(QcMapItem);

  QmlRegisterUncreatableType(QcMapPinchEvent);
  QmlRegisterUncreatableType(QcMapGestureArea);

  QmlRegisterUncreatableType(QcMapEventRouter);

  // qmlRegisterSingletonType  <QmlSensorGlobal      >(package, major, minor, "QmlSensors", global_object_50);
  // qmlRegisterUncreatableType<QmlSensorRange       >(package, major, minor, "Range",                QLatin1String("Cannot create Range"));
  // qmlRegisterUncreatableType<QmlSensorOutputRange >(package, major, minor, "OutputRange",          QLatin1String("Cannot create OutputRange"));
  // qmlRegisterUncreatableType<QmlSensor            >(package, major, minor, "Sensor",               QLatin1String("Cannot create Sensor"));
  // qmlRegisterUncreatableType<QmlSensorReading     >(package, major, minor, "SensorReading",        QLatin1String("Cannot create SensorReading"));

  QmlRegisterUncreatableType(QmlApplication);
  // QmlRegisterUncreatableType(PlatformAbstraction);

  QmlRegisterType2(QmlBarometerAltimeterSensor, BarometerAltimeterSensor);
  QmlRegisterUncreatableType2(QmlBarometerAltimeterReading, BarometerAltimeterReading);

  QmlRegisterType(SatelliteModel);

  QmlRegisterType(ThirdPartyLicense);
  // QmlRegisterUncreatableType(ThirdPartyLicenseModel);
  QmlRegisterUncreatableType(ThirdPartyLicenseSchemaManager);

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

  context->setContextProperty(QLatin1String("platform_abstraction"), m_platform_abstraction);

  context->setContextProperty(QLatin1String("service"), &m_service_client);
  context->setContextProperty(QStringLiteral("ephemeride"), &m_ephemeride);

  // Lazy loading
  QString third_party_licenses_json = ":/data/third_party_licenses.json"; // embedded in qrc
  m_third_party_license_schema_manager.set_json_path(third_party_licenses_json);
  context->setContextProperty(QStringLiteral("third_party_license_schema_manager"), &m_third_party_license_schema_manager);

  QString refuge_json = ":/data/refuges.json"; // embedded in qrc
  m_refuge_schema_manager.load_json(refuge_json);
  context->setContextProperty(QStringLiteral("refuge_schema_manager"), &m_refuge_schema_manager);

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
  qATInfo() << "Camptocamp Cache Path" << m_config->c2c_api_cache_path() << m_config->c2c_media_cache_path();
  C2cQmlClient * c2c_client = new C2cQmlClient(m_config->c2c_api_cache_path(), m_config->c2c_media_cache_path());
  context->setContextProperty(QLatin1String("c2c_client"), c2c_client);

  m_engine.addImageProvider(QLatin1String("c2c"), new C2cImageProvider(c2c_client));
}

void
Application::set_offline_storage_path()
{
  // Require user directory

  qATInfo() << "Default Offline Storage Path is" << m_engine.offlineStoragePath();
  // ~/.local/share/Alpine Toolkit/Alpine Toolkit/QML/OfflineStorage/

  m_engine.setOfflineStoragePath(m_config->application_user_directory());
}

void
Application::load_qml_main()
{
  qATInfo() << "Load main.qml";

  m_engine.addImportPath(QLatin1String("qrc:///qml"));

  // ASAN: throw new_delete_type_mismatch
  m_engine.load(QUrl("qrc:/qml/main.qml"));
  qATInfo() << "main.qml loaded";

  QList<QObject *> root_objects = m_engine.rootObjects();
  if (root_objects.size() == 1) {
    QObject * application_window = root_objects[0];
    m_can_start = true;

  // for (auto * obj : engine.rootObjects()) {
  //   QQuickWindow * window = qobject_cast<QQuickWindow *>(obj);
  //   if (window != NULL) {
  //     QSurfaceFormat format = window->format();
  //     qATInfo() << "QQuickWindow found" << format;
  //     // QQuickWindow found QSurfaceFormat(version 2.0, options QFlags(),
  //     // depthBufferSize 24,
  //     // redBufferSize 8, greenBufferSize 8, blueBufferSize 8, alphaBufferSize 0,
  //     // stencilBufferSize 8,
  //     // samples 4, swapBehavior 2, swapInterval 1, profile  0)
  //   }
  // }

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

void
Application::load_morse_code_engine()
{
  if (!m_morse_code_engine)
    m_morse_code_engine = new InternationalMorseCodeEngine();
}

QString
Application::encode_morse(const QString & message, bool use_bit)
{
  load_morse_code_engine();
  if (use_bit)
    return m_morse_code_engine->encode(message, true, true);
  else
    return m_morse_code_engine->encode(message);
}

QString
Application::decode_morse(const QString & message, bool & succeed)
{
  load_morse_code_engine();
  return m_morse_code_engine->decode(message, succeed);
}

/**************************************************************************************************/

void
Application::post_init()
{
  // Qt loop is running now

  qATInfo() << "Post Init";

  // Cleanup startup timer
  delete m_startup_timer;
  m_startup_timer = nullptr;

  // connect(m_platform_abstraction, SIGNAL(on_permission_granted(const QString &)),
  //         this, SLOT(on_permission_granted(const QString &)));
  // connect(m_platform_abstraction, SIGNAL(on_permission_denied(const QString &)),
  //         this, SLOT(on_permission_denied(const QString &)));

  setup_user_directory();
}

void
Application::setup_user_directory()
{
  QString user_directory = m_config->application_user_directory();
  qATInfo() << "Setup user directory" << user_directory;

  PermissionManager * permission_manager = m_platform_abstraction->permission_manager();
  if (permission_manager) {
    if (permission_manager->require_write_permission(user_directory)) {
      PermissionManager::PermissionCallback callback = [this](const QString & permission, bool granted) {
        if (granted) {
          qATInfo() << "Write permission granted";
          setup_user_directory_finish();
        } else {
          qATInfo() << "Write permission denied";
          setup_user_directory_finish(true); // use fallback mode
        }
      };
      // async call
      permission_manager->check_permission(QLatin1String("WRITE_EXTERNAL_STORAGE"), callback);
      return;
    }
  } else {
    setup_user_directory_finish();
  }
}

void
Application::setup_user_directory_finish(bool fallback_mode)
{
  // Fixme: fallback_mode is not implemented ???

  QString user_directory = m_config->application_user_directory();
  qATInfo() << "Setup user directory" << user_directory;

  m_config->create_application_user_directory();

  write_debug_data();
  set_offline_storage_path(); // Fixme: ok here ???
}
