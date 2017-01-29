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

#include "camptocamp/camptocamp_client.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QList>
#include <QtDebug>

using namespace c2c;

/**************************************************************************************************/

C2cLoginData::C2cLoginData()
  : m_language(),
    m_expire(),
    m_id(),
    m_token(),
    m_forum_username(),
    m_name(),
    m_roles(),
    m_redirect_internal(),
    m_username()
{}

C2cLoginData::C2cLoginData(const C2cLoginData & other)
  : m_language(other.m_language),
    m_expire(other.m_expire),
    m_id(other.m_id),
    m_token(other.m_token),
    m_forum_username(other.m_forum_username),
    m_name(other.m_name),
    m_roles(other.m_roles),
    m_redirect_internal(other.m_redirect_internal),
    m_username(other.m_username)
{}

C2cLoginData::~C2cLoginData()
{}

void
C2cLoginData::from_json(const QJsonDocument * json_document)
{
  QJsonObject root = json_document->object();
  m_language = root[QStringLiteral("lang")].toString();
  m_expire = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(root[QStringLiteral("expire")].toInt()) * 1000);
  // set_expire(QDateTime::fromSecsSinceEpoch(root[QStringLiteral("expire")].toInt()));
  m_id = root[QStringLiteral("id")].toInt();
  m_token = root[QStringLiteral("token")].toString();
  m_forum_username = root[QStringLiteral("forum_username")].toString();
  m_name = root[QStringLiteral("name")].toString();
  m_roles = root[QStringLiteral("roles")].toString();
  m_redirect_internal = root[QStringLiteral("redirect_internal")].toString();
  m_username = root[QStringLiteral("username")].toString();
}

void
C2cLoginData::reset()
{
  m_id = 0;
  m_expire = QDateTime();

  m_language.clear();
  m_token.clear();
  m_forum_username.clear();
  m_name.clear();
  m_roles.clear();
  m_redirect_internal.clear();
  m_username.clear();
}

C2cLoginData &
C2cLoginData::operator=(const C2cLoginData & other)
{
  if (this != &other) {
    m_language = other.m_language;
    m_expire = other.m_expire;
    m_id = other.m_id;
    m_token = other.m_token;
    m_forum_username = other.m_forum_username;
    m_name = other.m_name;
    m_roles = other.m_roles;
    m_redirect_internal = other.m_redirect_internal;
    m_username = other.m_username;
  }

  return *this;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const C2cLoginData & login_data)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace() << QLatin1Literal("C2cLoginData(") << '\n'; // std::endl
  debug << "  id: " << login_data.id() << '\n';
  debug << "  username: " << login_data.username() << '\n';
  debug << "  expire: " << login_data.expire() << '\n';
  debug << "  token: " << login_data.token() << '\n';
  debug << "  forum username: " << login_data.forum_username() << '\n';
  debug << "  name: " << login_data.name() << '\n';
  debug << "  language: " << login_data.language() << '\n';
  debug << "  redirect interval: " << login_data.redirect_internal() << '\n';
  debug << "  roles: " << login_data.roles() << '\n';
  debug << ')';

  return debug;
}
#endif

/**************************************************************************************************/

C2cSearchSettings::C2cSearchSettings()
  : m_language(QStringLiteral("fr")),
    m_limit(7),
    m_area(),
    m_article(),
    m_book(),
    m_image(),
    m_map(),
    m_outing(),
    m_route(),
    m_userprofile(),
    m_waypoint(),
    m_xreport()
{}

C2cSearchSettings::C2cSearchSettings(const C2cSearchSettings & other)
  : m_language(other.m_language),
    m_limit(other.m_limit),
    m_area(other.m_area),
    m_article(other.m_article),
    m_book(other.m_book),
    m_image(other.m_image),
    m_map(other.m_map),
    m_outing(other.m_outing),
    m_route(other.m_route),
    m_userprofile(other.m_userprofile),
    m_waypoint(other.m_waypoint),
    m_xreport(other.m_xreport)
{}

C2cSearchSettings::~C2cSearchSettings()
{}

C2cSearchSettings &
C2cSearchSettings::operator=(const C2cSearchSettings & other)
{
  if (this != &other) {
    m_language = other.m_language;
    m_limit = other.m_limit;
    m_area = other.m_area;
    m_article = other.m_article;
    m_book = other.m_book;
    m_image = other.m_image;
    m_map = other.m_map;
    m_outing = other.m_outing;
    m_route = other.m_route;
    m_userprofile = other.m_userprofile;
    m_waypoint = other.m_waypoint;
    m_xreport = other.m_xreport;
  }

  return *this;
}

QString
C2cSearchSettings::type_letters() const
{
  QStringList letters;
  if (m_area)
    letters << QStringLiteral("a");
  if (m_article)
    letters << QStringLiteral("c");
  if (m_book)
    letters << QStringLiteral("b");
  if (m_image)
    letters << QStringLiteral("i");
  if (m_map)
    letters << QStringLiteral("m");
  if (m_outing)
    letters << QStringLiteral("o");
  if (m_route)
    letters << QStringLiteral("r");
  if (m_userprofile)
    letters << QStringLiteral("u");
  if (m_xreport)
    letters << QStringLiteral("x");
  if (m_waypoint)
    letters << QStringLiteral("w");

  return letters.join(',');
}

/**************************************************************************************************/

C2cClient::C2cClient(const QString & api_url, int port)
  : QObject(),
    m_api_url(api_url),
    m_port(port),
    m_login(),
    m_login_data(),
    m_network_manager()
{}

QUrl
C2cClient::make_url(const QString & endpoint) const
{
  QUrl url(m_api_url + '/' + endpoint);
  url.setPort(m_port);
  return url;
}

QUrl
C2cClient::make_url(const QStringList & strings) const
{
  return make_url(strings.join('/'));
}

QNetworkRequest
C2cClient::create_network_request(const QStringList & strings, bool token) const
{
  return create_network_request(make_url(strings), token);
}

QNetworkRequest
C2cClient::create_network_request(const QUrl & url, bool token) const
{
  QNetworkRequest request(url);
  // QStringLiteral().toLatin1() QLatin1String
  request.setRawHeader("User-Agent", "alpine-toolkit");
  request.setRawHeader("Content-Type", "application/json");
  if (token and is_logged()) {
    QString jwt_token = "JWT token=\"";
    jwt_token += m_login_data.token() + "\"";
    request.setRawHeader("Authorization", jwt_token.toLatin1());
  }
  return request;
}

QJsonDocument *
C2cClient::reply_to_json(QNetworkReply * reply) const
{
  QByteArray json_data = reply->readAll();
  qInfo() << "Json Reply" << json_data;
  return new QJsonDocument(QJsonDocument::fromJson(json_data));
}

bool
C2cClient::check_json_response(const QJsonDocument * json_document) const
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

void
C2cClient::get(const QNetworkRequest & request)
{
  qInfo() << "Get" << request.url();

  QNetworkReply * reply = m_network_manager.get(request);
  if (reply->isFinished())
    handle_get_reply(reply);
  else
    connect(reply, SIGNAL(finished()),
	    this, SLOT(get_reply_finished()),
	    Qt::QueuedConnection);
}

void
C2cClient::get_reply_finished()
{
  QNetworkReply * reply = qobject_cast<QNetworkReply *>(sender());
  if (reply)
    handle_get_reply(reply);
  else { // Fixme: when ?
    qWarning() << __FUNCTION__ << "Reply is null";
  }
}

void
C2cClient::handle_get_reply(QNetworkReply * reply)
{
  if (reply->error() == QNetworkReply::NoError) {
      QJsonDocument * json_document = reply_to_json(reply);
      // qInfo() << "Login Reply" << json_data;
      if (check_json_response(json_document)) {
        emit received_document(json_document);
      }
      // else emit
  } else {
    qWarning() << "Get failed" << reply->errorString();
    emit get_failed();
  }

  reply->deleteLater();
}

void
C2cClient::post(const QNetworkRequest & request, const QJsonDocument * json_document)
{
  if (not is_logged())
    return;
  update_login();

  QByteArray payload = json_document->toJson(QJsonDocument::Compact);
  qInfo() << "POST" << request.url() << payload;

  QNetworkReply * reply = m_network_manager.post(request, payload);
  if (reply->isFinished())
    handle_get_reply(reply);
  else
    connect(reply, SIGNAL(finished()),
	    this, SLOT(get_reply_finished()),
	    Qt::QueuedConnection);
}

void
C2cClient::login(const C2cLogin & login, bool remember, bool discourse)
{
  m_login = login;
  if (not login)
    return;

  // info('Login to camptocamp.org with user {} ...'.format(self._client_login.username))

  QJsonObject json_object;
  json_object[USERNAME] = login.username();
  json_object[PASSWORD] = login.password();
  json_object[REMEMBER] = remember;
  json_object[DISCOURSE] = discourse;
  QByteArray payload = QJsonDocument(json_object).toJson(QJsonDocument::Compact);

  QStringList string_list;
  string_list << USERS << LOGIN;
  QNetworkRequest request = create_network_request(string_list);
  qInfo() << "Post" << request.url() << payload;

  QNetworkReply * reply = m_network_manager.post(request, payload);
  if (reply->isFinished())
    handle_login_reply(reply);
  else
    connect(reply, SIGNAL(finished()),
	    this, SLOT(loggin_reply_finished()),
	    Qt::QueuedConnection);
}

void
C2cClient::update_login()
{
  if (is_logged() and m_login_data.is_expired()) {
    qInfo() << "Login expired";
    login(m_login); // Fixme:
  }
}

void
C2cClient::loggin_reply_finished()
{
  QNetworkReply * reply = qobject_cast<QNetworkReply *>(sender());
  if (reply)
    handle_login_reply(reply);
  else { // Fixme: when ?
    qWarning() << __FUNCTION__ << "Reply is null";
  }
}

void
C2cClient::handle_login_reply(QNetworkReply * reply)
{
  if (reply->error() == QNetworkReply::NoError) {
    QJsonDocument * json_document = reply_to_json(reply);
    // qInfo() << "Login Reply" << json_data;
    if (check_json_response(json_document)) {
      m_login_data.from_json(json_document);
      qInfo() << "Logged successfully" << '\n' << m_login_data;
      // info("Logged successfully, connection will expire at {}".format(self._login_data.expire))
      emit logged();
    } else {
      m_login_data.reset();
      // emit
    }
  } else {
    qWarning() << "Login failed" << reply->errorString();
    emit login_failed();
  }

  reply->deleteLater();
}

// Query the health of the REST API service
void
C2cClient::health()
{
  QStringList string_list;
  string_list << HEALTH;
  QNetworkRequest request = create_network_request(string_list);
  get(request);
}

void
C2cClient::get_document(const QString & document_type, unsigned int document_id)
{
  QStringList string_list;
  string_list << document_type << QString::number(document_id);
  QNetworkRequest request = create_network_request(string_list);
  get(request);
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
  QUrl url = make_url(SEARCH);
  QUrlQuery url_query(url);
  url_query.addQueryItem(QStringLiteral("q"), search_string);
  url_query.addQueryItem(QStringLiteral("pl"), settings.language());
  url_query.addQueryItem(QStringLiteral("limit"), QString::number(settings.limit()));
  url_query.addQueryItem(QStringLiteral("t"), settings.type_letters());
  url.setQuery(url_query);
  QNetworkRequest request = create_network_request(url);
  get(request);
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
  return make_url(string_list);
}

void
C2cClient::post(const QJsonDocument * json_document)
{
  QUrl url = make_url_for_document(json_document);
  QNetworkRequest request = create_network_request(url, true);
  post(request, json_document);
}

void
C2cClient::update(const QJsonDocument * json_document, const QString & message)
{
  QUrl url = make_url_for_document(json_document);
  QNetworkRequest request = create_network_request(url, true);
  QJsonDocument payload;
  QJsonObject root = payload.object();
  root[MESSAGE] = message;
  root[DOCUMENT] = json_document->object();
  // update(request, &payload);
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
