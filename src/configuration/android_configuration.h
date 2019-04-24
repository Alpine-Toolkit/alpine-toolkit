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
