// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#ifndef ANDROID_PLATFORM_H
#define ANDROID_PLATFORM_H

/**************************************************************************************************/

#include "platform_abstraction/platform_abstraction.h"

/**************************************************************************************************/

class AndroidPlatform : public PlatformAbstraction
{
  Q_OBJECT

public:
  explicit AndroidPlatform(QObject * parent = nullptr);
  ~AndroidPlatform();

  PlatformType platform_type() const override { return Android; }

  Q_INVOKABLE QStringList external_storages() const override;

  Q_INVOKABLE void issue_call(const QString & phone_number) const override;
  Q_INVOKABLE void issue_dial(const QString & phone_number) const override;

  Q_INVOKABLE void perform_lamp_signal(const QString & message, int rate_ms = 250) const override;
  Q_INVOKABLE void stop_lamp_signal() const override;

  Q_INVOKABLE void start_lamp_dimmer(int period, int duty_cycle) const override;
  Q_INVOKABLE void stop_lamp_dimmer() const override;

  void on_permission_granted(const QString & permission);
  void on_permission_denied(const QString & permission);

public slots:
  virtual void update_orientation_lock() override;
  virtual void update_orientation() override;
  virtual void update_full_wave_lock() override;
  virtual void update_torch() override;
};

/**************************************************************************************************/

#endif // ANDROID_PLATFORM_H
