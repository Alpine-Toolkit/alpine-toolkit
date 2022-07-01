/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#include "platform_abstraction.h"
#include "alpine_toolkit.h"

#ifdef ON_LINUX
#include "platform_abstraction/linux_platform.h"
#include "platform_abstraction/android_fake_platform.h"
#endif

#ifdef ON_ANDROID
#include "platform_abstraction/android_platform.h"
#endif

#include <QDir>
#include <QFile>
#include <QProcessEnvironment>
#include <QUuid>
#include <QtDebug>

/**************************************************************************************************/

PlatformAbstraction *
PlatformAbstraction::instance()
{
  static PlatformAbstraction * _instance = nullptr;

  if (!_instance) {
#ifdef ON_LINUX
    QProcessEnvironment m_env = QProcessEnvironment::systemEnvironment();
    QString value = m_env.value(QStringLiteral("ALPINE_TOOLKIT_FAKE_ANDROID"));
    if (value == QStringLiteral("TRUE"))
      _instance = new AndroidFakePlatform();
    else
      _instance = new LinuxPlatform();
#endif

#ifdef ON_ANDROID
    _instance = new AndroidPlatform();
#endif
  }

  return _instance;
}

/**************************************************************************************************/

PlatformAbstraction::PlatformAbstraction(QObject * parent)
  : QObject(parent),
    m_orientation_lock(false),
    m_orientation(Unspecified),
    m_full_wave_lock(false),
    m_torch_enabled(false)
{
  connect(this, SIGNAL(orientation_lockChanged()), this, SLOT(update_orientation_lock()));
  connect(this, SIGNAL(orientationChanged()), this, SLOT(update_orientation()));
  connect(this, SIGNAL(full_wave_lockChanged()), this, SLOT(update_full_wave_lock()));
  connect(this, SIGNAL(torchChanged()), this, SLOT(update_torch()));
}

PlatformAbstraction::~PlatformAbstraction()
{}

/**************************************************************************************************/

QString
PlatformAbstraction::platform_name() const
{
  switch (platform_type()) {
  case Linux:
    return QStringLiteral("Linux");
  case Windows:
    return QStringLiteral("Windows");
  case OSX:
    return QStringLiteral("OSX");
  case Android:
    return QStringLiteral("Android");
  case AndroidFake:
    return QStringLiteral("FakeAndroid");
  case IOS:
    return QStringLiteral("IOS");
  default:
    return QStringLiteral("unknown");
  };
}

/**************************************************************************************************/

bool
PlatformAbstraction::is_directory_writable(const QString & path) const
{
  // The shared cache may not be writable when application isolation is enforced.
  // static bool cache_directory_writable = false; // static for later use
  // static bool cache_directory_writable_checked = false;
  // if (!cache_directory_writable_checked) {
  //   cache_directory_writable_checked = true;
  // }

  // Android ???
  // https://developer.android.com/reference/java/io/File.html  canWrite()
  // https://stackoverflow.com/questions/23289669/android-read-only-storage-behaves-like-writable

  // Create path and try to write a temporary file
  if (not QDir::root().mkpath(path))
    return false;
  QString filename = QDir(path).filePath(QStringLiteral(".") + QUuid().toString());
  QFile tmp_file(filename);
  bool writable = tmp_file.open(QIODevice::WriteOnly);
  if (writable)
    tmp_file.remove();

  return writable;
}

/**************************************************************************************************/

void
PlatformAbstraction::set_orientation_lock(bool orientation_lock)
{
  qATInfo() << "set_orientation_lock" << orientation_lock;

  if (m_orientation_lock != orientation_lock) {
     m_orientation_lock = orientation_lock;
     emit orientation_lockChanged();
  }
}

bool
PlatformAbstraction::orientation_lock() const
{
  return m_orientation_lock;
}

void
PlatformAbstraction::update_orientation_lock()
{
  qATInfo() << "update_orientation_lock" << m_orientation_lock;

  /*
    if (m_orientation_lock)
    ;
    else
    ;
  */
}

/**************************************************************************************************/

void
PlatformAbstraction::set_orientation(PlatformAbstraction::ScreenOrientation orientation)
{
  qATInfo() << "set_orientation" << orientation;

  if (m_orientation != orientation) {
    m_orientation = orientation;
    emit orientationChanged();
  }
}

PlatformAbstraction::ScreenOrientation
PlatformAbstraction::orientation() const
{
  return m_orientation;
}

void
PlatformAbstraction::update_orientation()
{
  qATInfo() << "update_orientation" << m_orientation;

  /*
  switch (m_orientation) {
  case Portrait:
    ;
  case Landscape:
    ;
  case Sensor:
  default:
    ;
  }
  */
}

/**************************************************************************************************/

void
PlatformAbstraction::set_full_wave_lock(bool full_wave_lock)
{
  qATInfo() << "set_full_wave_lock" << full_wave_lock;

  if (m_full_wave_lock != full_wave_lock) {
    m_full_wave_lock = full_wave_lock;
    emit full_wave_lockChanged();
  }
}

bool
PlatformAbstraction::full_wave_lock() const
{
  return m_full_wave_lock;
}

void
PlatformAbstraction::update_full_wave_lock()
{
  qATInfo() << "update_full_wave_lock" << m_full_wave_lock;

  /*
  if (m_full_wave_lock)
    ;
  else
    ;
  */
}

/**************************************************************************************************/

void
PlatformAbstraction::set_torch(bool enabled)
{
  qATInfo() << "set_torch" << enabled;

  if (m_torch_enabled != enabled) {
    m_torch_enabled = enabled;
    emit torchChanged();
  }
}

bool
PlatformAbstraction::torch() const
{
  return m_torch_enabled;
}

void
PlatformAbstraction::update_torch()
{
  qATInfo() << "update_torch" << m_torch_enabled;
}

/**************************************************************************************************/

void
PlatformAbstraction::issue_call(const QString & phone_number) const
{
  qATInfo() << "issue_call" << phone_number;
}

void
PlatformAbstraction::issue_dial(const QString & phone_number) const
{
  qATInfo() << "issue_dial" << phone_number;
}

/**************************************************************************************************/

void
PlatformAbstraction::perform_lamp_signal(const QString & message, int rate_ms) const
{
  qATInfo() << "perform_lamp_signal" << message << rate_ms;
}

void
PlatformAbstraction::stop_lamp_signal() const
{
  qATInfo() << "stop_lamp_signal";
}

void
PlatformAbstraction::start_lamp_dimmer(int period, int duty_cycle) const
{
  qATInfo() << "start_lamp_dimmer" << period << duty_cycle;
}

void
PlatformAbstraction::stop_lamp_dimmer() const
{
  qATInfo() << "stop_lamp_dimmer";
}
