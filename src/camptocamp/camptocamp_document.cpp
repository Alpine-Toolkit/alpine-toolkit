/***************************************************************************************************
 **
 ** $QTCARTO_BEGIN_LICENSE:GPL3$
 **
 ** Copyright (C) 2016 Fabrice Salvaire
 ** Contact: http://www.fabrice-salvaire.fr
 **
 ** This file is part of the QtCarto library.
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
 ** $QTCARTO_END_LICENSE$
 **
 ***************************************************************************************************/

/**************************************************************************************************/

#include "camptocamp/camptocamp_document.h"

#include "camptocamp/camptocamp_constant.h"
using namespace c2c;

#include <QJsonArray>
#include <QJsonObject>

/**************************************************************************************************/

C2cShortRoute::C2cShortRoute()
  : m_json_object()
{}

C2cShortRoute::C2cShortRoute(const QJsonObject json_object)
  : m_json_object(json_object)
{}

C2cShortRoute::C2cShortRoute(const C2cShortRoute & other)
    : m_json_object(other.m_json_object)
{}

C2cShortRoute::~C2cShortRoute()
{}

C2cShortRoute &
C2cShortRoute::operator=(const C2cShortRoute & other)
{
  if (this != &other) {
    m_json_object = other.m_json_object;
  }

  return *this;
}

QString
C2cShortRoute::title(const QString & language) const
{
  QJsonArray locales = m_json_object[LOCALES].toArray();
  for (const auto & ref : locales) {
      QJsonObject locale = ref.toObject();
      if (locale[LANG].toString() == language)
        return locale[TITLE].toString();
  }

  return QString();
}

/**************************************************************************************************/

C2cSearchResult::C2cSearchResult(const QJsonDocument * json_document)
{
  QJsonObject root = json_document->object();
  // for (const auto & key : root.keys())
  //   qInfo() << key;

  QJsonObject root_for_routes = root[ROUTES].toObject();
  // qInfo() << "Number of routes:" << root_for_routes["total"].toInt();
  QJsonArray routes = root_for_routes[DOCUMENTS].toArray();
  for (const auto & ref : routes) {
    QJsonObject route = ref.toObject();
    m_routes << C2cShortRoute(route);
  }
}

C2cSearchResult::~C2cSearchResult()
{}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
