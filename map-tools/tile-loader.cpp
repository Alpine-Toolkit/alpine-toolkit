/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include <QtDebug>
#include <QLoggingCategory>

/**************************************************************************************************/

#include "cache/offline_cache.h"
#include "coordinate/mercator.h"
#include "coordinate/wgs84.h"
#include "geometry/polygon.h"
#include "geometry/vector.h"
#include "logging/handler.h"
#include "wmts/wmts_plugin_manager.h"

// #include "map/tile_loader.h"

/***************************************************************************************************/

class TileFetcherHelper : public QObject
{
  Q_OBJECT;

 public:
  TileFetcherHelper(QcOfflineTileCache * offline_cache)
    : m_offline_cache(offline_cache)
  {}

 public:
  int number_of_received_tiles() const {
    return m_finished_tile.size();
  }
  bool has_received(const QcTileSpec & tile_spec) const {
    return m_finished_tile.contains(tile_spec);
  }

 public slots:
  void tile_finished(const QcTileSpec & tile_spec, const QByteArray & bytes, const QString & format) {
    qInfo() << "Tile finished" << tile_spec;
    m_finished_tile.push_back(tile_spec);
    m_offline_cache->insert(tile_spec, bytes, format);
  }

 private:
  QcOfflineTileCache * m_offline_cache;
  QList<QcTileSpec> m_finished_tile;
};

/**************************************************************************************************/

class Application : public QCoreApplication
{
  Q_OBJECT;

public:
  Application(int & argc, char ** argv);

public slots:
  void main_task();
};

Application::Application(int & argc, char ** argv)
  : QCoreApplication(argc, argv)
{
  QTimer::singleShot(0, this, SLOT(main_task()));
}

void
Application::main_task()
{
  QcWmtsPluginManager & plugin_manager = QcWmtsPluginManager::instance();

  QcWmtsPlugin * geoportail_plugin = plugin_manager["geoportail"];

  const QcTileMatrixSet & tile_matrix_set = geoportail_plugin->tile_matrix_set();

  // QcTileLoader tile_loader(geoportail_plugin);

  // 7 r jean baillet 95870 Bezons
  // coordinate changed QcGeoCoordinate<epsg:4326>(2.20624, 48.9246)
  // coordinate 48° 55' 28.4" N, 2° 12' 22.4" E, 73.2m
  // double longitude =  2.206321;
  // double latitude  = 48.924621;

  // Centre de la France
  // double longitude =  2.43227;
  // double latitude  = 46.768219;

  // Annecy
  // double longitude =  6.311331853277862;
  // double latitude  = 45.956298260767284;

  // Bérarde
  // double longitude =  6.2914;
  // double latitude  = 44.9328;

  // ailefroide 05340 Vallouise-Pelvoux
  // pré de Madame Carle 44.9185 , 6.415823
  // double longitude =  6.446528;
  // double latitude  = 44.888335;

  // Vallouise
  // double longitude =  6.4895;
  // double latitude  = 44.8461;

  // Centre
  // double longitude = 3;
  // double latitude = 46.5;

  // Freissinieres
  // double longitude =  6.5383;
  // double latitude  = 44.7523;

  // Mont-dore
  // double longitude =  2.816;
  // double latitude = 45.54;

  // Mont-Blanc
  // double longitude =  6.86;
  // double latitude  = 45.83;

  // Valmeinier
  // http://www.refuge-terre-rouge.fr/fr/il4-refuge,ete_p7-situation-et-acces.aspx
  // GPS Valmeinier La sausse (emplacement du refuge) : 45°07'50.3'' N / 6°30'44.5'' E
  // double longitude =  6.51;
  // double latitude  = 45.13;

  // Camping Sollières
  // double longitude =  6.81;
  // double latitude  = 45.26;

  // Grenoble
  double longitude = 5.737267;
  double latitude  = 45.185788;

  QcWgsCoordinate center_wsg84(longitude, latitude);
  QcPseudoWebMercatorCoordinate center_mercator = center_wsg84.pseudo_web_mercator();
  QcVectorDouble center = center_mercator.vector();;
  // double radius_m = 500 * 1000;
  double radius_m = 30 * 1000;
  // double radius_m = 10 * 1000;
  QcVectorDouble half_diagonal_m(radius_m, radius_m);

  QcVectorDouble point1 = center + half_diagonal_m;
  QcVectorDouble point2 = center + half_diagonal_m.mirror_x();
  QcVectorDouble point3 = center + half_diagonal_m.rotate_180();
  QcVectorDouble point4 = center + half_diagonal_m.mirror_y();
  QcPolygon polygon;
  polygon.add_vertex(point3);
  polygon.add_vertex(point2);
  polygon.add_vertex(point1);
  polygon.add_vertex(point4);

  const QcInterval2DDouble & interval = polygon.interval();
  qInfo() << "polygon interval"
          << "[" << interval.x().inf() << ", " << interval.x().sup() << "]"
          << "x"
          << "[" << interval.y().inf() << ", " << interval.y().sup() << "]";

  QcWmtsNetworkTileFetcher * tile_fetcher = geoportail_plugin->tile_fetcher(); // subclass QcGeoportailPlugin ???

  QcOfflineTileCache * offline_cache = geoportail_plugin->wmts_manager()->tile_cache()->offline_cache();
  TileFetcherHelper tile_fetcher_helper(offline_cache);
  QObject::connect(tile_fetcher, &QcWmtsNetworkTileFetcher::tile_finished,
                   &tile_fetcher_helper, &TileFetcherHelper::tile_finished);

  QString layer_title = "Carte topographique";
  // QString layer_title = "Carte"; // error
  // QString layer_title = "Vue aérienne";
  int map_id = geoportail_plugin->layer(layer_title)->map_id();

  QSet<QcTileSpec> tiles_added;
  QSet<QcTileSpec> tiles_removed;

  // Fixme: level <= 10 : any tiles
  // from 5
  // const int level_max = 10; // France = 678 tiles
  int level_max = 16;
  for (int level = 0; level <= level_max; level++) {
    double tile_length_m = tile_matrix_set[level].tile_length_m();
    QcTiledPolygon tiled_polygon = polygon.intersec_with_grid(tile_length_m);
    for (const QcTiledPolygonRun & run:  tiled_polygon.runs()) {
      const QcIntervalInt & run_interval = run.interval();
      qInfo() << "Run " << run.y() << " [" << run_interval.inf() << ", " << run_interval.sup() << "]";
      for (int x = run_interval.inf(); x <= run_interval.sup(); x++) {
        QcTileSpec tile_spec = geoportail_plugin->create_tile_spec(map_id, level, x, run.y());
        if (offline_cache->contains(tile_spec)) {
          qInfo() << "Ok" << tile_spec;
        }
        else {
          qInfo() << "Missing" << tile_spec;
          tiles_added << tile_spec;
        }
      }
    }
  }
  int number_of_tiles = tiles_added.size();

  // Add tiles to disk
  //  tile_fetcher::tile_finished -> QcWmtsManager::fetcher_tile_finished -> tile_cache()->insert
  //
  // Fixme:
  //   check if on disk
  //   just save
  //   don't count in online cache

  tile_fetcher->update_tile_requests(tiles_added, tiles_removed);
  while (tile_fetcher_helper.number_of_received_tiles() != number_of_tiles) {
    processEvents();
    // QThread::msleep(10);
  }

  exit(0);
}

/**************************************************************************************************/

int
main(int argc, char *argv[])
{
  qInstallMessageHandler(message_handler);
  QLoggingCategory::setFilterRules("*.warning=true");
  QLoggingCategory::setFilterRules("*.info=true");
  // QLoggingCategory::setFilterRules("*.debug=true");
  Application application(argc, argv);
  return application.exec();
}

/***************************************************************************************************/

#include "tile-loader.moc"
