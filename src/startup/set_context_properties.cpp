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

#include <QQmlContext>
#include <QtDebug>

#include "startup.h"
#include "ephemeride/ephemeride.h"
#include "refuge/refuge.h"

#ifdef ANDROID
#include "android_activity/android_activity.h"
#endif

/**************************************************************************************************/

void
set_context_properties(QQmlContext * context)
{
#ifdef ANDROID
  int on_android = 1;
  AndroidActivity * android_activity = new AndroidActivity(); // parent ?
  context->setContextProperty(QLatin1String("android_activity"), android_activity); // QLatin1String() ???
#else
  int on_android = 0;
#endif
  context->setContextProperty(QLatin1String("on_android"), on_android);

  Ephemeride * ephemeride = new Ephemeride(); // parent ?
  context->setContextProperty(QLatin1String("ephemeride"), ephemeride);

  QList<Refuge> * refuges = new QList<Refuge>();
  load_refuge_json(":/data/ffcam-refuges.json", *refuges);
  QList<QObject *> refuges_; // QObject* is required
  for (Refuge & refuge : *refuges)
    refuges_.append(&refuge);
  context->setContextProperty("refuge_model", QVariant::fromValue(refuges_));

  // RefugeModel * refuge_model = new RefugeModel(*refuges);
  // context->setContextProperty("refuge_model", refuge_model);
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
