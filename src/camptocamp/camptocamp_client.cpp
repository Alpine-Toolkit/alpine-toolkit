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

#include "camptocamp/camptocamp_client.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QUrlQuery>
#include <QList>
#include <QtDebug>

using namespace c2c;

/**************************************************************************************************/

C2cRequest::C2cRequest(const QNetworkRequest & request)
  : QObject(),
    m_request(request)
{}

C2cRequest::~C2cRequest()
{
  // m_reply->deleteLater();
}

void
C2cRequest::set_reply(C2cClient * client, QNetworkReply * network_reply)
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

/**************************************************************************************************/

// Fixme:
//  - public handle
//  - free C2cApiRequest and json document

C2cApiRequest::C2cApiRequest(const QNetworkRequest & request)
  : C2cRequest(request)
{}

C2cApiRequest::~C2cApiRequest()
{}

void
C2cApiRequest::finished()
{
  if (network_reply()->error() == QNetworkReply::NoError) {
    QJsonDocument * json_document = reply_to_json();
    if (check_json_response(json_document))
      handle_reply(json_document);
    else
      handle_error(json_document);
  } else
    handle_network_error();
}

QJsonDocument *
C2cApiRequest::reply_to_json() const
{
  QByteArray json_data = network_reply()->readAll();
  qInfo() << "Json reply" << url() << '\n' << json_data;
  return new QJsonDocument(QJsonDocument::fromJson(json_data)); // Fixme: delete
}

bool
C2cApiRequest::check_json_response(const QJsonDocument * json_document)
{
  QJsonObject root = json_document->object();
  if (root.contains(STATUS) and root[STATUS].toString() == ERROR) {
    // {'status': 'error', 'errors': [{'name': 'user', 'location': 'body', 'description': 'Login failed'}]}
    QJsonArray array = root[ERRORS].toArray();
    for (const auto & json_object : array)
      qWarning() << json_object.toObject()[DESCRIPTION]; // error !
    return false;
  } else
    return true;
}

/**************************************************************************************************/

class C2cLoginRequest : public C2cApiRequest
{
public:
  C2cLoginRequest(const QNetworkRequest & request)
    : C2cApiRequest(request)
  {}

  void handle_reply(const QJsonDocument * json_document) {
    client()->handle_login_reply(json_document);
  }

  void handle_error(const QJsonDocument * json_document) {
    client()->handle_login_error(json_document);
  }

  void handle_network_error() {
  }
};

/**************************************************************************************************/

class C2cHealthRequest : public C2cApiRequest
{
public:
  C2cHealthRequest(const QNetworkRequest & request)
    : C2cApiRequest(request)
  {}

  void handle_reply(const QJsonDocument * json_document) {
    client()->handle_health_reply(json_document);
  }

  void handle_error(const QJsonDocument * json_document) {
    client()->handle_health_error(json_document);
  }

  void handle_network_error() {
  }
};

/**************************************************************************************************/

class C2cSearchRequest : public C2cApiRequest
{
public:
  C2cSearchRequest(const QNetworkRequest & request)
    : C2cApiRequest(request)
  {}

  void handle_reply(const QJsonDocument * json_document) {
    client()->handle_search_reply(json_document);
  }

  void handle_error(const QJsonDocument * json_document) {
    client()->handle_search_error(json_document);
  }

  void handle_network_error() {
  }
};

/**************************************************************************************************/

class C2cDocumentRequest : public C2cApiRequest
{
public:
  C2cDocumentRequest(const QNetworkRequest & request)
    : C2cApiRequest(request)
  {}

  void handle_reply(const QJsonDocument * json_document) {
    client()->handle_document_reply(json_document);
  }

  void handle_error(const QJsonDocument * json_document) {
    client()->handle_document_error(json_document);
  }

  void handle_network_error() {
  }
};

/**************************************************************************************************/

C2cMediaRequest::C2cMediaRequest(const QNetworkRequest & request)
  : C2cRequest(request),
    m_media(request.url().fileName())
{
}

C2cMediaRequest::~C2cMediaRequest()
{}

void
C2cMediaRequest::finished()
{
  if (network_reply()->error() == QNetworkReply::NoError) {
    QByteArray data = network_reply()->readAll();
    client()->handle_media_reply(m_media, data);
  } else
    client()->handle_media_error(m_media);
}

/**************************************************************************************************/

C2cClient::C2cClient(const QString & api_url, const QString & media_url, int port)
  : QObject(),
    m_api_url(api_url),
    m_media_url(media_url),
    m_port(port),
    m_login(),
    m_login_data(),
    m_network_manager()
{}

QUrl
C2cClient::make_api_url(const QString & endpoint) const
{
  QUrl url(m_api_url + '/' + endpoint);
  url.setPort(m_port);
  return url;
}

QUrl
C2cClient::make_api_url(const QStringList & strings) const
{
  return make_api_url(strings.join('/'));
}

QUrl
C2cClient::make_media_url(const QString & media) const
{
  QUrl url(m_media_url + '/' + media);
  // url.setPort(m_port);
  return url;
}

QNetworkRequest
C2cClient::create_network_api_request(const QStringList & strings, bool token) const
{
  return create_network_api_request(make_api_url(strings), token);
}

QNetworkRequest
C2cClient::create_network_api_request(const QUrl & url, bool token) const
{
  QNetworkRequest request(url);
  // QStringLiteral().toLatin1() QLatin1String
  request.setRawHeader("User-Agent", "alpine-toolkit"); // Fixme: QStringLiteral
  request.setRawHeader("Content-Type", "application/json");
  if (token and is_logged()) {
    QString jwt_token = "JWT token=\"";
    jwt_token += m_login_data.token() + "\"";
    request.setRawHeader("Authorization", jwt_token.toLatin1());
  }
  return request;
}

QNetworkRequest
C2cClient::create_network_media_request(const QString & media) const
{
  QUrl url = make_media_url(media);
  QNetworkRequest request(url);
  request.setRawHeader("User-Agent", "alpine-toolkit");
  return request;
}

void
C2cClient::get(C2cApiRequest * request)
{
  // Fixme: if C2cClient is friend, then we can move this code in C2cApiRequest
  qInfo() << "Get" << request->url();
  QNetworkReply * network_reply = m_network_manager.get(request->request());
  request->set_reply(this, network_reply);
}

void
C2cClient::post(C2cApiRequest * request, const QJsonDocument * json_document, bool check_login)
{
  if (check_login) {
    if (not is_logged())
      return; // Fixme: emit ?
    update_login();
  }

  QByteArray payload = json_document->toJson(QJsonDocument::Compact);
  qInfo() << "Post" << request->url() << "payload" << '\n' << payload;
  QNetworkReply * network_reply = m_network_manager.post(request->request(), payload);
  request->set_reply(this, network_reply);
}

void
C2cClient::login(const C2cLogin & login, bool remember, bool discourse)
{
  m_login = login;
  if (not login)
    return;

  // info('Login to camptocamp.org with user {} ...'.format(self._client_login.username))

  QStringList string_list;
  string_list << USERS << LOGIN;
  C2cApiRequest * request = new C2cLoginRequest(create_network_api_request(string_list)); // Fixme: delete

  QJsonObject json_object;
  json_object[USERNAME] = login.username();
  json_object[PASSWORD] = login.password();
  json_object[REMEMBER] = remember;
  json_object[DISCOURSE] = discourse;
  QJsonDocument payload = QJsonDocument(json_object);

  post(request, &payload, false); // Fixme: QJsonDocument *
}

void
C2cClient::handle_login_reply(const QJsonDocument * json_document)
{
  m_login_data.from_json(json_document);
  qInfo() << "Logged successfully" << '\n' << m_login_data;
  // info("Logged successfully, connection will expire at {}".format(self._login_data.expire))
  emit logged();
}

void
C2cClient::handle_login_error(const QJsonDocument * json_document) // json_document unused
{
  Q_UNUSED(json_document);
  m_login_data.reset();
  emit login_failed();
}

void
C2cClient::update_login()
{
  if (is_logged() and m_login_data.is_expired()) {
    qInfo() << "Login expired";
    login(m_login); // Fixme:
  }
}

// Query the health of the REST API service
void
C2cClient::health()
{
  QStringList string_list;
  string_list << HEALTH;
  C2cApiRequest * request = new C2cHealthRequest(create_network_api_request(string_list)); // Fixme: delete
  get(request);
}

void
C2cClient::handle_health_reply(const QJsonDocument * json_document)
{
  emit received_health_status(json_document);
}

void
C2cClient::handle_health_error(const QJsonDocument * json_document)
{
  emit get_health_failed(json_document);
}

void
C2cClient::get_document(const QString & document_type, unsigned int document_id)
{
  QStringList string_list;
  string_list << document_type << QString::number(document_id);
  C2cApiRequest * request = new C2cDocumentRequest(create_network_api_request(string_list)); // Fixme: delete
  get(request);
}

void
C2cClient::handle_document_reply(const QJsonDocument * json_document)
{
  emit received_document(json_document);
}

void
C2cClient::handle_document_error(const QJsonDocument * json_document)
{
  emit get_document_failed(json_document);
}

void
C2cClient::area(unsigned int document_id)
{
  get_document(AREAS, document_id);
}

void
C2cClient::image(unsigned int document_id)
{
  get_document(IMAGES, document_id);
}

void
C2cClient::map(unsigned int document_id)
{
  get_document(MAPS, document_id);
}

void
C2cClient::outing(unsigned int document_id)
{
  get_document(OUTINGS, document_id);
}

void
C2cClient::route(unsigned int document_id)
{
  get_document(ROUTES, document_id);
}

void
C2cClient::user_profile(unsigned int user_id)
{
  if (user_id == 0) {
    if (is_logged())
      user_id = m_login_data.id();
    else
      return;
  }

  get_document(PROFILES, user_id);
}

void
C2cClient::xreport(unsigned int document_id)
{
  get_document(XREPORTS, document_id);
}

void
C2cClient::waypoint(unsigned int document_id)
{
  get_document(WAYPOINTS, document_id);
}

void
C2cClient::search(const QString & search_string, const C2cSearchSettings & settings)
{
  /*
   * Search documents
   *
   * https://github.com/c2corg/v6_api/blob/master/c2corg_api/views/search.py
   *
   * est:
   * `GET` `/search?q=...[&lang=...][&limit=...][&t=...]`
   *
   * meters:
   * `q=...`
   * The search word.
   *
   * `lang=...` (optional)
   * When set only the given locale will be included (if available).
   * Otherwise all locales will be returned.
   *
   * `limit=...` (optional)
   * How many results should be returned per document type
   * (default: 10). The maximum is 50.
   *
   * `t=...` (optional)
   * Which document types should be included in the search. If not
   * given, all document types are returned. Example: `...&t=w,r`
   * searches only for waypoints and routes.
   */

  // settings = SearchSettings()
  QUrl url = make_api_url(SEARCH);
  QUrlQuery url_query(url);

  url_query.addQueryItem(QStringLiteral("q"), search_string);
  url_query.addQueryItem(QStringLiteral("pl"), settings.language());
  url_query.addQueryItem(QStringLiteral("limit"), QString::number(settings.limit()));
  url_query.addQueryItem(QStringLiteral("t"), settings.type_letters());

  const C2cSearchSettings::FilterMap filters = settings.filters();
  for (const auto & key : filters.keys()) { // Fixme: better ? pair ?
    const QVariant & value = filters[key];
    QString string_value;
    if (value.type() == QVariant::StringList)
      string_value = value.toStringList().join(',');
    else
      string_value = value.toString();
    // qInfo() << key << value << value.toString() << string_value;
    url_query.addQueryItem(key, string_value);
  }

  url.setQuery(url_query);
  C2cApiRequest * request = new C2cSearchRequest(create_network_api_request(url)); // Fixme: delete
  get(request);
}

void
C2cClient::handle_search_reply(const QJsonDocument * json_document)
{
  emit received_search(json_document);
}

void
C2cClient::handle_search_error(const QJsonDocument * json_document)
{
  emit search_failed(json_document);
}

QUrl
C2cClient::make_url_for_document(const QJsonDocument * json_document) const
{
  QJsonObject root = json_document->object();
  const char type = root[TYPE].toString()[0].toLatin1();
  QString endpoint;
  switch (type) {
  case 'a':
    endpoint = AREAS;
    break;
  case 'c':
    endpoint = ARTICLES;
    break;
  case 'b':
    endpoint = BOOKS;
    break;
  case 'i':
    endpoint = IMAGES;
    break;
  case 'm':
    endpoint = MAPS;
    break;
  case 'o':
    endpoint = OUTINGS;
    break;
  case 'r':
    endpoint = ROUTES;
    break;
  case 'u':
    endpoint = USERPROFILES;
    break;
  case 'x':
    endpoint = XREPORTS;
    break;
  case 'w':
    endpoint = WAYPOINTS;
    break;
  }
  QString document_id = QString::number(root[DOCUMENT_ID].toInt());
  QStringList string_list;
  string_list << endpoint << document_id;
  return make_api_url(string_list);
}

void
C2cClient::post(const QJsonDocument * json_document)
{
  QUrl url = make_url_for_document(json_document);
  QNetworkRequest request = create_network_api_request(url, true);
  // post(request, json_document);
}

void
C2cClient::update(const QJsonDocument * json_document, const QString & message)
{
  QUrl url = make_url_for_document(json_document);
  QNetworkRequest request = create_network_api_request(url, true);
  QJsonDocument payload;
  QJsonObject root = payload.object();
  root[MESSAGE] = message;
  root[DOCUMENT] = json_document->object();
  // update(request, &payload);
}

void
C2cClient::media(const QString & media)
{
  C2cMediaRequest * request = new C2cMediaRequest(create_network_media_request(media)); // Fixme: delete
  QNetworkReply * network_reply = m_network_manager.get(request->request());
  request->set_reply(this, network_reply);
}

void
C2cClient::handle_media_reply(const QString & media, const QByteArray & data)
{
  emit received_media(media, data);
}

void
C2cClient::handle_media_error(const QString & media)
{
  emit get_media_failed(media);
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
