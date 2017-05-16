/***************************************************************************************************
 **
 ** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
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
 ** $ALPINE_TOOLKIT_END_LICENSE$
 **
 ***************************************************************************************************/

/**************************************************************************************************/

#include "network_ressource_request.h"

#include <QtDebug>

/**************************************************************************************************/

NetworkRessourceRequest::NetworkRessourceRequest()
  : QObject(),
    m_url()
{}

NetworkRessourceRequest::NetworkRessourceRequest(const QUrl & url)
  : QObject(),
    m_url(url)
{}

NetworkRessourceRequest::NetworkRessourceRequest(const NetworkRessourceRequest & other)
  : QObject(),
    m_url(other.m_url)
{}

NetworkRessourceRequest::~NetworkRessourceRequest()
{}

NetworkRessourceRequest &
NetworkRessourceRequest::operator=(const NetworkRessourceRequest & other)
{
  if (this != &other) {
    m_url = other.m_url;
  }

  return *this;
}

bool
NetworkRessourceRequest::operator==(const NetworkRessourceRequest & rhs) const
{
  return m_url == rhs.m_url;
}

unsigned int
qHash(const NetworkRessourceRequest & request)
{
  unsigned int result = qHash(request.url());
  qInfo() << "NetworkRessourceRequest hash" << result;
  return result;
}

QDebug
operator<<(QDebug debug, const NetworkRessourceRequest & request)
{
  debug << "NetworkRessourceRequest" << request.url().url();
  return debug;
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
