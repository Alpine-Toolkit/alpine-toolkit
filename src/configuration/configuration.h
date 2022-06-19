// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
  Q_PROPERTY(bool is_storage_enabled READ is_storage_enabled)

public:
  static QaConfig * instance();

  // Delete copy and move constructors and assign operators
  // QaConfig(QaConfig const &) = delete;             // Copy construct
  // QaConfig & operator=(QaConfig const &) = delete; // Copy assign
  // QaConfig(QaConfig &&) = delete;                  // Move construct
  // QaConfig & operator=(QaConfig &&) = delete;      // Move assign

public:
  void create_application_user_directory(); // called in application.cpp

  QSettings & settings() { return m_settings; }

  bool is_mockup_enabled() const { return m_is_mockup_enabled; }
  bool is_storage_enabled() const { return m_is_storage_enabled; }

  // public directory
  void application_user_directory(const QString & path) { m_application_user_directory = path; }
  const QString & application_user_directory() const { return m_application_user_directory; }
  const QString join_application_user_directory(const QString & path) const;

  // WMTS Data
  const QString wmts_cache_directory() const;
  const QString wmts_token_directory() const;
  const QString geoportail_token_path() const;

  // Camptocamp
  const QString c2c_cache_path() const;
  const QString c2c_api_cache_path() const;
  const QString c2c_media_cache_path() const;

protected:
  QaConfig();
  ~QaConfig();

private:
  void create_directory(const QString path, const QString label) const;
  void load_settings();
  QString get_env(const QString name) const;

private:
  bool m_is_mockup_enabled;
  bool m_is_storage_enabled;
  QProcessEnvironment m_env;
  QSettings m_settings;
  QString m_application_user_directory;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

#endif /* __CONFIGURATION_H__ */
