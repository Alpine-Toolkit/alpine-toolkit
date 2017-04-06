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

#ifndef __CAMPTOCAMP_SEARCH_SETTINGS_H__
#define __CAMPTOCAMP_SEARCH_SETTINGS_H__

/**************************************************************************************************/

#include <QHash>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>

/**************************************************************************************************/

class C2cSearchSettings : public QObject
{
  // Q_GADGET
  Q_OBJECT
  Q_PROPERTY(unsigned int limit READ limit WRITE set_limit)
  Q_PROPERTY(bool area READ area WRITE set_area)
  Q_PROPERTY(bool article READ article WRITE set_article)
  Q_PROPERTY(bool book READ book WRITE set_book)
  Q_PROPERTY(bool image READ image WRITE set_image)
  Q_PROPERTY(bool map READ map WRITE set_map)
  Q_PROPERTY(bool outing READ outing WRITE set_outing)
  Q_PROPERTY(bool route READ route WRITE set_route)
  Q_PROPERTY(bool userprofile READ userprofile WRITE set_userprofile)
  Q_PROPERTY(bool waypoint READ waypoint WRITE set_waypoint)
  Q_PROPERTY(bool xreport READ xreport WRITE set_xreport)
  Q_PROPERTY(QString language READ language WRITE set_language) // NOTIFY

public:
  typedef QHash<QString, QVariant> FilterMap;

public:
  C2cSearchSettings();
  C2cSearchSettings(const C2cSearchSettings & other);
  ~C2cSearchSettings();

  C2cSearchSettings & operator=(const C2cSearchSettings & other);

  // operator==

  Q_INVOKABLE void reset();

  unsigned int limit() const { return m_limit; }
  void set_limit(unsigned int limit) { m_limit = limit; }

  bool area() const { return m_area; }
  void set_area(bool area) { m_area = area; }

  bool article() const { return m_article; }
  void set_article(bool article) { m_article = article; }

  bool book() const { return m_book; }
  void set_book(bool book) { m_book = book; }

  bool image() const { return m_image; }
  void set_image(bool image) { m_image = image; }

  bool map() const { return m_map; }
  void set_map(bool map) { m_map = map; }

  bool outing() const { return m_outing; }
  void set_outing(bool outing) { m_outing = outing; }

  bool route() const { return m_route; }
  void set_route(bool route) { m_route = route; }

  bool userprofile() const { return m_userprofile; }
  void set_userprofile(bool userprofile) { m_userprofile = userprofile; }

  bool waypoint() const { return m_waypoint; }
  void set_waypoint(bool waypoint) { m_waypoint = waypoint; }

  bool xreport() const { return m_xreport; }
  void set_xreport(bool xreport) { m_xreport = xreport; }

  QString type_letters() const;

  // Fixme: QStringList ?
  const QString & language() const { return m_language; }
  void set_language(const QString & language) { m_language = language; }

  // bbox=xmin,ymin,xmax,ymax EPSG 3857

  // Fixme: overload ?
  Q_INVOKABLE void add_int_filter(const QString & filter_name, int value);
  Q_INVOKABLE void add_int_pair_filter(const QString & filter_name, int value_min, int value_max);
  Q_INVOKABLE void add_string_filter(const QString & filter_name, const QString & value);
  Q_INVOKABLE void add_string_list_filter(const QString & filter_name, const QStringList & value);

  const FilterMap & filters() const { return m_filters; }

private:
  unsigned int m_limit;
  bool m_area;
  bool m_article;
  bool m_book;
  bool m_image;
  bool m_map;
  bool m_outing;
  bool m_route;
  bool m_userprofile;
  bool m_waypoint;
  bool m_xreport;
  QString m_language;
  FilterMap m_filters;
};

Q_DECLARE_METATYPE(C2cSearchSettings) // Variant

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_SEARCH_SETTINGS_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
