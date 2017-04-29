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

#include "bleaudb/bleaudb_json_helper.h"

/**************************************************************************************************/

namespace bleaudb {

  QGeoCoordinate
  load_json_coordinate(const QJsonObject & json_object)
  {
    QJsonObject json_coordinate = json_object[QLatin1Literal("coordinate")].toObject();
    double longitude = json_coordinate[QLatin1Literal("longitude")].toDouble();
    double latitude = json_coordinate[QLatin1Literal("latitude")].toDouble();
    return QGeoCoordinate(latitude, longitude);
  }

  QJsonObject
  dump_json_coordinate(const QGeoCoordinate & coordinate)
  {
    QJsonObject json_object;
    json_object[QLatin1Literal("longitude")] = coordinate.longitude();
    json_object[QLatin1Literal("latitude")] = coordinate.latitude();

    return json_object;
  }

}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
