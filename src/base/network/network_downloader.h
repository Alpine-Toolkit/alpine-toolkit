// -*- mode: c++ -*-

/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
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
#include <QSharedPointer>

#include "network/network_request.h"
#include "network/network_request_manager.h"

/**************************************************************************************************/

/* Fixme:
 * request model
 * retry
 */

/**************************************************************************************************/

/* The class QaNetworkDownloadRequest defines the URL of the request and the path of the target.
 *
 */
class QaNetworkDownloadRequest : public QaGetNetworkRequest
{
  Q_OBJECT

public:
  QaNetworkDownloadRequest();
  QaNetworkDownloadRequest(const QUrl & url, const QString & target_path);
  QaNetworkDownloadRequest(const QaNetworkDownloadRequest & other);

  QaNetworkDownloadRequest & operator=(const QaNetworkDownloadRequest & other);

  QString target_path() const { return m_target_path; }

  bool operator==(const QaNetworkDownloadRequest & rhs) const;

signals:
  void finished();
  void error();

public slots:
  void on_error(const QString & error_string);
  void on_data_received(const QByteArray & data);

private:
  QString m_target_path;
};

typedef QSharedPointer<QaNetworkDownloadRequest> QaNetworkDownloadRequestPtr;

QDebug operator<<(QDebug debug, const QaNetworkDownloadRequest & request);

/**************************************************************************************************/

/* The class QaNetworkDownloader manages asynchronous resource downloads.
 *
 */
class QaNetworkDownloader : public QaNetworkRequestManager
{
  Q_OBJECT

public:
  QaNetworkDownloader(); // QaNetworkRequestManager & network_fetcher
  ~QaNetworkDownloader();

  void add_request(const QaNetworkDownloadRequestPtr & request);
  void cancel_request(const QaNetworkDownloadRequestPtr & request);
};

/**************************************************************************************************/

#endif /* __NETWORK_DOWNLOADER_H__ */
