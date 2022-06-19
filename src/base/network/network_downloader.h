// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
