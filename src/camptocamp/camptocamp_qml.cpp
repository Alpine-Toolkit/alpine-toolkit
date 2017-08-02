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

#include "camptocamp/camptocamp_qml.h"

#include <QColor>
#include <QPixmap>
#include <QSize>

/**************************************************************************************************/

C2cQmlClient::C2cQmlClient(const QString & sqlite_path, const QString & media_path)
  : QObject(),
    m_client(),
    m_api_cache(sqlite_path),
    m_media_cache(media_path),
    m_login(),
    m_documents(),
    m_medias(),
    m_search_result()
{
  m_login = m_api_cache.login();

  connect(&m_client, &C2cClient::logged, this, &C2cQmlClient::on_logged);
  connect(&m_client, &C2cClient::login_failed, this, &C2cQmlClient::on_loggin_failed);

  // connect(&m_client, &C2cClient::logged), this, &C2cQmlClient::logged);
  // connect(&m_client, &C2cClient::login_failed, this, &C2cQmlClient::loggin_failed);

  connect(&m_client, &C2cClient::received_document, this, &C2cQmlClient::on_received_document);
  // connect(&m_client, &C2cClient::get_document_failed, this, &C2cQmlClient::on_get_document_failed);

  connect(&m_client, &C2cClient::received_media, this, &C2cQmlClient::on_received_media);
  // connect(&m_client, &C2cClient::get_media_failed), this, &C2cQmlClient::on_get_media_failed);

  connect(&m_client, &C2cClient::received_search, this, &C2cQmlClient::on_received_search);
  // connect(&m_client, &C2cClient::search_failed, this, &C2cQmlClient::on_search_failed);
}

/************************************************/

const QString &
C2cQmlClient::username() const
{
  return m_login.username();
}

void
C2cQmlClient::set_username(const QString & username)
{
  if (username != m_login.username()) {
    m_login.set_username(username);
    // save_login();
    emit usernameChanged(); // username
  }
}

const QString &
C2cQmlClient::password() const
{
  return m_login.password();
}

void
C2cQmlClient::set_password(const QString & password)
{
  if (password != m_login.password()) {
    m_login.set_password(password);
    // save_login();
    emit passwordChanged(); // password
  }
}

void
C2cQmlClient::save_login()
{
  m_api_cache.save_login(m_login);
}

void
C2cQmlClient::login()
{
  m_client.login(m_login);
}

void
C2cQmlClient::logout()
{
  // Fixme
}

void
C2cQmlClient::on_logged()
{
  emit loginStatusChanged();
  // emit logged();
}

void
C2cQmlClient::on_loggin_failed()
{
  emit loginStatusChanged();
  // emit on_loggin_failed();
}

/************************************************/

/*
bool
C2cQmlClient::look_for_document(unsigned int document_id, bool use_cache))
{
  if (use_cache and m_api_cache.has_document(document_id)) {
    emit receivedDocument(document_id);
    return true;
  } else
    return false;
}
*/

void
C2cQmlClient::load_document(unsigned int document_id, bool use_cache,
                            void (C2cClient::*loader)(unsigned int))
{
  if (use_cache and m_api_cache.has_document(document_id))
    emit receivedDocument(document_id);
  else
    // Fixme: could use C2cClient::get_document(const QString & document_type, unsigned int document_id)
    (m_client.*loader)(document_id);
}

void
C2cQmlClient::area(unsigned int document_id, bool use_cache)
{
  load_document(document_id, use_cache, &C2cClient::area);
}

void
C2cQmlClient::image(unsigned int document_id, bool use_cache)
{
  load_document(document_id, use_cache, &C2cClient::image);
}

void
C2cQmlClient::map(unsigned int document_id, bool use_cache)
{
  load_document(document_id, use_cache, &C2cClient::map);
}

void
C2cQmlClient::outing(unsigned int document_id, bool use_cache)
{
  load_document(document_id, use_cache, &C2cClient::route);
}

void
C2cQmlClient::user_profile(unsigned int user_id, bool use_cache)
{
  load_document(user_id, use_cache, &C2cClient::route);
}

void
C2cQmlClient::route(unsigned int document_id, bool use_cache)
{
  load_document(document_id, use_cache, &C2cClient::route);
}

void
C2cQmlClient::xreport(unsigned int document_id, bool use_cache)
{
  load_document(document_id, use_cache, &C2cClient::route);
}

void
C2cQmlClient::waypoint(unsigned int document_id, bool use_cache)
{
  load_document(document_id, use_cache, &C2cClient::route);
}

/************************************************/

void
C2cQmlClient::on_received_document(const QJsonDocumentPtr & json_document)
{
  // Fixme: ok ???
  C2cDocument document(*json_document);
  C2cDocumentPtr casted_document = document.cast();
  unsigned int document_id = document.id();
  m_documents.insert(document_id, casted_document);
  qInfo() << "C2cQmlClient::on_received_document" << *casted_document;
  emit receivedDocument(document_id);
}

bool
C2cQmlClient::is_document_cached(unsigned int document_id)
{
  // Fixme: cache ?
  return m_api_cache.has_document(document_id);
}

C2cDocument *
C2cQmlClient::get_document(unsigned int document_id, bool use_cache)
{
  // Fixme: db -> mem cache ?
  if (use_cache) {
    C2cDocumentPtr document = m_api_cache.get_document(document_id);
    if (not document.isNull()) {
      qInfo() << "Found document" << document_id << "in cache";
      m_documents.insert(document_id, document);
      return document.data();
    }
  }
  C2cDocumentPtr document = m_documents.value(document_id, nullptr);
  return document.data();
}

void
C2cQmlClient::save_document(unsigned int document_id)
{
  C2cDocumentPtr document = m_documents.value(document_id, nullptr);
  if (not document.isNull())
    m_api_cache.save_document(document);
}

/************************************************/

void
C2cQmlClient::search(const QString & search_string, const C2cSearchSettings & settings)
{
  m_client.search(search_string, settings);
}

void
C2cQmlClient::on_received_search(const QJsonDocumentPtr & json_document)
{
  qInfo() << "C2cQmlClient::on_received_search";
  m_search_result.update(json_document);
  emit receivedSearch();
}

/************************************************/

void
C2cQmlClient::media(const QString & media, bool use_cache)
{
  if (use_cache and m_media_cache.has_media(media)) {
    qInfo() << "Found media " << media << " in cache";
    QByteArray data = m_media_cache.get_media(media);
    on_received_media(media, data);
  } else
    m_client.media(media);
}

void
C2cQmlClient::on_received_media(const QString & media, QByteArray data)
{
  qInfo() << "C2cQmlClient::on_received_media" << media;
  m_medias.insert(media, QSharedPointer<QByteArray>(new QByteArray(data)));
  emit receivedMedia(media);
}

bool
C2cQmlClient::is_media_cached(const QString & media)
{
  // Fixme: cache ?
  return m_media_cache.has_media(media);
}

void
C2cQmlClient::save_media(const QString & media)
{
  QSharedPointer<QByteArray> data = m_medias.value(media, nullptr);
  if (data)
    m_media_cache.save_media(media, *data);
}

QSharedPointer<QByteArray>
C2cQmlClient::get_media(const QString & media)
{
  return m_medias.value(media, nullptr);
}

/************************************************/

void
C2cQmlClient::load_document_on_cache()
{
  m_document_on_cache.clear(); // Fixme: useless
  qInfo() << m_api_cache.number_of_documents() << "on cache";
  m_document_on_cache = m_api_cache.get_documents();
  for (const auto & document : m_document_on_cache) {
    qInfo() << document->id();
  }
  emit documentOnCacheChanged();
}

QQmlListProperty<C2cDocument>
C2cQmlClient::document_on_cache_list_property()
{
  // Called at init or when the list change
  // qInfo() << "C2cQmlClient::document_on_cache_list_property";
  return QQmlListProperty<C2cDocument>(this,
                                       nullptr, // data
                                       &C2cQmlClient::document_on_cache_list_property_count,
                                       &C2cQmlClient::document_on_cache_list_property_at);
}

int
C2cQmlClient::document_on_cache_list_property_count(QQmlListProperty<C2cDocument> * list)
{
  // Called several times
  // qInfo() << "C2cQmlClient::document_on_cache_list_property_count";
  C2cQmlClient * client = qobject_cast<C2cQmlClient *>(list->object);
  return client->m_document_on_cache.size();
}

C2cDocument *
C2cQmlClient::document_on_cache_list_property_at(QQmlListProperty<C2cDocument> * list, int index)
{
  // Called several times
  // qInfo() << "C2cQmlClient::document_on_cache_list_property_at" << index;
  C2cQmlClient * client = qobject_cast<C2cQmlClient *>(list->object);
  C2cDocumentPtr & document = client->m_document_on_cache[index];
  return document.data();
}

/**************************************************************************************************/

C2cImageProvider::C2cImageProvider(C2cQmlClient * client)
  : QQuickImageProvider(QQuickImageProvider::Pixmap),
    m_client(client)
{}

QPixmap
C2cImageProvider::requestPixmap(const QString & id, QSize * size, const QSize & requested_size)
{
  qInfo() << "C2C request pixmap" << id << size << requested_size;

  QPixmap pixmap;
  QSharedPointer<QByteArray> data = m_client->get_media(id);
  if (not data.isNull())
    pixmap.loadFromData(*data);

  if (size)
    *size = pixmap.size();

  QSize _size(requested_size.width() > 0 ? requested_size.width() : pixmap.width(),
              requested_size.height() > 0 ? requested_size.height() : pixmap.height());

  if (_size == pixmap.size())
    return pixmap;
  else
    return pixmap.scaled(_size);
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
