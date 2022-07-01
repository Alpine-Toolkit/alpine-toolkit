// -*- mode: c++ -*-


/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

#ifndef ANDROID_CONFIGURATION_H
#define ANDROID_CONFIGURATION_H

/**************************************************************************************************/

#include "configuration/configuration.h"

/**************************************************************************************************/

class QaAndroidConfig : public QaConfig
{
  Q_OBJECT

public:
  QaAndroidConfig(); // Fixme: can't be private
  ~QaAndroidConfig();

  QString generic_data_location() const;
  QString make_application_user_directory_path(const QString & root_path, bool public_path) const;
};

/**************************************************************************************************/

#endif // ANDROID_CONFIGURATION_H
