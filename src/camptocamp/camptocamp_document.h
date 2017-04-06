// -*- mode: c++ -*-

/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
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

#ifndef __CAMPTOCAMP_DOCUMENT_H__
#define __CAMPTOCAMP_DOCUMENT_H__

/**************************************************************************************************/

#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QQmlListProperty>
#include <QString>
#include <QtDebug>

/**************************************************************************************************/

QString markdown_to_html(const QString & markdown);

/**************************************************************************************************/

class C2cDocument : public QObject
{
public:
  enum class Type {
    Area,
    Article,
    Book,
    Image,
    Map,
    Outing,
    Route,
    UserProfile,
    XReport,
    Waypoint
  };
  Q_ENUMS(Type)

private:
  Q_OBJECT // Q_GADGET ?

  Q_PROPERTY(unsigned int id READ id CONSTANT)
  Q_PROPERTY(Type type READ type CONSTANT)
  // Q_PROPERTY(QString type READ type_string CONSTANT)
  Q_PROPERTY(QStringList available_langs READ available_langs CONSTANT)
  Q_PROPERTY(bool is_protected READ is_protected CONSTANT)
  Q_PROPERTY(QString quality READ quality CONSTANT) // Fixme: no all
  Q_PROPERTY(unsigned int version READ version CONSTANT)

public:
  C2cDocument();
  C2cDocument(const QJsonDocument & json_object);
  C2cDocument(const QJsonObject & json_object);
  C2cDocument(const C2cDocument & other);
  ~C2cDocument();

  C2cDocument & operator=(const C2cDocument & other);

  // JSON Interface
  Q_INVOKABLE QStringList attributes() const;
  Q_INVOKABLE bool has_attribute(const QString attribute_name) const;
  Q_INVOKABLE bool get_bool(const QString attribute_name, bool default_value = false) const;
  Q_INVOKABLE int get_int(const QString attribute_name, int default_value = -1) const;
  Q_INVOKABLE double get_double(const QString attribute_name, double default_value = -1.) const;
  Q_INVOKABLE QString get_string(const QString attribute_name) const;
  Q_INVOKABLE QStringList get_string_list(const QString attribute_name) const;

  const QJsonObject & json_object() const { return m_json_object; }
  QJsonDocument json_document() const { return QJsonDocument(m_json_object); }
  QByteArray to_binary_data() const;
  QByteArray to_json() const;
  Q_INVOKABLE QString to_json_string() const;

  C2cDocument * cast() const;

  // C2c attributes
  unsigned int id() const;
  Type type() const;
  QString type_string() const;
  QStringList available_langs() const; // list of code languages e.g. ['it', 'es', 'fr']
  bool is_protected() const;
  QString quality() const;
  unsigned int version() const;

private:
  QJsonObject m_json_object;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const C2cDocument & document);
#endif

Q_DECLARE_METATYPE(C2cDocument)
// Q_DECLARE_METATYPE(C2cDocument*)

/**************************************************************************************************/

// Area
// area_type : string e.g. 'country', 'range', 'admin_limits'
// locales : [{TITLE_LOCAL}]

// Article
//     activities
//     article_type : 'collab'
//     associations :
//         articles : []
//         books : []
//         images : []
//         outings : []
//         routes : []
//         users : []
//         waypoints : []
//         xreports : []
//     author : {AUTHOR}
//     categories : ['site_info']
//     locales : [{ARTICLE_LOCALE}]

// Map
//     code : '3145ET'
//     editor : 'IGN'
//     locales : [{TITLE_LOCALE}]

// Outing
//     activities : ['rock_climbing']
//     areas : [{AREA}]
//     author : {Author}
//     date_end : string date e.g. '2016-12-31'
//     date_start : string date e.g. '2016-12-31'
//     elevation_max : null
//     geometry : {POINT_GEOMETRY}
//     height_diff_up : null
//     locales : [{OUTING_LOCALE}]

// User Profile
//     activities : 
//     areas : [{AREA}]
//     associations : {images : []}
//     categories : ['amateur']
//     forum_username : string e.g. 'John_Doe'
//     geometry : {POINT_GEOMETRY_WITH_DETAIL}
//     locales : [{USER_LOCALE}]
//     name : string e.g. 'John Doe'

// X Report
//     activities : ['skitouring']
//     areas : [{AREA}]
//     associations :
//         routes : []
//         waypoints : []
//         users : [{USER}]
//         articles : []
//         outings : [{OUTING}]
//         images : [{IMAGE}]
//     author : {AUTHOR}
//     available_langs : ['fr']
//     avalanche_level : 'level_2'
//     avalanche_slope : null
//     date : '2016-03-23'
//     elevation : int
//     event_type : ['avalanche']
//     geometry : {POINT_GEOMETRY_WITH_DETAIL}
//     locales : [{XREPORT_LOCALE}]
//     nb_impacted : int
//     nb_participants : int
//     rescue : null
//     severity : 'severity_no'

// Waypoint
//     areas : [{AREA}]
//     waypoint_type : e.g. 'climbing_outdoor', 'summit'
//     geometry : {POINT_GEOMETRY}
//     locales : [{WAYPOINT_LOCALE}]
//     elevation : int

/**************************************************************************************************/

class C2cImage: public C2cDocument
{
  Q_OBJECT
  Q_PROPERTY(QString title_fr READ title_fr CONSTANT) // Fixme
  Q_PROPERTY(QString author READ author CONSTANT)
  Q_PROPERTY(QString filename READ filename CONSTANT)

public:
  C2cImage();
  C2cImage(const QJsonDocument & json_document);
  C2cImage(const QJsonObject & json_object);
  C2cImage(const C2cImage & other);
  ~C2cImage();

  // areas() const; // [{AREA}]
  QString author() const;
  QString filename() const;
  // geometry
  // locales

  Q_INVOKABLE QString title(const QString & language) const;

  QString title_fr() const { return title("fr"); };
};

Q_DECLARE_METATYPE(C2cImage)
// Q_DECLARE_METATYPE(C2cImage*)

// #ifndef QT_NO_DEBUG_STREAM
// QDebug operator<<(QDebug debug, const C2cImage & document);
// #endif

/**************************************************************************************************/

class C2cShortRoute: public C2cDocument
{
  Q_OBJECT
  Q_PROPERTY(QString title_fr READ title_fr CONSTANT) // Fixme
  Q_PROPERTY(QStringList activities READ activities CONSTANT) // Fixme
  Q_PROPERTY(QString aid_rating READ aid_rating CONSTANT)
  // Q_PROPERTY(areas READ CONSTANT)
  Q_PROPERTY(unsigned int elevation_max READ elevation_max CONSTANT)
  Q_PROPERTY(QString engagement_rating READ engagement_rating CONSTANT)
  Q_PROPERTY(QString equipment_rating READ equipment_rating CONSTANT)
  Q_PROPERTY(QString exposition_rock_rating READ exposition_rock_rating CONSTANT)
  // Q_PROPERTY(geometry READ CONSTANT)
  Q_PROPERTY(QString global_rating READ global_rating CONSTANT)
  Q_PROPERTY(unsigned int height_diff_difficulties READ height_diff_difficulties CONSTANT)
  Q_PROPERTY(unsigned int height_diff_up READ height_diff_up CONSTANT)
  // Q_PROPERTY(locales)
  Q_PROPERTY(QStringList orientations READ orientations CONSTANT)
  Q_PROPERTY(QString risk_rating READ risk_rating CONSTANT)
  Q_PROPERTY(QString rock_free_rating READ rock_free_rating CONSTANT)
  Q_PROPERTY(QString rock_required_rating READ rock_required_rating CONSTANT)

public:
  C2cShortRoute();
  C2cShortRoute(const QJsonDocument & json_document);
  C2cShortRoute(const QJsonObject & json_object);
  C2cShortRoute(const C2cShortRoute & other);
  ~C2cShortRoute();

  QStringList activities() const;
  QString aid_rating() const;
  // areas() const; // [{AREA}]
  unsigned int elevation_max() const;
  QString engagement_rating() const; // e.g. 'I'
  QString equipment_rating() const; // e.g. 'P1'
  QString exposition_rock_rating() const;
  // geometry() const; // {POINT_GEOMETRY}
  QString global_rating() const; // e.g. 'AD+'
  unsigned int height_diff_difficulties() const;
  unsigned int height_diff_up() const;
  // locales() const; // [{ROUTE_LOCALE_SHORT}]
  QStringList orientations() const; // e.g. ['SW']
  QString risk_rating() const;
  QString rock_free_rating() const; // e.g. '5a'
  QString rock_required_rating() const; // e.g. '4c'

  Q_INVOKABLE QString title(const QString & language) const;
  Q_INVOKABLE QString description(const QString & language) const;

  QString title_fr() const { return title("fr"); };
};

Q_DECLARE_METATYPE(C2cShortRoute)
// Q_DECLARE_METATYPE(C2cShortRoute*)

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const C2cShortRoute & document);
#endif

/**************************************************************************************************/

class C2cRoute : public C2cShortRoute
{
  Q_OBJECT
  Q_PROPERTY(QString climbing_outdoor_type READ climbing_outdoor_type CONSTANT)
  Q_PROPERTY(QStringList configuration READ configuration CONSTANT)
  Q_PROPERTY(unsigned int difficulties_height READ difficulties_height CONSTANT)
  // Q_PROPERTY(durations READ durations CONSTANT)
  Q_PROPERTY(unsigned int elevation_min READ elevation_min CONSTANT)
  Q_PROPERTY(QString glacier_gear READ glacier_gear CONSTANT)
  Q_PROPERTY(unsigned int height_diff_access READ height_diff_access CONSTANT)
  Q_PROPERTY(unsigned int height_diff_down READ height_diff_down CONSTANT)
  // Q_PROPERTY(lift_access READ lift_access CONSTANT)
  Q_PROPERTY(unsigned int main_waypoint_id READ main_waypoint_id CONSTANT)
  // Q_PROPERTY(maps READ maps CONSTANT)
  Q_PROPERTY(QStringList rock_types READ rock_types CONSTANT)
  Q_PROPERTY(QStringList route_types READ route_types CONSTANT)
  Q_PROPERTY(QQmlListProperty<C2cImage> images READ image_list_property)

public:
  C2cRoute();
  C2cRoute(const QJsonDocument & json_document);
  C2cRoute(const QJsonObject & json_object);
  C2cRoute(const C2cRoute & other);
  ~C2cRoute();

  QString climbing_outdoor_type() const; // 'multi'
  QStringList configuration() const; // ['pillar']
  unsigned int difficulties_height() const;
  // durations() const; // ['1'] why ???
  unsigned int elevation_min() const;
  QString glacier_gear() const; // e.g. 'no'
  unsigned int height_diff_access() const;
  unsigned int height_diff_down() const;
  // lift_access() const;
  unsigned int main_waypoint_id() const;
  // maps() const; // [{MAP}]
  QStringList rock_types() const; // ['calcaire']
  QStringList route_types() const; // ['traverse']

  QQmlListProperty<C2cImage> image_list_property(); // const

private:
  void init();
  static int image_list_property_count(QQmlListProperty<C2cImage> * list);
  static C2cImage * image_list_property_at(QQmlListProperty<C2cImage> * list, int index);

private:
  QList<C2cImage *> m_images;
};

Q_DECLARE_METATYPE(C2cRoute)
// Q_DECLARE_METATYPE(C2cRoute*)

/**************************************************************************************************/

class C2cSearchResult : public QObject
{
  Q_OBJECT // Q_GADGET ?
  Q_PROPERTY(QQmlListProperty<C2cShortRoute> routes READ route_list_property)

public:
  C2cSearchResult();
  C2cSearchResult(const QJsonDocument * json_document);
  C2cSearchResult(const C2cSearchResult & other);
  ~C2cSearchResult();

  C2cSearchResult & operator=(const C2cSearchResult & other);

  const QList<C2cShortRoute> & routes() const { return m_routes; }
  QQmlListProperty<C2cShortRoute> route_list_property(); // const

  void update(const QJsonDocument * json_document);

private:
  static int route_list_property_count(QQmlListProperty<C2cShortRoute> * list);
  static C2cShortRoute * route_list_property_at(QQmlListProperty<C2cShortRoute> * list, int index);

private:
  QList<C2cShortRoute> m_routes;
};

Q_DECLARE_METATYPE(C2cSearchResult)
// Q_DECLARE_METATYPE(C2cSearchResult*)

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_DOCUMENT_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
