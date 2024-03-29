// -*- mode: c++ -*-

/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire.
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine Toolkit software.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef PLATFORM_ABSTRACTION_H
#define PLATFORM_ABSTRACTION_H

#include "platform_abstraction/permission_manager.h"

#include <QObject>
#include <QString>
#include <QStringList>

/**************************************************************************************************/

class PlatformAbstraction : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool platform_type READ platform_type CONSTANT)
  Q_PROPERTY(bool orientation_lock READ orientation_lock WRITE set_orientation_lock NOTIFY orientation_lockChanged)
  Q_PROPERTY(ScreenOrientation orientation READ orientation WRITE set_orientation NOTIFY orientationChanged)
  Q_PROPERTY(bool full_wave_lock READ full_wave_lock WRITE set_full_wave_lock NOTIFY full_wave_lockChanged)
  Q_PROPERTY(bool torch READ torch WRITE set_torch NOTIFY torchChanged)
  Q_PROPERTY(PermissionManager* permission_manager READ permission_manager)

public:
  // Fixme: versus tools/platform.h
  enum PlatformType {
    Linux = Qt::UserRole, // 256 = 0x0100
    Windows,              // 257
    OSX,                  // 258
    Android,              // 259
    AndroidFake,          // 260
    IOS,                  // 261
  };
  typedef PlatformType PlatformType;
  Q_ENUMS(PlatformType)

  enum ScreenOrientation {
    Unspecified = Qt::UserRole + 1,
    Sensor,
    Portrait,
    Landscape,
  };
  typedef ScreenOrientation ScreenOrientation;
  Q_ENUMS(ScreenOrientation)

public:
  static PlatformAbstraction * instance();

public:
  explicit PlatformAbstraction(QObject * parent = nullptr);
  ~PlatformAbstraction();

  virtual PlatformType platform_type() const = 0;
  QString platform_name() const;
  Q_INVOKABLE bool on_android() const { return platform_type() == Android; }
  Q_INVOKABLE bool on_android_fake() const { return platform_type() == AndroidFake; }
  Q_INVOKABLE bool on_ios() const { return platform_type() == IOS; }
  Q_INVOKABLE bool on_linux() const { return platform_type() == Linux; }
  Q_INVOKABLE bool on_osx() const { return platform_type() == OSX; }
  Q_INVOKABLE bool on_windows() const { return platform_type() == Windows; }

  PermissionManager * permission_manager() { return m_permission_manager; }

  Q_INVOKABLE bool has_external_storages() const { return external_storages().size(); }
  Q_INVOKABLE virtual QStringList external_storages() const { return QStringList(); }

  bool is_directory_writable(const QString & path) const;

  void set_orientation_lock(bool orientation_lock);
  bool orientation_lock() const;

  void set_orientation(ScreenOrientation orientation);
  ScreenOrientation orientation() const;

  void set_full_wave_lock(bool full_wave_lock);
  bool full_wave_lock() const;

  void set_torch(bool enabled);
  bool torch() const;

  virtual Q_INVOKABLE void issue_call(const QString & phone_number) const;
  virtual Q_INVOKABLE void issue_dial(const QString & phone_number) const;

  virtual Q_INVOKABLE void perform_lamp_signal(const QString & message, int rate_ms = 250) const;
  virtual Q_INVOKABLE void stop_lamp_signal() const;

  virtual Q_INVOKABLE void start_lamp_dimmer(int period, int duty_cycle) const;
  virtual Q_INVOKABLE void stop_lamp_dimmer() const;

protected slots:
  virtual void update_orientation_lock();
  virtual void update_orientation();
  virtual void update_full_wave_lock();
  virtual void update_torch();

signals:
  // Fixme: _changed ???
  void orientation_lockChanged();
  void orientationChanged();
  void full_wave_lockChanged();
  void torchChanged();

protected:
  PermissionManager * m_permission_manager = nullptr;
  bool m_orientation_lock;
  ScreenOrientation m_orientation;
  bool m_full_wave_lock;
  bool m_torch_enabled;
};

/**************************************************************************************************/

#endif // PLATFORM_ABSTRACTION_H
