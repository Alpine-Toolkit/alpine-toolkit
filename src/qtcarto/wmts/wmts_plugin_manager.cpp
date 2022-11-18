/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "wmts_plugin_manager.h"
#include "qtcarto.h"

#include "configuration/configuration.h"
#include "providers/artic_web_map/artic_web_map_plugin.h"
#include "providers/austria/austria_plugin.h"
#include "providers/esri/esri_plugin.h"
#include "providers/geoportail/geoportail_plugin.h"
#include "providers/germany/germany_plugin.h"
#include "providers/osm/osm_plugin.h"
#include "providers/spain/spain_plugin.h"
#include "providers/swiss_topo/swiss_topo_plugin.h"

#include <QtDebug>

/**************************************************************************************************/

QcWmtsPluginManager::QcWmtsPluginManager()
{
  // Fixme: plugin name versus title ?
  m_plugin_names
    << QcArticWebMapPlugin::PLUGIN_NAME
    << QcAustriaPlugin::PLUGIN_NAME
    << QcEsriPlugin::PLUGIN_NAME
    << QcGeoportailPlugin::PLUGIN_NAME
    << QcGermanyPlugin::PLUGIN_NAME
    << QcOsmPlugin::PLUGIN_NAME
    << QcSpainPlugin::PLUGIN_NAME
    << QcSwissTopoPlugin::PLUGIN_NAME
    ;
}

QcWmtsPluginManager::~QcWmtsPluginManager()
{
  for (auto * plugin : m_plugins.values())
    delete plugin;
}

QcWmtsPlugin *
QcWmtsPluginManager::operator[](const QString & name)
{
  if (m_plugins.contains(name))
    return m_plugins[name];
  else {
    // Fixme:: use Qt Meta
    // int QMetaObject::indexOfMethod(const char *method) const
    // bool QMetaObject::invokeMethod(QObject *obj, const char *member
    QcWmtsPlugin * plugin = nullptr;
    if (name == QcGeoportailPlugin::PLUGIN_NAME)
      plugin = create_plugin_geoportail();
    else if (name == QcEsriPlugin::PLUGIN_NAME)
      plugin = new QcEsriPlugin();
    else if (name == QcOsmPlugin::PLUGIN_NAME)
      plugin = new QcOsmPlugin();
    else if (name == QcArticWebMapPlugin::PLUGIN_NAME)
      plugin = new QcArticWebMapPlugin();
    else if (name == QcSwissTopoPlugin::PLUGIN_NAME)
      plugin = new QcSwissTopoPlugin();
    else if (name == QcSpainPlugin::PLUGIN_NAME)
      plugin = new QcSpainPlugin();
    else if (name == QcAustriaPlugin::PLUGIN_NAME)
      plugin = new QcAustriaPlugin();
    else if (name == QcGermanyPlugin::PLUGIN_NAME)
      plugin = new QcGermanyPlugin();

    if (plugin)
      m_plugins.insert(plugin->name(), plugin);

    return plugin;
  }
}

QcWmtsPlugin *
QcWmtsPluginManager::create_plugin_geoportail()
{
  QString json_path = QaConfig::instance()->geoportail_token_path();
  QcGeoportailWmtsLicense geoportail_license(json_path);

  return new QcGeoportailPlugin(geoportail_license);
}

/**************************************************************************************************/

// #include "wmts_plugin_manager.moc"
