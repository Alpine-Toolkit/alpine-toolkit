// -*- mode: c++ -*-

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

#ifndef __NETWORK_DOWNLOADER_H__
#define __NETWORK_DOWNLOADER_H__

/**************************************************************************************************/

#include <QHash>
#include <QObject>

#include "network/network_request.h"
#include "network/network_request_manager.h"

/**************************************************************************************************/

/* Fixme:
 * request model
 * retry
 */

/**************************************************************************************************/

/* The class NetworkDownloadRequest defines the URL of the request and the path of the target.
 *
 */
class NetworkDownloadRequest : public QcGetNetworkRequest
{
  Q_OBJECT

public:
  NetworkDownloadRequest();
  NetworkDownloadRequest(const QUrl & url, const QString & target_path);
  NetworkDownloadRequest(const NetworkDownloadRequest & other);

  NetworkDownloadRequest & operator=(const NetworkDownloadRequest & other);

  QString target_path() const { return m_target_path; }

  bool operator==(const NetworkDownloadRequest & rhs) const;

private:
  QString m_target_path;
};

QDebug operator<<(QDebug debug, const NetworkDownloadRequest & request);

/**************************************************************************************************/

/* The class NetworkDownloader manages asynchronous ressource downloads.
 *
 */
class NetworkDownloader : public QObject
{
  Q_OBJECT

public:
  NetworkDownloader(QcNetworkRequestManager & network_fetcher);
  ~NetworkDownloader();

  void add_request(const QcNetworkRequestPtr & request); // Fixme: NetworkDownloadRequest
  void cancel_request(const QcNetworkRequestPtr & request);

signals:
  // void download_progress(const QcNetworkRequestPtr & request, qint64 percent);
  void finished(const QcNetworkRequestPtr & request);
  void error(const QcNetworkRequestPtr & request, const QString & error_string);

private slots:
  void on_request_finished(const QcNetworkRequestPtr & request, const QByteArray & payload); // & ???
  void on_request_error(const QcNetworkRequestPtr & request, const QString & error_string);

private:
  QcNetworkRequestManager & m_network_fetcher;
  QHash<QcNetworkRequestPtr, QcNetworkRequestPtr> m_invmap;
};

/**************************************************************************************************/

#endif /* __NETWORK_DOWNLOADER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
