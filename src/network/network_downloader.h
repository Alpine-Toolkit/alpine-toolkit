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

#ifndef __NETWORK_DOWNLOADER_H__
#define __NETWORK_DOWNLOADER_H__

/**************************************************************************************************/

#include <QHash>
#include <QObject>

#include "network_ressource_request.h"
#include "network_fetcher.h"

/**************************************************************************************************/

// request model
// retry

/* The class NetworkDownloadRequest defines the URL of the request and the path of the target.
 *
 */
class NetworkDownloadRequest : public NetworkRessourceRequest
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

unsigned int qHash(const NetworkDownloadRequest & request);

QDebug operator<<(QDebug debug, const NetworkDownloadRequest & request);

/**************************************************************************************************/

/* The class NetworkDownloader manages asynchronous ressource downloads.
 *
 */
class NetworkDownloader : public QObject
{
  Q_OBJECT

public:
  NetworkDownloader(NetworkFetcher & network_fetcher);
  ~NetworkDownloader();

  void add_request(const NetworkDownloadRequest & request);
  void cancel_request(const NetworkDownloadRequest & request);

signals:
  void download_progress(const NetworkRessourceRequest & request, qint64 percent);
  void finished(const NetworkRessourceRequest & request);
  void error(const NetworkRessourceRequest & request, const QString & error_string);

private slots:
  void request_finished(const NetworkRessourceRequest & request, const QByteArray & payload); // & ???
  void request_error(const NetworkRessourceRequest & request, const QString & error_string);

private:
  NetworkFetcher & m_network_fetcher;
  QHash<NetworkRessourceRequest, NetworkDownloadRequest> m_invmap; // NetworkRessourceRequest vs NetworkDownloadRequest
};

/**************************************************************************************************/

#endif /* __NETWORK_DOWNLOADER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
