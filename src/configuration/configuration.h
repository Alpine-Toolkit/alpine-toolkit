// -*- mode: c++ -*-

/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
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
** $ALPINE_TOOLKIT_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

/**************************************************************************************************/

#include <QProcessEnvironment>
#include <QSettings>
#include <QString>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QaConfig : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool is_mockup_enabled READ is_mockup_enabled CONSTANT) // Fixme: const ?

public:
  static QaConfig & instance() {
    // Thread-safe in C++11
    static QaConfig m_instance;
    return m_instance;
  }

  // Delete copy and move constructors and assign operators
  // QaConfig(QaConfig const &) = delete;             // Copy construct
  // QaConfig & operator=(QaConfig const &) = delete; // Copy assign
  // QaConfig(QaConfig &&) = delete;                  // Move construct
  // QaConfig & operator=(QaConfig &&) = delete;      // Move assign

  void init(); // called in application.cpp

  QSettings & settings() { return m_settings; }

  bool is_mockup_enabled() const { return m_is_mockup_enabled; }

  // public directory
  const QString & application_user_directory() const { return m_application_user_directory; }
  const QString join_application_user_directory(const QString & path) const;

  // WMTS Data
  const QString wmts_cache_directory() const;
  const QString wmts_token_directory() const;
  const QString geoportail_token_path() const;

private:
  QaConfig();
  ~QaConfig();

  void create_directory(const QString path, const QString label) const;
  void load_settings();
  QString get_env(const QString name) const;

private:
  bool m_initialised;
  bool m_is_mockup_enabled;
  QProcessEnvironment m_env;
  QSettings m_settings;
  QString m_application_user_directory;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

#endif /* __CONFIGURATION_H__ */
