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

#include "network_downloader.h"

#include <QFile>

/**************************************************************************************************/

NetworkDownloadRequest::NetworkDownloadRequest()
  : NetworkRessourceRequest(),
    m_target_path()
{}

NetworkDownloadRequest::NetworkDownloadRequest(const QUrl & url, const QString & target_path)
  : NetworkRessourceRequest(url),
    m_target_path(target_path)
{}

NetworkDownloadRequest::NetworkDownloadRequest(const NetworkDownloadRequest & other)
  : NetworkRessourceRequest(other),
    m_target_path(other.m_target_path)
{}

NetworkDownloadRequest &
NetworkDownloadRequest::operator=(const NetworkDownloadRequest & other)
{
  if (this != &other) {
    NetworkRessourceRequest::operator=(other);
    m_target_path = other.m_target_path;
  }

  return *this;
}

bool
NetworkDownloadRequest::operator==(const NetworkDownloadRequest & rhs) const
{
  return NetworkRessourceRequest::operator==(rhs) && m_target_path == rhs.m_target_path;
}

unsigned int
qHash(const NetworkDownloadRequest & request)
{
  unsigned int result = qHash(request.url().url() + request.target_path()); /// ???
  qInfo() << "NetworkDownloadRequest hash" << result;
  return result;
}

QDebug
operator<<(QDebug debug, const NetworkDownloadRequest & request)
{
  debug << "NetworkDownloadRequest" << request.url().url() << "->" << request.target_path();
  return debug;
}

/**************************************************************************************************/

NetworkDownloader::NetworkDownloader(NetworkFetcher & network_fetcher)
  : QObject(),
    m_network_fetcher(network_fetcher)
{
  connect(&m_network_fetcher, SIGNAL(request_finished(const NetworkRessourceRequest&, const QByteArray&)),
  	  this, SLOT(request_finished(const NetworkRessourceRequest&, const QByteArray&)));

  connect(&m_network_fetcher, SIGNAL(request_error(const NetworkRessourceRequest &, const QString &)),
  	  this, SLOT(request_error(const NetworkRessourceRequest &, const QString &)));

  connect(&m_network_fetcher, &NetworkFetcher::download_progress,
	  this, &NetworkDownloader::download_progress);
}

NetworkDownloader::~NetworkDownloader()
{}

void
NetworkDownloader::add_request(const NetworkDownloadRequest & request)
{
  qInfo() << "NetworkDownloader:add_request" << request;
  m_invmap.insert(request, request);
  m_network_fetcher.add_request(request);
}

void
NetworkDownloader::cancel_request(const NetworkDownloadRequest & request)
{
  if (m_invmap.contains(request)) {
    m_network_fetcher.cancel_request(request); // hash ???
    m_invmap.remove(request);
  }
}

void
NetworkDownloader::request_finished(const NetworkRessourceRequest & request, const QByteArray & payload)
{
  qInfo() << "NetworkDownloader::request_finished" << request;
  if (m_invmap.contains(request)) {
    NetworkDownloadRequest download_request = m_invmap.value(request); // pop ???
    m_invmap.remove(request);
    qInfo() << "request found" << download_request;
    QFile output_file(download_request.target_path());
    if (!output_file.open(QIODevice::WriteOnly | QIODevice::Text))
      qWarning() << "couldn't write to file";
    output_file.write(payload);
    emit finished(request);
  }
}

void
NetworkDownloader::request_error(const NetworkRessourceRequest & request, const QString & error_string)
{
  qInfo() << "NetworkDownloader::request_error" << request << error_string;
  m_invmap.remove(request);
  emit error(request, error_string);
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
