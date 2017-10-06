/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
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
** $ALPINE_TOOLKIT_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include "alpine_toolkit.h"

#include <jni.h>

#include <QtAndroidExtras>
#include <QMetaObject>
#include <QtDebug>

#include "service/service_alpine_toolkit.h"
#include "platform_abstraction/platform_abstraction.h"

/**************************************************************************************************/

/*
 * JNIEnv*: reference to JNI environment, which lets you access all the JNI fucntions.
 * jobject: reference to "this" Java object.
 *
 */

// Define our native static functions
// these are the functions that Java part will call directly from Android UI thread

/**************************************************************************************************/

static void
on_permission_granted(JNIEnv * env, jobject obj, jstring j_permission)
{
  QAndroidJniObject string = j_permission;
  QString permission = string.toString();
  qATInfo() << "on_permission_granted" << permission;
  QMetaObject::invokeMethod(PlatformAbstraction::instance(),
                            "on_permission_granted",
                            Qt::QueuedConnection,
                            permission
                            );
}

static void
on_permission_denied(JNIEnv * env, jobject obj, jstring permission)
{
  QAndroidJniObject string = j_permission;
  QString permission = string.toString();
  qATInfo() << "on_permission_denied" << permission;
  QMetaObject::invokeMethod(PlatformAbstraction::instance(),
                            "on_permission_denied",
                            Qt::QueuedConnection,
                            permission
                            );
}

static void
stop_service(JNIEnv * env, jobject obj)
{
  qATInfo() << "invoke stop_service";
  QMetaObject::invokeMethod(ServiceApplication::service,
                            "stop_service",
                            Qt::QueuedConnection
                            );
}

/**************************************************************************************************/

// Create a vector with all our JNINativeMethod(s)
static JNINativeMethod methods[] = {
  {"on_permission_granted", "(Ljava/lang/String)V", (void *) on_permission_granted},
  {"on_permission_denied", "(Ljava/lang/String)V", (void *) on_permission_denied},
  {"stop_service", "()V", (void *) stop_service},
};

// this method is called automatically by Java after the .so file is loaded
JNIEXPORT jint
JNI_OnLoad(JavaVM * vm, void * /*reserved*/)
{
  JNIEnv * env;
  // get the JNIEnv pointer.
  if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK)
    return JNI_ERR;

  // search for Java class which declares the native methods
  jclass javaClass = env->FindClass("org/alpine_toolkit/NativeFunctions");
  if (!javaClass)
    return JNI_ERR;

  // register our native methods
  if (env->RegisterNatives(javaClass, methods, sizeof(methods) / sizeof(methods[0])) < 0)
    return JNI_ERR;

  return JNI_VERSION_1_6;
}
