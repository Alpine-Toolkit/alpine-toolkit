// -*- mode: c++ -*-
/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

/**************************************************************************************************/

#include <QApplication>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <QTranslator>
// #include <QGuiApplication>

#include "config.h"
#include "configuration/configuration.h"
#include "ephemeride/ephemeride.h"
#include "international_morse_code_engine/international_morse_code_engine.h"
#include "platform_abstraction/platform_abstraction.h"
#include "refuge/refuge_schema_manager.h"
#include "service/client.h"
#include "third_party_license/third_party_license_schema_manager.h"

/**************************************************************************************************/

class Application;

// Created after Qt Application
class QmlApplication : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString version READ version CONSTANT)
  Q_PROPERTY(QUrl home_page READ home_page CONSTANT)
  Q_PROPERTY(QaConfig* config READ config CONSTANT)
  // Q_PROPERTY(bool online_state READ is_online NOTIFY onlineStateChanged)
  // Q_PROPERTY(bool wifi_state READ wifi_state NOTIFY wifiStateChanged)

public:
  QmlApplication(Application * application);
  ~QmlApplication();

  Q_INVOKABLE QString encode_morse(const QString & message, bool use_bit);
  Q_INVOKABLE QString decode_morse(const QString & message);

signals:
  // void onlineStateChanged(bool is_online);
  // void wifiStateChanged(bool wifi_state);

private slots:
  // void network_configuration_changed(const QNetworkConfiguration & config);

private:
  QString version() const;
  QUrl home_page() const;
  QaConfig * config();
  // bool is_online() const;
  // bool wifi_state() const { return m_wifi_state; }
  // bool get_wifi_state();

private:
  Application * m_application;
  // QNetworkConfigurationManager m_network_configuration_manager;
  bool m_wifi_state;
};

/**************************************************************************************************/

class Application : public QObject
{
  Q_OBJECT

private:
  static Application * m_instance;

public:
  // Startup: call create then instance
  static Application & create(int & argc, char ** argv);
  static Application & instance() { return *m_instance; } // /!\ *nullptr !!!

public:
  // delete copy and move constructors and assign operators
  Application(const Application &) = delete;
  Application(Application &&) = delete;
  Application & operator=(const Application &) = delete;
  Application & operator=(Application &&) = delete;

  int exec();

  QmlApplication * qml_application() { return &m_qml_application; }

  const QString & application_user_directory() const { return m_config->application_user_directory(); } // Fixme: ???
  QaConfig * config() { return m_config; }
  QSettings & settings() { return m_config->settings(); }

  // Fixme: config.h
  const QVersionNumber & version() const { return ALPINE_TOOLKIT_VERSION; }

  QString encode_morse(const QString & message, bool use_bit);
  QString decode_morse(const QString & message, bool & succeed);

  QString tr(const char * message) const { return m_application.tr(message); }

private slots:
  void post_init();

private:
  // QString copy_file_from_asset(const QDir & destination, const QString & filename);
  void load_qml_main();
  void load_translation();
  void register_qml_types(); // static ???
  void run_before_event_loop();
  void set_context_properties();
  void set_offline_storage_path();
  void set_env_variables();
  static void setup_gui_application();
  void write_debug_data() const;
  void load_morse_code_engine();
  void setup_user_directory();
  void setup_user_directory_finish(bool fallback_mode = false);

protected:
  Application(int & argc, char ** argv);
  ~Application();

private:
  bool m_can_start = false;
  // QGuiApplication m_application;
  QApplication m_application; // for charts
  QTranslator m_translator;
  PlatformAbstraction * m_platform_abstraction = nullptr; // singleton
  QaConfig * m_config; // singleton
  QQmlApplicationEngine m_engine;
  QmlApplication m_qml_application;
  QTimer * m_startup_timer = nullptr;

  InternationalMorseCodeEngine * m_morse_code_engine = nullptr; // lazy loading
  ThirdPartyLicenseSchemaManager m_third_party_license_schema_manager;
  Ephemeride m_ephemeride;
  RefugeSchemaManager m_refuge_schema_manager;
  ServiceClient m_service_client;
};

/**************************************************************************************************/

#endif /* __APPLICATION_H__ */
