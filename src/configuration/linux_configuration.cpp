/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "linux_configuration.h"
#include "alpine_toolkit.h"

#include <QDir>
#include <QStandardPaths>
#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QaLinuxConfig::QaLinuxConfig()
  : QaConfig()
{
  QString generic_data_location_path = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
  // qATInfo() << "GenericDataLocation:" << generic_data_location_path;
  // GenericDataLocation = $HOME/.local/share

  application_user_directory(QDir(generic_data_location_path).filePath(CONFIG_DIRECTORY_NAME));
}

QaLinuxConfig::~QaLinuxConfig()
{}

/**************************************************************************************************/

// QC_END_NAMESPACE
