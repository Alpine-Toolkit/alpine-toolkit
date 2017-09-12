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

// Fixme: Qc / Qa clash

#ifndef __QA_NETWORK_REPLY_H__
#define __QA_NETWORK_REPLY_H__

/**************************************************************************************************/

#include "network/network_request.h"

#include <QNetworkReply>
#include <QPointer>

/**************************************************************************************************/

/* The QaNetworkReply class encapsulates a request and a QaNetworkReply instance.
 *
 */
class QaNetworkReply : public QObject
{
  Q_OBJECT

public:
  enum Error { // Fixme: check, class enum
    NoError,
    CommunicationError,
    UnknownError
  };

public:
  explicit QaNetworkReply(const QaNetworkRequestPtr & request, QNetworkReply * reply);
  // QaNetworkReply(Error error, const QString & error_string); // Fixme: ???
  Q_DISABLE_COPY(QaNetworkReply);
  ~QaNetworkReply();

  const QaNetworkRequestPtr & request() const { return m_request; }
  QNetworkReply * network_reply() const { return m_reply; }

  void abort();

  int completion() const { return m_completion; }

  bool is_finished() const { return m_is_finished; }
  bool succeed() const { return m_is_finished and m_error == NoError; }

  Error error() const { return m_error; };
  QString error_string() const { return m_error_string; };

  // const QByteArray & payload() const { return m_payload; };

signals:
  // void download_progress(const NetworkRessourceRequest & request, qint64 percent);
  void finished();
  void error();

protected:
  void set_finished(bool finished);
  void set_error(Error error, const QString & error_string);

private:
  void release();
  void set_completion(qint64 bytes_done, qint64 bytes_total);

private slots:
  void on_download_progress(qint64 bytes_received, qint64 bytes_total);
  void on_upload_progress(qint64 bytes_sent, qint64 bytes_total);
  void on_reply_finished();
  void on_reply_error(QNetworkReply::NetworkError error);

private:
  QaNetworkRequestPtr m_request;
  QPointer<QNetworkReply> m_reply; // guarded pointer set to nullptr when destroyed
  int m_completion = 0;
  bool m_aborted = false;
  bool m_is_finished = false;
  Error m_error = QaNetworkReply::NoError;
  QString m_error_string;
  // QByteArray m_payload;
};

/**************************************************************************************************/

#endif /* __QA_NETWORK_REPLY_H__ */
