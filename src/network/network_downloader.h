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
#include <QSharedPointer>

#include "network/network_request.h"
#include "network/network_request_manager.h"

/**************************************************************************************************/

/* Fixme:
 * request model
 * retry
 */

/**************************************************************************************************/

/* The class QcNetworkDownloadRequest defines the URL of the request and the path of the target.
 *
 */
class QcNetworkDownloadRequest : public QcGetNetworkRequest
{
  Q_OBJECT

public:
  QcNetworkDownloadRequest();
  QcNetworkDownloadRequest(const QUrl & url, const QString & target_path);
  QcNetworkDownloadRequest(const QcNetworkDownloadRequest & other);

  QcNetworkDownloadRequest & operator=(const QcNetworkDownloadRequest & other);

  QString target_path() const { return m_target_path; }

  bool operator==(const QcNetworkDownloadRequest & rhs) const;

signals:
  void finished();
  void error();

public slots:
  void on_error(const QString & error_string);
  void on_data_received(const QByteArray & data);

private:
  QString m_target_path;
};

typedef QSharedPointer<QcNetworkDownloadRequest> QcNetworkDownloadRequestPtr;

QDebug operator<<(QDebug debug, const QcNetworkDownloadRequest & request);

/**************************************************************************************************/

/* The class QcNetworkDownloader manages asynchronous ressource downloads.
 *
 */
class QcNetworkDownloader : public QcNetworkRequestManager
{
  Q_OBJECT

public:
  QcNetworkDownloader(); // QcNetworkRequestManager & network_fetcher
  ~QcNetworkDownloader();

  void add_request(const QcNetworkDownloadRequestPtr & request);
  void cancel_request(const QcNetworkDownloadRequestPtr & request);
};

/**************************************************************************************************/

#endif /* __NETWORK_DOWNLOADER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
