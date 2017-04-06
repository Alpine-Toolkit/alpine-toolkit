// -*- mode: c++ -*-

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

#ifndef __NETWORK_RESSOURCE_REQUEST_H__
#define __NETWORK_RESSOURCE_REQUEST_H__

/**************************************************************************************************/

#include <QHash>
#include <QUrl>
#include <QObject>

/**************************************************************************************************/

// Fixme: similar to QNetworkRequest

/* The NetworkRessourceRequest class defines a network ressource request.
 *
 */
class NetworkRessourceRequest : public QObject
{
  Q_OBJECT

public:
  NetworkRessourceRequest();
  NetworkRessourceRequest(const QUrl & url);
  NetworkRessourceRequest(const NetworkRessourceRequest & other);
  ~NetworkRessourceRequest();

  NetworkRessourceRequest & operator=(const NetworkRessourceRequest & other);

  inline QUrl url() const { return m_url; }

  bool operator==(const NetworkRessourceRequest & rhs) const;

private:
  QUrl m_url;
};

unsigned int qHash(const NetworkRessourceRequest & request);

QDebug operator<<(QDebug, const NetworkRessourceRequest & request);

/**************************************************************************************************/

#endif /* __NETWORK_RESSOURCE_REQUEST_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
