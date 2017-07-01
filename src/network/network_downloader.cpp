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

#include "network_downloader.h"

#include <QFile>

/**************************************************************************************************/

NetworkDownloadRequest::NetworkDownloadRequest()
  : QcGetNetworkRequest(),
    m_target_path()
{}

NetworkDownloadRequest::NetworkDownloadRequest(const QUrl & url, const QString & target_path)
  : QcGetNetworkRequest(url),
    m_target_path(target_path)
{}

NetworkDownloadRequest::NetworkDownloadRequest(const NetworkDownloadRequest & other)
  : QcGetNetworkRequest(other),
    m_target_path(other.m_target_path)
{}

NetworkDownloadRequest &
NetworkDownloadRequest::operator=(const NetworkDownloadRequest & other)
{
  if (this != &other) {
    QcGetNetworkRequest::operator=(other);
    m_target_path = other.m_target_path;
  }

  return *this;
}

bool
NetworkDownloadRequest::operator==(const NetworkDownloadRequest & rhs) const
{
  return QcGetNetworkRequest::operator==(rhs) && m_target_path == rhs.m_target_path;
}

QDebug
operator<<(QDebug debug, const NetworkDownloadRequest & request)
{
  debug << "NetworkDownloadRequest" << request.url().url() << "->" << request.target_path();
  return debug;
}

/**************************************************************************************************/

NetworkDownloader::NetworkDownloader(QcNetworkRequestManager & network_fetcher)
  : QObject(),
    m_network_fetcher(network_fetcher)
{
  connect(&m_network_fetcher, &QcNetworkRequestManager::request_finished,
  	  this, &NetworkDownloader::on_request_finished);
  connect(&m_network_fetcher, &QcNetworkRequestManager::request_error,
  	  this, &NetworkDownloader::on_request_error);

  // connect(&m_network_fetcher, &QcNetworkRequestManager::download_progress,
  //         this, &NetworkDownloader::download_progress);
}

NetworkDownloader::~NetworkDownloader()
{}

void
NetworkDownloader::add_request(const QcNetworkRequestPtr & request)
{
  qInfo() << "NetworkDownloader:add_request" << request;
  m_invmap.insert(request, request);
  m_network_fetcher.add_request(request);
}

void
NetworkDownloader::cancel_request(const QcNetworkRequestPtr & request)
{
  if (m_invmap.contains(request)) {
    // Fixme: !!!!
    // m_network_fetcher.cancel_request(request); // hash ???
    m_invmap.remove(request);
  }
}

void
NetworkDownloader::on_request_finished(const QcNetworkRequestPtr & request, const QByteArray & payload)
{
  qInfo() << "NetworkDownloader::request_finished" << request;
  if (m_invmap.contains(request)) {
    // Fixme:
    //! QcNetworkRequestPtr request = m_invmap.value(request); // pop ???
    //! m_invmap.remove(request);
    auto download_request = request.dynamicCast<NetworkDownloadRequest>();
    qInfo() << "request found" << download_request;
    QFile output_file(download_request->target_path());
    if (!output_file.open(QIODevice::WriteOnly | QIODevice::Text))
      qWarning() << "couldn't write to file";
    output_file.write(payload);
    emit finished(request);
  }
}

void
NetworkDownloader::on_request_error(const QcNetworkRequestPtr & request, const QString & error_string)
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
