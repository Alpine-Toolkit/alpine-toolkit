// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/**************************************************************************************************/

#include <QByteArray>
#include <QJsonObject>
#include <QString>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcPlatform
{
public:
  // note: ANDROID is a macro
  enum OsType {LinuxOS, AndroidOS, WindowsOS, OsxOS};
  enum ArchitectureType {X86, X86_64, ARM, ARM_64};

public:
  static QcPlatform & instance() {
    // Thread-safe in C++11
    static QcPlatform m_instance;
    return m_instance;
  }

  // Delete copy and move constructors and assign operators
  QcPlatform(QcPlatform const &) = delete;             // Copy construct
  QcPlatform & operator=(QcPlatform const &) = delete; // Copy assign
  QcPlatform(QcPlatform &&) = delete;                  // Move construct
  QcPlatform & operator=(QcPlatform &&) = delete;      // Move assign

  QString os_name() const;
  QString architecture_name() const;

  bool on_linux() const { return m_os_type == LinuxOS; }
  bool on_android() const { return m_os_type == AndroidOS; }
  bool on_windows() const { return m_os_type == WindowsOS; }
  bool on_osx() const { return m_os_type == OsxOS; }

  bool on_x86() const { return m_architecture_type == X86; }
  bool on_x86_64() const { return m_architecture_type == X86_64; }
  bool on_arm() const { return m_architecture_type == ARM; }
  bool on_arm_64() const { return m_architecture_type == ARM_64; }

  QJsonObject to_json() const;

private:
  QcPlatform();
  ~QcPlatform();

private:
  OsType m_os_type;
  ArchitectureType m_architecture_type;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __PLATFORM_H__ */
