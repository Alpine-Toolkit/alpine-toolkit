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

#include "document/document_manager.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QUrlQuery>
#include <QList>
#include <QtDebug>

/**************************************************************************************************/

DocumentServerRequest::DocumentServerRequest(const QNetworkRequest & request)
  : QObject(),
    m_request(request)
{}

DocumentServerRequest::~DocumentServerRequest()
{
  // m_reply->deleteLater();
}

void
DocumentServerRequest::set_reply(DocumentManager * client, QNetworkReply * network_reply)
{
  m_client = client;
  m_network_reply = network_reply;

  if (network_reply->isFinished())
    finished();
  else
    connect(network_reply, SIGNAL(finished()),
	    this, SLOT(finished()),
	    Qt::QueuedConnection);
  // QueuedConnection: The slot is invoked when control returns to the
  // event loop of the receiver's thread. The slot is executed in the
  // receiver's thread.
}

void
DocumentServerRequest::finished()
{
  if (network_reply()->error() == QNetworkReply::NoError) {
    QJsonDocument * json_document = reply_to_json();
    handle_reply(json_document);
  } else
    handle_network_error();
}

QJsonDocument *
DocumentServerRequest::reply_to_json() const
{
  QByteArray json_data = network_reply()->readAll();
  qInfo() << "Json reply" << url() << '\n' << json_data;
  return new QJsonDocument(QJsonDocument::fromJson(json_data)); // Fixme: delete
}

void
DocumentServerRequest::handle_reply(const QJsonDocument * json_document)
{
  client()->handle_document_list_reply(json_document);
}

void
DocumentServerRequest::handle_network_error()
{
  qInfo() << "Network Error";
};

/**************************************************************************************************/

DocumentManager::DocumentManager(const QString & api_url, int port)
  : QObject(),
    m_api_url(api_url),
    m_port(port),
    m_network_manager()
{}

DocumentManager::~DocumentManager()
{}

QUrl
DocumentManager::make_api_url(const QString & endpoint) const
{
  QUrl url(m_api_url + '/' + endpoint);
  url.setPort(m_port);
  return url;
}

QNetworkRequest
DocumentManager::create_network_api_request(const QUrl & url) const
{
  QNetworkRequest request(url);
  request.setRawHeader("User-Agent", "alpine-toolkit"); // Fixme: QStringLiteral
  // request.setRawHeader("Content-Type", "application/json");
  return request;
}

QNetworkRequest
DocumentManager::create_network_api_request(const QString & endpoint) const
{
  return create_network_api_request(make_api_url(endpoint));
}

void
DocumentManager::get(DocumentServerRequest * request)
{
  // Fixme: if DocumentManager is friend, then we can move this code in C2cApiRequest
  qInfo() << "Get" << request->url();
  QNetworkReply * network_reply = m_network_manager.get(request->request());
  request->set_reply(this, network_reply);
}

void
DocumentManager::get_document_list()
{
  // http://127.0.0.1:8000/api/document/?document__date__gt=2017-04-21T18:28:11Z
  DocumentServerRequest * request = new DocumentServerRequest(create_network_api_request("document/?format=json")); // Fixme: delete
  get(request);
}

void
DocumentManager::handle_document_list_reply(const QJsonDocument * json_document)
{
  emit received_document_list(); // json_document
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
