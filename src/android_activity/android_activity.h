// -*- mode: c++ -*-

/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire.
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the QtCarto library.
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
 * $QTCARTO_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef ANDROID_ACTIVITY_H
#define ANDROID_ACTIVITY_H

#include <QObject>

#include "international_morse_code_engine/international_morse_code_engine.h"

/**************************************************************************************************/

class AndroidActivity : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool orientation_lock READ orientation_lock WRITE set_orientation_lock NOTIFY orientation_lockChanged)
  Q_PROPERTY(ScreenOrientation orientation READ orientation WRITE set_orientation NOTIFY orientationChanged)
  Q_PROPERTY(bool full_wave_lock READ full_wave_lock WRITE set_full_wave_lock NOTIFY full_wave_lockChanged)
  Q_PROPERTY(bool torch READ torch WRITE set_torch NOTIFY torchChanged)

public:
  explicit AndroidActivity(QObject *parent = 0);
  ~AndroidActivity();

  enum ScreenOrientation {
    Unspecified = Qt::UserRole + 1,
    Sensor,
    Portrait,
    Landscape,
  };
  typedef ScreenOrientation ScreenOrientation;
  Q_ENUMS(ScreenOrientation)

  void set_orientation_lock(bool orientation_lock);
  bool orientation_lock() const;

  void set_orientation(ScreenOrientation orientation);
  ScreenOrientation orientation() const;

  void set_full_wave_lock(bool full_wave_lock);
  bool full_wave_lock() const;

  void set_torch(bool enabled);
  bool torch() const;

  Q_INVOKABLE void issue_call(const QString & phone_number);
  Q_INVOKABLE void issue_dial(const QString & phone_number);
  Q_INVOKABLE void perform_lamp_signal(const QString & message, int rate_ms); // const if not load_morse_code_engine
  Q_INVOKABLE QString decode_morse(const QString & encoded_message);

signals:
  void orientation_lockChanged();
  void orientationChanged();
  void full_wave_lockChanged();
  void torchChanged();

private slots:
  void update_orientation_lock();
  void update_orientation();
  void update_full_wave_lock();
  void update_torch();

private:
  void load_morse_code_engine();

private:
  bool m_orientation_lock;
  ScreenOrientation m_orientation;
  bool m_full_wave_lock;
  bool m_torch_enabled;
  InternationalMorseCodeEngine * m_morse_code_engine;
};

/**************************************************************************************************/

#endif // ANDROID_ACTIVITY_H

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
