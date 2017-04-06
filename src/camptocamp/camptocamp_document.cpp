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

#include "cmark/cmark.h"

/**************************************************************************************************/

QString
markdown_to_html(const QString & markdown)
{
  QString markdown_fixed(markdown);
  markdown_fixed.replace(QStringLiteral("\r\n"), QStringLiteral("\n"));
  markdown_fixed.replace(QStringLiteral("\n"), QStringLiteral("   \n")); // ???
  QByteArray byte_array = markdown_fixed.toUtf8();
  char * html_c = cmark_markdown_to_html(byte_array.constData(),
                                         byte_array.size(),
                                         CMARK_OPT_DEFAULT);
  QString html(html_c);
  free(html_c);
  // qInfo() << "markdown_to_html" << '\n' << markdown_fixed << '\n' << html;
  return html;
}

/**************************************************************************************************/

C2cDocument::C2cDocument()
  : QObject(),
    m_json_object()
{}

C2cDocument::C2cDocument(const QJsonDocument & json_document)
  : QObject(),
    m_json_object(json_document.object())
{}

C2cDocument::C2cDocument(const QJsonObject & json_object)
  : QObject(),
    m_json_object(json_object)
{}

C2cDocument::C2cDocument(const C2cDocument & other)
  : QObject(),
    m_json_object(other.m_json_object)
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

QString
C2cDocument::to_json_string() const
{
  return QJsonDocument(m_json_object).toJson(QJsonDocument::Indented);
}

QStringList
C2cDocument::attributes() const
{
  return m_json_object.keys();
}

bool
C2cDocument::has_attribute(const QString attribute_name) const
{
  return m_json_object.contains(attribute_name);
}

bool
C2cDocument::get_bool(const QString attribute_name, bool default_value) const
{
  QJsonValue json_value = m_json_object[attribute_name];
  if (json_value.isUndefined())
    return default_value;
  else
    return json_value.toBool();
}
int
C2cDocument::get_int(const QString attribute_name, int default_value) const
{
  QJsonValue json_value = m_json_object[attribute_name];
  if (json_value.isUndefined())
    return default_value;
  else
    return json_value.toInt();
}

double
C2cDocument::get_double(const QString attribute_name, double default_value) const
{
  QJsonValue json_value = m_json_object[attribute_name];
  if (json_value.isUndefined())
    return default_value;
  else
    return json_value.toDouble();
}
QString
C2cDocument::get_string(const QString attribute_name) const
{
  QJsonValue json_value = m_json_object[attribute_name];
  if (json_value.isUndefined())
    return QString();
  else
    return json_value.toString();
}

QStringList
C2cDocument::get_string_list(const QString attribute_name) const
{
  QStringList string_list;
  QJsonValue json_value = m_json_object[attribute_name];
  if (!json_value.isUndefined()) {
    const QJsonArray array = m_json_object[attribute_name].toArray();
    for (const auto & ref : array)
      string_list << ref.toString();
  }
  return string_list;
}

unsigned int
C2cDocument::id() const
{
  return m_json_object[DOCUMENT_ID].toInt();
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
    return new C2cRoute(m_json_object); // Fixme: delete
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

QStringList C2cDocument::available_langs() const
{
  return get_string_list(AVAILABLE_LANGS);
}

bool
C2cDocument::is_protected() const
{
  return m_json_object[PROTECTED].toBool();
}

QString
C2cDocument::quality() const
{
  return m_json_object[QUALITY].toString();
}

unsigned int
C2cDocument::version() const
{
  return m_json_object[VERSION].toInt();
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

C2cImage::C2cImage()
  : C2cDocument()
{}

C2cImage::C2cImage(const QJsonDocument & json_document)
  : C2cDocument(json_document)
{}

C2cImage::C2cImage(const QJsonObject & json_object)
  : C2cDocument(json_object)
{}

C2cImage::C2cImage(const C2cImage & other)
  : C2cDocument(other)
{}

C2cImage::~C2cImage()
{}

QString
C2cImage::author() const
{
  return get_string(AUTHOR);
}

QString
C2cImage::filename() const
{
  return get_string(FILENAME);
}

QString
C2cImage::title(const QString & language) const
{
  // Fixme: duplicate
  const QJsonArray locales = json_object()[LOCALES].toArray();
  for (const auto & ref : locales) {
      const QJsonObject locale = ref.toObject();
      if (locale[LANG].toString() == language)
        return locale[TITLE].toString();
  }

  return QString();
}

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
  return get_string_list(ACTIVITIES);
}

QString
C2cShortRoute::aid_rating() const
{
  return get_string(AID_RATING);
}

// C2cShortRoute::areas() const

unsigned int
C2cShortRoute::elevation_max() const
{
  return get_int(ELEVATION_MAX);
}

QString
C2cShortRoute::engagement_rating() const
{
  return get_string(ENGAGEMENT_RATING);
}

QString
C2cShortRoute::equipment_rating() const
{
  return get_string(EQUIPMENT_RATING);
}

QString
C2cShortRoute::exposition_rock_rating() const
{
  return get_string(EXPOSITION_ROCK_RATING);
}

// C2cShortRoute::geometry() const

QString
C2cShortRoute::global_rating() const
{
  return get_string(GLOBAL_RATING);
}

unsigned int
C2cShortRoute::height_diff_difficulties() const
{
  return get_int(HEIGHT_DIFF_DIFFICULTIES);
}

unsigned int
C2cShortRoute::height_diff_up() const
{
  return get_int(HEIGHT_DIFF_UP);
}

// C2cShortRoute::locales() const

QStringList
C2cShortRoute::orientations() const
{
  return get_string_list(ORIENTATIONS);
}

QString
C2cShortRoute::risk_rating() const
{
  return get_string(RISK_RATING);
}

QString
C2cShortRoute::rock_free_rating() const
{
  return get_string(ROCK_FREE_RATING);
}

QString
C2cShortRoute::rock_required_rating() const
{
  return get_string(ROCK_REQUIRED_RATING);
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
        return markdown_to_html(locale[DESCRIPTION].toString());
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
  : C2cShortRoute(),
    m_images()
{}

C2cRoute::C2cRoute(const QJsonDocument & json_document)
  : C2cShortRoute(json_document),
    m_images()
{
  init();
}

C2cRoute::C2cRoute(const QJsonObject & json_object)
  : C2cShortRoute(json_object),
    m_images()
{
  init();
}

C2cRoute::C2cRoute(const C2cRoute & other)
  : C2cShortRoute(other),
    m_images(other.m_images)
{}

C2cRoute::~C2cRoute()
{}

void
C2cRoute::init()
{
  QJsonObject associations = json_object()[ASSOCIATIONS].toObject();
  QJsonArray array = associations[IMAGES].toArray();
  for (const auto & json_value : array) {
    QJsonObject object = json_value.toObject();
    m_images << new C2cImage(object); // Fixme: delete
  }
}

QString
C2cRoute::climbing_outdoor_type() const
{
  return get_string(CLIMBING_OUTDOOR_TYPE);
}

QStringList
C2cRoute::configuration() const
{
  return get_string_list(CONFIGURATION);
}

unsigned int
C2cRoute::difficulties_height() const
{
  return get_int(DIFFICULTIES_HEIGHT);
}

// durations() const

unsigned int
C2cRoute::elevation_min() const
{
  return get_int(ELEVATION_MIN);
}

QString
C2cRoute::glacier_gear() const
{
  return get_string(GLACIER_GEAR);
}

unsigned int
C2cRoute::height_diff_access() const
{
  return get_int(HEIGHT_DIFF_ACCESS);
}

unsigned int
C2cRoute::height_diff_down() const
{
  return get_int(HEIGHT_DIFF_DOWN);
}

// C2cRoute::lift_access() const

unsigned int
C2cRoute::main_waypoint_id() const
{
  return get_int(MAIN_WAYPOINT_ID);
}

// maps() const

QStringList
C2cRoute::rock_types() const
{
  return get_string_list(ROCK_TYPES);
}

QStringList
C2cRoute::route_types() const
{
  return get_string_list(ROUTE_TYPES);
}

QQmlListProperty<C2cImage>
C2cRoute::image_list_property()
{
  return QQmlListProperty<C2cImage>(this, nullptr,
                                    &C2cRoute::image_list_property_count,
                                    &C2cRoute::image_list_property_at);
}

int
C2cRoute::image_list_property_count(QQmlListProperty<C2cImage> * list)
{
  C2cRoute * route = qobject_cast<C2cRoute *>(list->object); // Fixme: func
  return route->m_images.size();
}

C2cImage *
C2cRoute::image_list_property_at(QQmlListProperty<C2cImage> * list, int index)
{
  C2cRoute * route = qobject_cast<C2cRoute *>(list->object);
  return route->m_images[index];
}

/**************************************************************************************************/

C2cSearchResult::C2cSearchResult()
  : QObject(),
    m_routes()
{}

C2cSearchResult::C2cSearchResult(const QJsonDocument * json_document)
  : QObject(),
    m_routes()
{
  update(json_document);
}

C2cSearchResult::C2cSearchResult(const C2cSearchResult & other)
  : QObject(),
    m_routes(other.m_routes)
{}

C2cSearchResult &
C2cSearchResult::operator=(const C2cSearchResult & other)
{
  qInfo() << "C2cSearchResult::operator=";

  if (this != &other) {
    m_routes = other.m_routes;
  }

  return *this;
}

C2cSearchResult::~C2cSearchResult()
{}

void
C2cSearchResult::update(const QJsonDocument * json_document)
{
  m_routes.clear();

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

  qInfo() << "C2cShortRoute::update " << m_routes.size();
}

QQmlListProperty<C2cShortRoute>
C2cSearchResult::route_list_property()
{
  return QQmlListProperty<C2cShortRoute>(this, nullptr,
                                         &C2cSearchResult::route_list_property_count,
                                         &C2cSearchResult::route_list_property_at);
}

int
C2cSearchResult::route_list_property_count(QQmlListProperty<C2cShortRoute> * list)
{
  C2cSearchResult * search_result = qobject_cast<C2cSearchResult *>(list->object);
  return search_result->m_routes.size();
}

C2cShortRoute *
C2cSearchResult::route_list_property_at(QQmlListProperty<C2cShortRoute> * list, int index)
{
  C2cSearchResult * search_result = qobject_cast<C2cSearchResult *>(list->object);
  C2cShortRoute & route = search_result->m_routes[index];
  return &route;
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
