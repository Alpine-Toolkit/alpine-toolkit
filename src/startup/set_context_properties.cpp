/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the QtCarto library.
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

#include <algorithm>

#include <QDir>
#include <QQmlContext>
#include <QQmlEngine>
#include <QtDebug>

#include "bleaudb/bleaudb.h"
#include "bleaudb/bleaudb_json_loader.h"
#include "camptocamp/camptocamp_qml.h"
#include "ephemeride/ephemeride.h"
#include "refuge/refuge.h"
#include "startup.h"

#include "service/client.h"

#ifdef ANDROID
#include "android_activity/android_activity.h"
#endif

/**************************************************************************************************/

void
set_context_properties(QQmlContext * context)
{
  // Create Android helper instances
#ifdef ANDROID
  int on_android = 1;
  AndroidActivity * android_activity = new AndroidActivity(); // parent ?
  context->setContextProperty(QLatin1String("android_activity"), android_activity); // QLatin1String() ???
#else
  int on_android = 0;
#endif
  context->setContextProperty(QLatin1String("on_android"), on_android);

  // Create Ephemeride instance
  Ephemeride * ephemeride = new Ephemeride(); // parent ?
  context->setContextProperty(QLatin1Literal("ephemeride"), ephemeride);

  // Create FFCAM Refuge Model
  QList<Refuge> * refuges = new QList<Refuge>();
  QString ffcam_refuge_json = ":/data/ffcam-refuges.json";
  load_refuge_json(ffcam_refuge_json, *refuges);
  QList<QObject *> refuges_; // QObject* is required
  for (Refuge & refuge : *refuges)
    refuges_.append(&refuge);
  context->setContextProperty("refuge_model", QVariant::fromValue(refuges_));

  // Create Bleau Model
  BleauDB * bleaudb = new BleauDB();
  QString bleau_json_path = ":/data/bleau.json";
  load_json_bleaudb(bleau_json_path, *bleaudb);
  QList<QObject *> massifs_; // QObject* is required
  for (BleauMassif & massif : bleaudb->massifs())
    massifs_.append(&massif);
  std::sort(massifs_.begin(), massifs_.end(),
            // qLess<T>()
            [](QObject * a, QObject * b) { return qobject_cast<BleauMassif *>(a)->name() < qobject_cast<BleauMassif *>(b)->name(); }
            );
  context->setContextProperty("massif_model", QVariant::fromValue(massifs_));

  // Create Camptocamp client
  QDir offline_storage_path = QDir(context->engine()->offlineStoragePath()); // same as application_user_directory
  QString c2c_api_cache_path = offline_storage_path.absoluteFilePath(QLatin1String("c2c-cache.sqlite"));
  QString c2c_media_cache_path = offline_storage_path.absoluteFilePath(QLatin1String("media"));
  qInfo() << "Camptocamp Cache" << c2c_api_cache_path << c2c_media_cache_path;
  C2cQmlClient * c2c_client = new C2cQmlClient(c2c_api_cache_path, c2c_media_cache_path);
  context->setContextProperty(QLatin1String("c2c_client"), c2c_client);

  // RefugeModel * refuge_model = new RefugeModel(*refuges);
  // context->setContextProperty("refuge_model", refuge_model);

  // Create Service Client
  ServiceClient * service_client = new ServiceClient();
  context->setContextProperty(QLatin1String("service"), service_client);
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
