/***************************************************************************************************
 **
 ** $QTCARTO_BEGIN_LICENSE:GPL3$
 **
 ** Copyright (C) 2016 Fabrice Salvaire
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
 ** $QTCARTO_END_LICENSE$
 **
 ***************************************************************************************************/

/**************************************************************************************************/

#include <QtQml/QQmlExtensionPlugin>
#include <QtQml/qqml.h>

/**************************************************************************************************/

#include "qtcarto.h"

#include "declarative_map_item.h"
#include "map_gesture_area.h"

// Fixme:
#include "coordinate/wgs84.h"
#include "geometry/vector.h"
#include "map/location_circle_data.h"
#include "map/map_event_router.h"
#include "map/map_path_editor.h"
#include "map/path_property.h"

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QtCartoDeclarativeModule : public QQmlExtensionPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
  // Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0"
  //                   FILE "plugin.json")

 public:
  void registerTypes(const char *uri)
  {
    // Q_ASSERT(uri == QLatin1String("fr.alpine_toolkit.QtCarto"));
    if (QLatin1String(uri) == QLatin1String("QtCarto")) { // fr.alpine_toolkit.

      // @uri QtCarto
      int major = 1;
      int minor = 0;

      // Register the 1.0 types

      qRegisterMetaType<QcVectorDouble>();
      QMetaType::registerEqualsComparator<QcVectorDouble>();

      qRegisterMetaType<QcWgsCoordinate>();
      QMetaType::registerEqualsComparator<QcWgsCoordinate>();
      // qRegisterAnimationInterpolator<QGeoCoordinate>(q_coordinateInterpolator);

      qRegisterMetaType<QcMapEvent>();
      qRegisterMetaType<QcMapScale>();
      qRegisterMetaType<QcWmtsPluginData>();
      qRegisterMetaType<QcWmtsPluginLayerData>();

      qmlRegisterUncreatableType<QcLocationCircleData>(uri, major, minor, "QcLocationCircleData",
                                                       QStringLiteral("QcLocationCircleData is not intended instantiable by developer."));

      qmlRegisterUncreatableType<QcMapPathEditor>(uri, major, minor, "QcMapPathEditor",
                                                  QStringLiteral("QcMapPathEditor is not intended instantiable by developer."));

      qmlRegisterUncreatableType<QcPathProperty>(uri, major, minor, "QcPathProperty",
                                                  QStringLiteral("QcPathProperty is not intended instantiable by developer."));

      // QDeclarativeGeoMap
      qmlRegisterType<QcMapItem>(uri, major, minor, "QcMapItem");

      qmlRegisterUncreatableType<QcMapPinchEvent>(uri, major, minor, "QcMapPinchEvent",
                                                  QStringLiteral("(Map)PinchEvent is not intended instantiable by developer."));
      qmlRegisterUncreatableType<QcMapGestureArea>(uri, major, minor, "QcMapGestureArea",
                                                   QStringLiteral("(Map)GestureArea is not intended instantiable by developer."));

      qmlRegisterUncreatableType<QcMapEventRouter>(uri, major, minor, "QcMapEventRouter",
                                                   QStringLiteral("QcMapEventRouter is not intended instantiable by developer."));

      // registrations below are version independent
    } else {
      qQCDebug() << "Unsupported URI given to load location QML plugin: " << QLatin1String(uri);
    }
  }
};

/**************************************************************************************************/

#include "qtcarto.moc"

// QC_END_NAMESPACE
