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

QcNetworkDownloadRequest::QcNetworkDownloadRequest()
  : QcGetNetworkRequest(),
    m_target_path()
{}

QcNetworkDownloadRequest::QcNetworkDownloadRequest(const QUrl & url, const QString & target_path)
  : QcGetNetworkRequest(url),
    m_target_path(target_path)
{}

QcNetworkDownloadRequest::QcNetworkDownloadRequest(const QcNetworkDownloadRequest & other)
  : QcGetNetworkRequest(other),
    m_target_path(other.m_target_path)
{}

QcNetworkDownloadRequest &
QcNetworkDownloadRequest::operator=(const QcNetworkDownloadRequest & other)
{
  if (this != &other) {
    QcGetNetworkRequest::operator=(other);
    m_target_path = other.m_target_path;
  }

  return *this;
}

bool
QcNetworkDownloadRequest::operator==(const QcNetworkDownloadRequest & rhs) const
{
  return QcGetNetworkRequest::operator==(rhs) && m_target_path == rhs.m_target_path;
}

void
QcNetworkDownloadRequest::on_error(const QString & error_string)
{
  // Fixme:
  qInfo() << "QcNetworkDownloadRequest::on_error" << url() << error_string;
  emit error(); // error_string
}

void
QcNetworkDownloadRequest::on_data_received(const QByteArray & data)
{
  qInfo() << "QcNetworkDownloadRequest::on_data_received" << url();
  QFile output_file(m_target_path);
  if (!output_file.open(QIODevice::WriteOnly | QIODevice::Text))
    qWarning() << "couldn't write to file";
  output_file.write(data);
  emit finished();
}

QDebug
operator<<(QDebug debug, const QcNetworkDownloadRequest & request)
{
  debug << "QcNetworkDownloadRequest" << request.url().url() << "->" << request.target_path();
  return debug;
}

/**************************************************************************************************/

QcNetworkDownloader::QcNetworkDownloader()
  : QcNetworkRequestManager()
{}

QcNetworkDownloader::~QcNetworkDownloader()
{}

void
QcNetworkDownloader::add_request(const QcNetworkDownloadRequestPtr & request)
{
  qInfo() << "QcNetworkDownloader:add_request" << request;
  QcNetworkRequestManager::add_request(request);
}

void
QcNetworkDownloader::cancel_request(const QcNetworkDownloadRequestPtr & request)
{
  qInfo() << "QcNetworkDownloader:cancel_request" << request;
  QcNetworkRequestManager::cancel_request(request);
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
