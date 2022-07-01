/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "network_downloader.h"
#include "alpine_toolkit.h"

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
  qATInfo() << "QaNetworkDownloadRequest::on_error" << url() << error_string;
  emit error(); // error_string
}

void
QaNetworkDownloadRequest::on_data_received(const QByteArray & data)
{
  qATInfo() << "QaNetworkDownloadRequest::on_data_received" << url();
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
  qATInfo() << "QaNetworkDownloader:add_request" << request;
  QaNetworkRequestManager::add_request(request);
}

void
QaNetworkDownloader::cancel_request(const QaNetworkDownloadRequestPtr & request)
{
  qATInfo() << "QaNetworkDownloader:cancel_request" << request;
  QaNetworkRequestManager::cancel_request(request);
}
