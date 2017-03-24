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
#include <QtDebug>

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

public:
  C2cDocument();
  C2cDocument(const QJsonDocument & json_object);
  C2cDocument(const QJsonObject & json_object);
  C2cDocument(const C2cDocument & other);
  ~C2cDocument();

  C2cDocument & operator=(const C2cDocument & other);

  unsigned int id() const;
  Type type() const;
  QString type_string() const;

  C2cDocument * cast() const;

  const QJsonObject & json_object() const { return m_json_object; }
  QJsonDocument json_document() const { return QJsonDocument(m_json_object); }
  QByteArray to_binary_data() const;
  QByteArray to_json() const;

private:
  QJsonObject m_json_object;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const C2cDocument & document);
#endif

Q_DECLARE_METATYPE(C2cDocument)
// Q_DECLARE_METATYPE(C2cDocument*)

/**************************************************************************************************/

class C2cShortRoute: public C2cDocument
{
  Q_OBJECT
  Q_PROPERTY(QString title_fr READ title_fr CONSTANT) // Fixme

public:
  C2cShortRoute();
  C2cShortRoute(const QJsonDocument & json_document);
  C2cShortRoute(const QJsonObject & json_object);
  C2cShortRoute(const C2cShortRoute & other);
  ~C2cShortRoute();

  QStringList activities() const;
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

public:
  C2cRoute();
  C2cRoute(const QJsonDocument & json_document);
  C2cRoute(const QJsonObject & json_object);
  C2cRoute(const C2cRoute & other);
  ~C2cRoute();
};

Q_DECLARE_METATYPE(C2cRoute)
// Q_DECLARE_METATYPE(C2cRoute*)

/**************************************************************************************************/

class C2cSearchResult : public QObject
{
  Q_OBJECT // Q_GADGET ?
  Q_PROPERTY(QQmlListProperty<C2cShortRoute> routes READ routes_list_property)

public:
  C2cSearchResult();
  C2cSearchResult(const QJsonDocument * json_document);
  C2cSearchResult(const C2cSearchResult & other);
  ~C2cSearchResult();

  C2cSearchResult & operator=(const C2cSearchResult & other);

  const QList<C2cShortRoute> & routes() const { return m_routes; }
  QQmlListProperty<C2cShortRoute> routes_list_property(); // const

  void update(const QJsonDocument * json_document);

private:
  static int routes_list_property_count(QQmlListProperty<C2cShortRoute> * list);
  static C2cShortRoute * routes_list_property_at(QQmlListProperty<C2cShortRoute> * list, int index);

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
