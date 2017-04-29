// -*- mode: c++ -*-
/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire
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

#ifndef __JSON_HELPER_H__
#define __JSON_HELPER_H__

/**************************************************************************************************/

#include <QDateTime>
#include <QJsonArray>
#include <QJsonValue>
#include <QStringList>
#include <QUrl>

/**************************************************************************************************/

namespace json_helper {

  QStringList load_string_list(const QJsonArray & json_array);
  inline QStringList load_string_list(const QJsonValue & json_value) {
    return load_string_list(json_value.toArray());
  }

  QJsonArray dump_string_list(const QStringList & string_list);

  inline QDateTime load_datetime(const QJsonValue & json_value) {
    return QDateTime::fromString(json_value.toString());
  }
  inline QString dump_datetime(const QDateTime & datetime) {
    return datetime.toString(Qt::ISODate);
  }

  inline QString dump_url(const QUrl & url) {
    return url.toString();
  }

}

/**************************************************************************************************/

#endif /* __JSON_HELPER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
