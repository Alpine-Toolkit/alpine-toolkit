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

QaNetworkDownloadRequest::QaNetworkDownloadRequest()
  : QaGetNetworkRequest(),
    m_target_path()
{}

QaNetworkDownloadRequest::QaNetworkDownloadRequest(const QUrl & url, const QString & target_path)
  : QaGetNetworkRequest(url),
    m_target_path(target_path)
{}

QaNetworkDownloadRequest::QaNetworkDownloadRequest(const QaNetworkDownloadRequest & other)
  : QaGetNetworkRequest(other),
    m_target_path(other.m_target_path)
{}

QaNetworkDownloadRequest &
QaNetworkDownloadRequest::operator=(const QaNetworkDownloadRequest & other)
{
  if (this != &other) {
    QaGetNetworkRequest::operator=(other);
    m_target_path = other.m_target_path;
  }

  return *this;
}

bool
QaNetworkDownloadRequest::operator==(const QaNetworkDownloadRequest & rhs) const
{
  return QaGetNetworkRequest::operator==(rhs) && m_target_path == rhs.m_target_path;
}

void
QaNetworkDownloadRequest::on_error(const QString & error_string)
{
  // Fixme:
  qInfo() << "QaNetworkDownloadRequest::on_error" << url() << error_string;
  emit error(); // error_string
}

void
QaNetworkDownloadRequest::on_data_received(const QByteArray & data)
{
  qInfo() << "QaNetworkDownloadRequest::on_data_received" << url();
  QFile output_file(m_target_path);
  if (!output_file.open(QIODevice::WriteOnly | QIODevice::Text))
    qWarning() << "couldn't write to file";
  output_file.write(data);
  emit finished();
}

QDebug
operator<<(QDebug debug, const QaNetworkDownloadRequest & request)
{
  debug << "QaNetworkDownloadRequest" << request.url().url() << "->" << request.target_path();
  return debug;
}

/**************************************************************************************************/

QaNetworkDownloader::QaNetworkDownloader()
  : QaNetworkRequestManager()
{}

QaNetworkDownloader::~QaNetworkDownloader()
{}

void
QaNetworkDownloader::add_request(const QaNetworkDownloadRequestPtr & request)
{
  qInfo() << "QaNetworkDownloader:add_request" << request;
  QaNetworkRequestManager::add_request(request);
}

void
QaNetworkDownloader::cancel_request(const QaNetworkDownloadRequestPtr & request)
{
  qInfo() << "QaNetworkDownloader:cancel_request" << request;
  QaNetworkRequestManager::cancel_request(request);
}
