/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
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
** $ALPINE_TOOLKIT_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include "platform.h"
#include "alpine_toolkit.h"

#include <QApplication>
#include <QScreen>
#include <QSslSocket>
#include <QSysInfo>
// #include <QGuiApplication>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

QcPlatform::QcPlatform()
{
#ifdef ON_LINUX
  m_os_type = LinuxOS;
#endif
#ifdef ON_ANDROID
  m_os_type = AndroidOS;
#endif
#ifdef ON_WINDOWS
  m_os_type = WindowsOS;
#endif
}

QcPlatform::~QcPlatform()
{}

QString
QcPlatform::os_name() const
{
  switch (m_os_type) {
  case LinuxOS:
    return QStringLiteral("linux");
  case AndroidOS:
    return QStringLiteral("android");
  case WindowsOS:
    return QStringLiteral("windows");
  case OsxOS:
    return QStringLiteral("osx");
  }
  // -Wreturn-type
}

QString
QcPlatform::architecture_name() const
{
  switch (m_architecture_type) {
  case X86:
    return QStringLiteral("x86");
  case X86_64:
    return QStringLiteral("x86_64");
  case ARM:
    return QStringLiteral("arm");
  case ARM_64:
    return QStringLiteral("arm_64");
  }
  // -Wreturn-type
}

QJsonObject
QcPlatform::to_json() const
{
  QJsonObject platform_object;
  platform_object[QStringLiteral("os")] = os_name();
  platform_object[QStringLiteral("architecture")] = architecture_name();
  platform_object[QStringLiteral("build_abi")] = QSysInfo::buildAbi();
  platform_object[QStringLiteral("build_cpu_architecture")] = QSysInfo::buildCpuArchitecture();
  platform_object[QStringLiteral("current_cpu_architecture")] = QSysInfo::currentCpuArchitecture();
  platform_object[QStringLiteral("product_type")] = QSysInfo::productType();
  platform_object[QStringLiteral("product_version")] = QSysInfo::productVersion();
  platform_object[QStringLiteral("pretty_product_name")] = QSysInfo::prettyProductName();
  // https://doc.qt.io/qt-5/qsysinfo-obsolete.html
  // if (on_windows())
  //   platform_object[QStringLiteral("windows_version")] = QSysInfo::windowsVersion();
  // if (on_osx())
  //   platform_object[QStringLiteral("osx_version")] = QSysInfo::macVersion();
  // platform_object[QStringLiteral("pretty_product_name")] = QSslSocket::supportsSsl();

  // QGuiApplication * application = static_cast<QGuiApplication *>(QGuiApplication::instance());
  QApplication * application = static_cast<QApplication *>(QApplication::instance());

  QJsonObject screens_object;
  for (const auto * screen : application->screens()) {
    QJsonObject screen_object;
    screen_object[QStringLiteral("device_pixel_ratio")] = screen->devicePixelRatio();
    QSize resolution = screen->size();
    QSizeF physical_size = screen->physicalSize();
    screen_object[QStringLiteral("resolution")] =
      QString::number(resolution.width()) + 'x' + QString::number(resolution.height()) + QStringLiteral(" px");
    screen_object[QStringLiteral("screen_format_px")] = resolution.width() / float(resolution.height());
    screen_object[QStringLiteral("physical_size")] =
      QString::number(physical_size.width()) + 'x' + QString::number(physical_size.height()) + QStringLiteral(" mm");
    screen_object[QStringLiteral("screen_format_mm")] = physical_size.width() / physical_size.height();
    screen_object[QStringLiteral("physical_dots_per_inch_x")] = screen->physicalDotsPerInchX();
    screen_object[QStringLiteral("physical_dots_per_inch_y")] = screen->physicalDotsPerInchY();
    screen_object[QStringLiteral("logical_dots_per_inch_x")] = screen->logicalDotsPerInchX();
    screen_object[QStringLiteral("logical_dots_per_inch_y")] = screen->logicalDotsPerInchY();
    screens_object[screen->name()] = screen_object;
  }
  platform_object[QStringLiteral("screens")] = screens_object;

  return platform_object;
}

/**************************************************************************************************/

// QC_END_NAMESPACE
