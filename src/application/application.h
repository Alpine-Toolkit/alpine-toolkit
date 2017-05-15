// -*- mode: c++ -*-
/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire
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
 * $QTCARTO_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

/**************************************************************************************************/

#include <QApplication>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QTranslator>
// #include <QGuiApplication>

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

  QDir & application_user_directory() { return m_application_user_directory; }
  QSettings & settings() { return m_settings; }

private:
  QString copy_file_from_asset(const QDir & destination, const QString & filename);
  void create_user_application_directory();
  void load_qml_main();
  void load_settings();
  void load_translation();
  void register_qml_types(); // static ???
  void run_before_event_loop();
  void set_context_properties();
  void set_offline_storage_path();
  void setup_gui_application();

protected:
  Application(int & argc, char ** argv);
  ~Application();

private:
  // QGuiApplication m_application;
  QApplication m_application; // for charts
  QTranslator m_translator;
  QSettings m_settings;
  QDir m_application_user_directory;
  QQmlApplicationEngine m_engine;
};

/**************************************************************************************************/

#endif /* __APPLICATION_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
