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

#include <QtTest/QtTest>
#include <QtDebug>

/**************************************************************************************************/

#include "network/network_reply.h"
#include "network/network_fetcher.h"
#include "network/network_downloader.h"

/***************************************************************************************************/

class NetworkFetcherHelper : public QObject
{
  Q_OBJECT;

public:
  bool has_received(const QUrl & url) {
    return m_finished_request.contains(url);
  }

public slots:
  void request_finished(const NetworkRessourceRequest & request) {
    QUrl url = request.url();
    qInfo() << "Url finished" << url.url();
    m_finished_request.push_back(url);;
  }
  void download_progress(const NetworkRessourceRequest & request, qint64 percent) {
    QUrl url = request.url();
    qInfo() << "download progress" << url.url() << percent;
  }

private:
  QList<QUrl> m_finished_request;
};

/**************************************************************************************************/

class TestNetwork: public QObject
{
  Q_OBJECT

private slots:
  void test_network_fetcher();
  void test_network_downloader();
};

void
TestNetwork::test_network_fetcher()
{
  QSKIP("");

  NetworkFetcher network_fetcher;

  NetworkFetcherHelper network_fetcher_helper;
  connect(&network_fetcher, &NetworkFetcher::request_finished,
  	  &network_fetcher_helper, &NetworkFetcherHelper::request_finished);

  QUrl url;
  url = QStringLiteral("http://127.0.0.1:5000/todos/todo1");
  network_fetcher.add_request(url);
  url = QStringLiteral("http://127.0.0.1:5000/todos/todo2");
  network_fetcher.add_request(url);
  while (!network_fetcher_helper.has_received(url)) // Fixme:
    QTest::qWait(200);
}

void
TestNetwork::test_network_downloader()
{
  NetworkFetcher network_fetcher;
  NetworkDownloader network_downloader(network_fetcher);

  NetworkFetcherHelper network_fetcher_helper;
  connect(&network_downloader, &NetworkDownloader::finished,
  	  &network_fetcher_helper, &NetworkFetcherHelper::request_finished);
  connect(&network_downloader, &NetworkDownloader::download_progress,
  	  &network_fetcher_helper, &NetworkFetcherHelper::download_progress);

  QUrl url;
  url = QStringLiteral("http://127.0.0.1:5000/static/large-file.txt");
  QString target_path = "request1.json";
  NetworkDownloadRequest request(url, target_path);
  network_downloader.add_request(request);
  while (!network_fetcher_helper.has_received(url)) // Fixme:
    QTest::qWait(200);
}

/**************************************************************************************************/

// QNetworkAccessManager *manager = new QNetworkAccessManager(this);
// manager->networkAccessible()

// connect(manager, SIGNAL(finished(QNetworkReply*)),
// 	  this, SLOT(replyFinished(QNetworkReply*)));

// manager->get(QNetworkRequest(QUrl("http://qt-project.org")));

// QNetworkReply *reply = manager->get(request);
// connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
// connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
//         this, SLOT(slotError(QNetworkReply::NetworkError)));
// connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
//         this, SLOT(slotSslErrors(QList<QSslError>)));

/***************************************************************************************************/

QTEST_MAIN(TestNetwork)
#include "test_network.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
