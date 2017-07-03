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

bool
C2cApiRequestMixin::check_json_response(const QJsonDocumentPtr & json_document)
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

QJsonDocumentPtr
C2cApiRequestMixin::to_json_document(const QByteArray & json_data)
{
  return QJsonDocumentPtr(new QJsonDocument(QJsonDocument::fromJson(json_data)));
}

/**************************************************************************************************/

C2cApiGetRequest::C2cApiGetRequest(const QUrl & url)
  : QcGetNetworkRequest(url),
    C2cApiRequestMixin()
{}

void
C2cApiGetRequest::on_error(const QString & error_string)
{
  // Fixme:
  qInfo() << "C2cApiGetRequest::on_error" << url() << error_string;
  emit error(nullptr);
}

void
C2cApiGetRequest::on_data_received(const QByteArray & json_data)
{
  qInfo() << "C2cApiGetRequest::on_data_received" << url() << '\n' << json_data;
  // Fixme: this code must be duplicated
  QJsonDocumentPtr json_document = to_json_document(json_data);
  if (check_json_response(json_document))
    emit finished(json_document);
  else
    emit error(json_document);
}

/**************************************************************************************************/

C2cApiPostRequest::C2cApiPostRequest(const QUrl & url, const QJsonDocument & document)
  : QcPostNetworkRequest(url, document),
    C2cApiRequestMixin()
{}

void
C2cApiPostRequest::on_error(const QString & error_string)
{
  // Fixme:
  qInfo() << "C2cApiPostRequest::on_error" << url() << error_string;
  emit error(nullptr);
}

void
C2cApiPostRequest::on_data_received(const QByteArray & json_data)
{
  qInfo() << "C2cApiPostRequest::on_data_received" << url() << '\n' << json_data;
  QJsonDocumentPtr json_document = to_json_document(json_data);
  if (check_json_response(json_document))
    emit finished(json_document);
  else
    emit error(json_document);
}

/**************************************************************************************************/

C2cApiMediaRequest::C2cApiMediaRequest(const QUrl & url)
  : QcGetNetworkRequest(url),
    m_media(url.fileName())
{}

void
C2cApiMediaRequest::on_error(const QString & error_string)
{
  // Fixme:
  qInfo() << "C2cApiMediaRequest::on_error" << url() << error_string;
  emit error(m_media);
}

void
C2cApiMediaRequest::on_data_received(const QByteArray & data)
{
  emit finished(m_media, data);
}

/**************************************************************************************************/

C2cNetworkRequestManager::C2cNetworkRequestManager(C2cClient * client)
  : QcNetworkRequestManager(),
    m_client(client)
{}

C2cNetworkRequestManager::~C2cNetworkRequestManager()
{}

QNetworkRequest
C2cNetworkRequestManager::make_request(const QcNetworkRequestPtr & request_ptr) const
{
  QNetworkRequest request = QcNetworkRequestManager::make_request(request_ptr);
  if (request_ptr->type() != QcNetworkRequest::RequestType::Get) {
    request.setRawHeader("Content-Type", "application/json"); // Fixme: here ?
    if (m_client->is_logged()) {
      QString jwt_token = "JWT token=\"";
      jwt_token += m_client->login_data().token() + "\"";
      request.setRawHeader("Authorization", jwt_token.toLatin1());
    }
  }
  return request;
}

/**************************************************************************************************/

C2cClient::C2cClient(const QString & api_url, const QString & media_url, int port)
  : QObject(),
    m_api_url(api_url),
    m_media_url(media_url),
    m_port(port),
    m_login(),
    m_login_data(),
    m_network_manager(this)
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

/*
void
C2cClient::check_login()
{
  if (is_logged())
    update_login();
}
*/

void
C2cClient::login(const C2cLogin & login, bool remember, bool discourse)
{
  m_login = login;
  if (not login)
    return;

  // info('Login to camptocamp.org with user {} ...'.format(self._client_login.username))

  QStringList string_list;
  string_list << USERS << LOGIN;

  QJsonObject json_object;
  json_object[USERNAME] = login.username();
  json_object[PASSWORD] = login.password();
  json_object[REMEMBER] = remember;
  json_object[DISCOURSE] = discourse;
  QJsonDocument payload = QJsonDocument(json_object);

  C2cApiPostRequest * request = new C2cApiPostRequest(make_api_url(string_list), payload);
  connect(request, &C2cApiPostRequest::finished, this, &C2cClient::on_login_reply);
  connect(request, &C2cApiPostRequest::error, this, &C2cClient::on_login_error);
  m_network_manager.add_request(request);
}

void
C2cClient::on_login_reply(const QJsonDocumentPtr & json_document)
{
  m_login_data.from_json(json_document);
  qInfo() << "Logged successfully" << '\n' << m_login_data;
  // info("Logged successfully, connection will expire at {}".format(self._login_data.expire))
  emit logged();
}

void
C2cClient::on_login_error(const QJsonDocumentPtr & json_document) // json_document unused
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
  C2cApiGetRequest * request = new C2cApiGetRequest(make_api_url(string_list));
  connect(request, &C2cApiGetRequest::finished, this, &C2cClient::received_health_status);
  connect(request, &C2cApiGetRequest::error, this, &C2cClient::get_health_failed);
  m_network_manager.add_request(request);
}

void
C2cClient::get_document(const QString & document_type, unsigned int document_id)
{
  QStringList string_list;
  string_list << document_type << QString::number(document_id);
  C2cApiGetRequest * request = new C2cApiGetRequest(make_api_url(string_list));
  connect(request, &C2cApiGetRequest::finished, this, &C2cClient::received_document);
  connect(request, &C2cApiGetRequest::error, this, &C2cClient::get_document_failed);
  m_network_manager.add_request(request);
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
  C2cApiGetRequest * request = new C2cApiGetRequest(url);
  connect(request, &C2cApiGetRequest::finished, this, &C2cClient::received_search);
  connect(request, &C2cApiGetRequest::error, this, &C2cClient::search_failed);
  m_network_manager.add_request(request);
}

QUrl
C2cClient::make_url_for_document(const QJsonDocumentPtr & json_document) const
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
C2cClient::post(const QJsonDocumentPtr & json_document)
{
  QUrl url = make_url_for_document(json_document);
  // Fixme: ...
}

void
C2cClient::update(const QJsonDocumentPtr & json_document, const QString & message)
{
  QUrl url = make_url_for_document(json_document);
  QJsonDocument payload;
  QJsonObject root = payload.object();
  root[MESSAGE] = message;
  root[DOCUMENT] = json_document->object();
  // Fixme: ...
}

void
C2cClient::media(const QString & media)
{
  C2cApiMediaRequest * request = new C2cApiMediaRequest(make_media_url(media));
  connect(request, &C2cApiMediaRequest::finished, this, &C2cClient::received_media);
  connect(request, &C2cApiMediaRequest::error, this, &C2cClient::get_media_failed);
  m_network_manager.add_request(request);
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
