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

C2cDocument::C2cDocument()
  : QObject(),
    m_json_object()
{}

C2cDocument::C2cDocument(const QJsonDocument & json_document)
  : m_json_object(json_document.object())
{}

C2cDocument::C2cDocument(const QJsonObject & json_object)
  : m_json_object(json_object)
{}

C2cDocument::C2cDocument(const C2cDocument & other)
  : m_json_object(other.m_json_object)
{}

C2cDocument::~C2cDocument()
{}

C2cDocument &
C2cDocument::operator=(const C2cDocument & other)
{
  if (this != &other) {
    m_json_object = other.m_json_object;
  }

  return *this;
}

QByteArray
C2cDocument::to_binary_data() const
{
  return QJsonDocument(m_json_object).toBinaryData();
}

QByteArray
C2cDocument::to_json() const
{
  return QJsonDocument(m_json_object).toJson(QJsonDocument::Compact);
}

C2cDocument::Type
C2cDocument::type() const
{
  const char type = m_json_object[TYPE].toString()[0].toLatin1();

  switch (type) {
  case 'a':
    return Type::Area;
  case 'c':
    return Type::Article;
  case 'b':
    return Type::Book;
  case 'i':
    return Type::Image;
  case 'm':
    return Type::Map;
  case 'o':
    return Type::Outing;
  case 'r':
    return Type::Route;
  case 'u':
    return Type::UserProfile;
  case 'x':
    return Type::XReport;
  case 'w':
    return Type::Waypoint;
    // Fixme:
    // default:
  }
}

QString
C2cDocument::type_string() const
{
  switch (type()) {
  case Type::Area:
    return "Area";
  case Type::Article:
    return "Article";
  case Type::Book:
    return "Book";
  case Type::Image:
    return "Image";
  case Type::Map:
    return "Map";
  case Type::Outing:
    return "Outing";
  case Type::Route:
    return "Route";
  case Type::UserProfile:
    return "UserProfile";
  case Type::XReport:
    return "XReport";
  case Type::Waypoint:
    return "Waypoint";
    // Fixme:
    // default:
  }
}

unsigned int
C2cDocument::id() const
{
  return m_json_object[DOCUMENT_ID].toInt();
}

C2cDocument *
C2cDocument::cast() const
{
  switch (type()) {
  case Type::Area:
    return nullptr;
  case Type::Article:
    return nullptr;
  case Type::Book:
    return nullptr;
  case Type::Image:
    return nullptr;
  case Type::Map:
    return nullptr;
  case Type::Outing:
    return nullptr;
  case Type::Route:
    return new C2cRoute(m_json_object);
  case Type::UserProfile:
    return nullptr;
  case Type::XReport:
    return nullptr;
  case Type::Waypoint:
    return nullptr;
    // Fixme:
    // default:
  }
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const C2cDocument & document)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace().noquote() << QLatin1Literal("C2cDocument<");
  debug.noquote() << document.type_string();
  debug << ">(";
  debug << document.id();
  debug << ")";

  return debug;
}
#endif

/**************************************************************************************************/

C2cShortRoute::C2cShortRoute()
  : C2cDocument()
{}

C2cShortRoute::C2cShortRoute(const QJsonDocument & json_document)
  : C2cDocument(json_document)
{}

C2cShortRoute::C2cShortRoute(const QJsonObject & json_object)
  : C2cDocument(json_object)
{}

C2cShortRoute::C2cShortRoute(const C2cShortRoute & other)
  : C2cDocument(other)
{}

C2cShortRoute::~C2cShortRoute()
{}

QStringList
C2cShortRoute::activities() const
{
  QStringList activities;
  const QJsonArray array = json_object()[ACTIVITIES].toArray();
  for (const auto & ref : array) {
    activities << ref.toString();
  }

  return activities;
}

QString
C2cShortRoute::title(const QString & language) const
{
  const QJsonArray locales = json_object()[LOCALES].toArray();
  for (const auto & ref : locales) {
      const QJsonObject locale = ref.toObject();
      if (locale[LANG].toString() == language)
        return locale[TITLE].toString();
  }

  return QString();
}

QString
C2cShortRoute::description(const QString & language) const
{
  const QJsonArray locales = json_object()[LOCALES].toArray();
  for (const auto & ref : locales) {
      const QJsonObject locale = ref.toObject();
      if (locale[LANG].toString() == language)
        return locale[DESCRIPTION].toString();
  }

  return QString();
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const C2cShortRoute & document)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace().noquote() << QLatin1Literal("C2cShortRoute");
  debug << "(";
  debug << document.id();
  debug << ",";
  debug << document.title_fr();
  debug << ")";

  return debug;
}
#endif

/**************************************************************************************************/

C2cRoute::C2cRoute()
  : C2cShortRoute()
{}

C2cRoute::C2cRoute(const QJsonDocument & json_document)
  : C2cShortRoute(json_document)
{}

C2cRoute::C2cRoute(const QJsonObject & json_object)
  : C2cShortRoute(json_object)
{}

C2cRoute::C2cRoute(const C2cRoute & other)
  : C2cShortRoute(other)
{}

C2cRoute::~C2cRoute()
{}

/**************************************************************************************************/

C2cSearchResult::C2cSearchResult()
  : QObject(),
    m_routes()
{
  qInfo() << "C2cSearchResult::C2cSearchResult()";
}

C2cSearchResult::C2cSearchResult(const QJsonDocument * json_document)
  : QObject(),
    m_routes()
{
  qInfo() << "C2cSearchResult::C2cSearchResult(json_document)";
  update(json_document);
}

C2cSearchResult::C2cSearchResult(const C2cSearchResult & other)
  : QObject(),
    m_routes(other.m_routes)
{
  qInfo() << "C2cSearchResult::C2cSearchResult(&)";
}

C2cSearchResult &
C2cSearchResult::operator=(const C2cSearchResult & other)
{
  qInfo() << "C2cSearchResult::operator=";

  if (this != &other) {
    m_routes = other.m_routes;
  }

  emit updated();

  return *this;
}

C2cSearchResult::~C2cSearchResult()
{
  qInfo() << "C2cSearchResult::~";
}

void
C2cSearchResult::update(const QJsonDocument * json_document)
{
  qInfo() << "C2cSearchResult::update";

  m_routes.clear();
  m_routes_obj.clear();

  QJsonObject root = json_document->object();
  // for (const auto & key : root.keys())
  //   qInfo() << key;

  QJsonObject root_for_routes = root[ROUTES].toObject();
  // qInfo() << "Number of routes:" << root_for_routes["total"].toInt();
  QJsonArray routes = root_for_routes[DOCUMENTS].toArray();
  for (const auto & ref : routes) {
    QJsonObject json_obj = ref.toObject();
    m_routes << C2cShortRoute(json_obj);
  }

  for (auto & route : m_routes)
    m_routes_obj << &route;

  emit updated();
}

QQmlListProperty<C2cShortRoute>
C2cSearchResult::routes_list_property()
{
  return QQmlListProperty<C2cShortRoute>(this, nullptr,
                                         &C2cSearchResult::routes_list_property_count,
                                         &C2cSearchResult::routes_list_property_at);
}

int
C2cSearchResult::routes_list_property_count(QQmlListProperty<C2cShortRoute> * list)
{
  C2cSearchResult * search_result = qobject_cast<C2cSearchResult *>(list->object);
  return search_result->m_routes.size();
}

C2cShortRoute *
C2cSearchResult::routes_list_property_at(QQmlListProperty<C2cShortRoute> * list, int index)
{
  C2cSearchResult * search_result = qobject_cast<C2cSearchResult *>(list->object);
  return &search_result->m_routes[index];
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
