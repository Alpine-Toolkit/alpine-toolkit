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

/**************************************************************************************************/

NetworkReply::NetworkReply(const NetworkRessourceRequest & request, QNetworkReply * reply)
  : QObject(),
    m_request(request),
    m_reply(reply),
    m_is_finished(false),
    m_error(NetworkReply::NoError)
{
  connect(m_reply, SIGNAL(finished()),
	  this, SLOT(reply_finished()));

  connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
	  this, SLOT(reply_error(QNetworkReply::NetworkError)));

  connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)),
	  this, SLOT(_download_progress(qint64, qint64)));
}

NetworkReply::~NetworkReply()
{
  if (m_reply) {
    m_reply->deleteLater();
    m_reply = nullptr; // dtor ???
  }
}

void NetworkReply::set_finished(bool finished)
{
  m_is_finished = finished;
  if (m_is_finished)
    emit this->finished();
}

void
NetworkReply::set_error(NetworkReply::Error error, const QString & error_string)
{
  m_error = error;
  m_error_string = error_string;
  emit this->error(error, error_string);
  set_finished(true); // will emit finished as well !
}

void
NetworkReply::abort()
{
  if (m_reply)
    m_reply->abort();

  // ???
  // if (!is_finished())
  //   set_finished(true);
}

void
NetworkReply::release() {
  set_finished(true);
  m_reply->deleteLater();
  m_reply = nullptr;
}

// Handle a successful request : store image data
void
NetworkReply::reply_finished()
{
  if (!m_reply)
    return;

  if (m_reply->error() != QNetworkReply::NoError) { // Fixme: when ?
    qWarning() << "reply != NoError";
    return;
  }

  m_payload = m_reply->readAll();
  release();
}

// Handle an unsuccessful request : set error message
void
NetworkReply::reply_error(QNetworkReply::NetworkError error)
{
  if (!m_reply)
    return;

  if (error != QNetworkReply::OperationCanceledError)
    set_error(NetworkReply::CommunicationError, m_reply->errorString());
  release();
}

void
NetworkReply::_download_progress(qint64 bytes_received, qint64 bytes_total)
{
  // qInfo() << "_download_progress" << bytes_received << bytes_total;
  emit download_progress(m_request, qRound64(100. * bytes_received / (qreal) bytes_total));
}

/***************************************************************************************************
 *
 * end
 *
 **************************************************************************************************/
