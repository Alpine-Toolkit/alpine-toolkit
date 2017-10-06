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

#include "network_reply.h"
#include "alpine_toolkit.h"

/**************************************************************************************************/

QaNetworkReply::QaNetworkReply(const QaNetworkRequestPtr & request, QNetworkReply * reply)
  : QObject(),
    m_request(request),
    m_reply(reply),
    m_is_finished(false), // Fixme: others
    m_error(QaNetworkReply::NoError)
{
  connect(m_reply, &QNetworkReply::downloadProgress, this, &QaNetworkReply::on_download_progress);
  connect(m_reply, &QNetworkReply::uploadProgress, this, &QaNetworkReply::on_upload_progress);
  connect(m_reply, &QNetworkReply::finished, this, &QaNetworkReply::on_reply_finished);
  // Fixme: compilation error ???
  // connect(m_reply, &QNetworkReply::error, this, &QaNetworkReply::on_reply_error);
  connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
	  this, SLOT(on_reply_error(QNetworkReply::NetworkError)));
}

QaNetworkReply::~QaNetworkReply()
{
  qATInfo() << "~QaNetworkReply";
  if (m_reply) {
    m_reply->deleteLater();
    m_reply = nullptr; // dtor ???
  }
}

void QaNetworkReply::set_finished(bool finished)
{
  m_is_finished = finished;
  if (m_is_finished)
    emit this->finished();
}

void
QaNetworkReply::set_error(QaNetworkReply::Error error, const QString & error_string)
{
  m_error = error;
  m_error_string = error_string;
  emit this->error(); // error, error_string
  set_finished(true); // will emit finished as well !
}

void
QaNetworkReply::abort()
{
  if (m_reply)
    m_reply->abort();
  m_aborted = true; // Fixme: ???

  // Fixme: ???
  // if (!is_finished())
  //   set_finished(true);
}

void
QaNetworkReply::release()
{
  set_finished(true); // emit finished
  m_reply->deleteLater();
  m_reply = nullptr;
}

// Handle a successful request :
void
QaNetworkReply::on_reply_finished()
{
  if (!m_reply) // Fixme: ???
    return;

  if (m_reply->error() == QNetworkReply::NoError) { // Fixme: when ?
      QByteArray payload = m_reply->readAll();
      m_request->on_data_received(payload);
      // QaNetworkRequest::RequestType request_type = m_request->type();
      // if (request_type == QaNetworkRequest::RequestType::Get) {
      //   auto get_request = m_request.dynamicCast<QaGetNetworkRequest>();
      //   QByteArray payload = m_reply->readAll();
      //   get_request->on_data_received(payload);
      // } else if(request_type == QaNetworkRequest::RequestType::Post) {
      //   auto post_request = m_request.dynamicCast<QaPostNetworkRequest>();
      //   post_request->on_success();
      // }
    release(); // emit finished

  } else {
    qWarning() << "reply != NoError";
  }
}

// Handle an unsuccessful request : set error message
void
QaNetworkReply::on_reply_error(QNetworkReply::NetworkError error)
{
  if (!m_reply)
    return;

  if (error != QNetworkReply::OperationCanceledError)
    set_error(QaNetworkReply::CommunicationError, m_reply->errorString()); // Fixme: emit error and finished
  release(); // emit finished
  m_request->on_error(m_error_string);
}

void
QaNetworkReply::set_completion(qint64 bytes_done, qint64 bytes_total)
{
  if (bytes_total > 0)
    m_completion = qRound64(100. * bytes_done / (qreal) bytes_total);
  else
    m_completion = 0;
}

void
QaNetworkReply::on_download_progress(qint64 bytes_received, qint64 bytes_total)
{
  set_completion(bytes_received, bytes_total);
  qATInfo() << "on_download_progress" << m_completion << "\%";
  // emit download_progress(m_request, download_progress);
}

void
QaNetworkReply::on_upload_progress(qint64 bytes_sent, qint64 bytes_total)
{
  set_completion(bytes_sent, bytes_total);
  qATInfo() << "on_upload_progress" << m_completion << "\%";
  // emit upload_progress(m_request, upload_progress);
}

/***************************************************************************************************
 *
 * end
 *
 **************************************************************************************************/
