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

#include "network_reply.h"

/**************************************************************************************************/

NetworkReply::NetworkReply(QNetworkReply * reply)
  : QObject(),
    m_error(NetworkReply::NoError),
    m_is_finished(false),
    m_reply(reply),
    m_url(reply->url())
{
  connect(m_reply, SIGNAL(finished()),
	  this, SLOT(network_reply_finished()));

  connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
	  this, SLOT(network_reply_error(QNetworkReply::NetworkError)));

  // downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
}

NetworkReply::~NetworkReply()
{
  if (m_reply) {
    m_reply->deleteLater();
    m_reply = nullptr;
  }
}

QUrl
NetworkReply::url() const
{
  return m_url;
}

void NetworkReply::set_finished(bool finished)
{
  m_is_finished = finished;
  if (m_is_finished)
    emit this->finished();
}

bool
NetworkReply::is_finished() const
{
  return m_is_finished;
}

void
NetworkReply::set_error(NetworkReply::Error error, const QString & error_string)
{
  m_error = error;
  m_error_string = error_string;
  emit this->error(error, error_string);
  set_finished(true); // will emit finished as well !
}

NetworkReply::Error
NetworkReply::error() const
{
  return m_error;
}

QString
NetworkReply::error_string() const
{
  return m_error_string;
}

QNetworkReply *
NetworkReply::network_reply() const
{
  return m_reply;
}

void
NetworkReply::abort()
{
  if (m_reply)
    m_reply->abort();

  // if (!is_finished())
  //   set_finished(true);
}

// Handle a successful request : store image data
void
NetworkReply::network_reply_finished()
{
  if (!m_reply)
    return;

  if (m_reply->error() != QNetworkReply::NoError) { // Fixme: when ?
    qWarning() << "reply != NoError";
    return;
  }

  QByteArray payload = m_reply->readAll();
  qInfo() << "Data:" << payload;

  // Fixme: duplicated code
  set_finished(true);
  m_reply->deleteLater();
  m_reply = nullptr;
}

// Handle an unsuccessful request : set error message
void
NetworkReply::network_reply_error(QNetworkReply::NetworkError error)
{
  if (!m_reply)
    return;

  if (error != QNetworkReply::OperationCanceledError)
    set_error(NetworkReply::CommunicationError, m_reply->errorString());

  set_finished(true);
  m_reply->deleteLater();
  m_reply = nullptr;
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
