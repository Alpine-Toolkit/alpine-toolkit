/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "alpine_toolkit.h"

#include <jni.h>

#include <QtAndroidExtras>
#include <QMetaObject>
#include <QtDebug>

#include "service/service.h"
#include "platform_abstraction/platform_abstraction.h"

/**************************************************************************************************/

/*
 * These are the functions that Java part will call directly from Android UI thread.
 *
 * JNIEnv*: reference to JNI environment, which lets you access all the JNI fucntions.
 * jobject: reference to "this" Java object.
 *
 * native functions are declared static
 *
 */

static void
on_permission_granted(JNIEnv * env, jobject obj, jstring j_permission)
{
  QAndroidJniObject string = j_permission;
  QString permission = string.toString();
  qATInfo() << "on_permission_granted" << permission;
  PermissionManager * permission_manager = PlatformAbstraction::instance()->permission_manager();
  // Fixme: cast AndroidPermissionmanager
  // QMetaObject::invokeMethod(permission_manager,
  //                           "on_permission_granted",
  //                           Qt::QueuedConnection,
  //                           permission
  //                           );
}

static void
on_permission_denied(JNIEnv * env, jobject obj, jstring j_permission)
{
  QAndroidJniObject string = j_permission;
  QString permission = string.toString();
  qATInfo() << "on_permission_denied" << permission;
  PermissionManager * permission_manager = PlatformAbstraction::instance()->permission_manager();
  // QMetaObject::invokeMethod(permission_manager,
  //                           "on_permission_denied",
  //                           Qt::QueuedConnection,
  //                           permission
  //                           );
}

static void
stop_service(JNIEnv * env, jobject obj)
{
  qATInfo() << "invoke stop_service";
  // Fixme: ???
  // QMetaObject::invokeMethod(Service::service,
  //                           "stop_service",
  //                           Qt::QueuedConnection
  //                           );
}

/**************************************************************************************************/

// Create a vector with all our JNINativeMethod(s)
static JNINativeMethod methods[] = {
  {"on_permission_granted", "(Ljava/lang/String)V", (void *) on_permission_granted},
  {"on_permission_denied", "(Ljava/lang/String)V", (void *) on_permission_denied},
  {"stop_service", "()V", (void *) stop_service},
};

/**************************************************************************************************/

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
