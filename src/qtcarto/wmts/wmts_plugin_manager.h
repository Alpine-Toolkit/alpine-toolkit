// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __QC_WMTS_PLUGIN_MANAGER_H__
#define __QC_WMTS_PLUGIN_MANAGER_H__

/**************************************************************************************************/

#include <QObject>
#include <QHash>

#include "wmts/wmts_plugin.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/// The QcWmtsPluginManager singleton class implements a WMTS plugin manager.
/// It provides the list of available plugins and to lazy instantiate a plugin.
class QcWmtsPluginManager : QObject
{
public:
  static QcWmtsPluginManager & instance() {
    // Thread-safe in C++11
    static QcWmtsPluginManager m_instance;
    return m_instance;
  }

  // Delete copy and move constructors and assign operators
  QcWmtsPluginManager(QcWmtsPluginManager const &) = delete;             // Copy construct
  QcWmtsPluginManager & operator=(QcWmtsPluginManager const &) = delete; // Copy assign
  QcWmtsPluginManager(QcWmtsPluginManager &&) = delete;                  // Move construct
  QcWmtsPluginManager & operator=(QcWmtsPluginManager &&) = delete;      // Move assign

  QList<QcWmtsPlugin *> plugins() const { return m_plugins.values(); }
  const QList<QString> & plugin_names() const { return m_plugin_names; }

  QcWmtsPlugin * operator[](const QString & name);

private:
  QcWmtsPluginManager();
  ~QcWmtsPluginManager();

  QcWmtsPlugin * create_plugin_geoportail();

private:
  QList<QString> m_plugin_names;
  QHash<QString, QcWmtsPlugin *> m_plugins;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_WMTS_PLUGIN_MANAGER_H__ */
