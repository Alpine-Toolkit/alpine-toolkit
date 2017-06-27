// -*- mode: c++ -*-
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

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

/**************************************************************************************************/

#include <QApplication>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QNetworkConfigurationManager>
#include <QSettings>
#include <QTranslator>
// #include <QGuiApplication>

#include "configuration/configuration.h"
#include "ephemeride/ephemeride.h"
#include "refuge/refuge_schema_manager.h"
#include "service/client.h"

#ifdef ANDROID
#include "android_activity/android_activity.h"
#endif

/**************************************************************************************************/

// Created after Qt Application
class QmlApplication : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString version READ version CONSTANT)
  Q_PROPERTY(QUrl home_page READ home_page CONSTANT)
  Q_PROPERTY(bool online_state READ is_online NOTIFY onlineStateChanged)
  Q_PROPERTY(bool wifi_state READ wifi_state NOTIFY wifiStateChanged)

public:
  QmlApplication();
  ~QmlApplication();

  const QString & version() const;
  QUrl home_page() const;

  bool is_online() const;
  bool wifi_state() const { return m_wifi_state; }

signals:
  void onlineStateChanged(bool is_online);
  void wifiStateChanged(bool wifi_state);

private slots:
  void network_configuration_changed(const QNetworkConfiguration & config);

private:
  bool get_wifi_state();

private:
  QNetworkConfigurationManager m_network_configuration_manager;
  bool m_wifi_state;
};

/**************************************************************************************************/

class Application
{
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

  const QString & application_user_directory() const { return m_config.application_user_directory(); } // Fixme: ???
  QcConfig & config() { return m_config; }

  QSettings & settings() { return m_settings; }

private:
  QString copy_file_from_asset(const QDir & destination, const QString & filename);
  void load_qml_main();
  void load_settings();
  void load_translation();
  void register_qml_types(); // static ???
  void run_before_event_loop();
  void set_context_properties();
  void set_offline_storage_path();
  static void setup_gui_application();
  void write_debug_data() const;

protected:
  Application(int & argc, char ** argv);
  ~Application();

private:
  bool m_can_start = false;
  // QGuiApplication m_application;
  QApplication m_application; // for charts
  QTranslator m_translator;
  QSettings m_settings;
  QcConfig & m_config; // Fixme: singleton ???
  QQmlApplicationEngine m_engine;

#ifdef ANDROID
  AndroidActivity m_android_activity;
#endif
  QmlApplication m_qml_application;
  Ephemeride m_ephemeride;
  RefugeSchemaManager m_refuge_schema_manager;
  ServiceClient m_service_client;
};

/**************************************************************************************************/

#endif /* __APPLICATION_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
