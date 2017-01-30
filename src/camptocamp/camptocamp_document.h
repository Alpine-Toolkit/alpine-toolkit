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

/**************************************************************************************************/

class C2cShortRoute
{
public:
  C2cShortRoute();
  C2cShortRoute(const QJsonObject json_object);
  C2cShortRoute(const C2cShortRoute & other);
  ~C2cShortRoute();

  C2cShortRoute & operator=(const C2cShortRoute & other);

  unsigned int id() const;
  QStringList activities() const;
  QString title(const QString & language) const;

private:
  QJsonObject m_json_object;
};

/**************************************************************************************************/

class C2cSearchResult
{
public:
  C2cSearchResult(const QJsonDocument * json_document);
  ~C2cSearchResult();

  const QList<C2cShortRoute> & routes() const { return m_routes; }

private:
  QList<C2cShortRoute> m_routes;
};

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_DOCUMENT_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
