# QcCarto WMTS

The WMTS plugins are registered in the QcWmtsPluginManager singleton class and implemented as a subclass of QcWmtsPlugin.

A plugin can be lazily instantiated by:
```
auto plugin_manager = QcWmtsPluginManager::instance();
auto plugin_names = plugin_manager.plugin_names();
QcWmtsPlugin * plugin = plugin_manager["plugin name"];
```

A WMTS plugin is composed of a QcWmtsNetworkTileFetcher and a QcWmtsManager instance.

The QcWmtsNetworkTileFetcher class implements a tile fetcher that fetch tiles from a queue and send
a notification when the tile is available.


```
QcNetworkReply > QcNetworkFuture > QObject

QcElevationServiceReply > QcNetworkReply

QcLocationServiceQueryBase
QcLocationServiceQuery > QcLocationServiceQueryBase
QcLocationServiceReply > QcNetworkReply
QcLocationServiceReverseQuery > QcLocationServiceQueryBase
QcLocationServiceReverseReply > QcNetworkReply

QcTileMatrix
QcTileMatrixSet
QcMercatorTileMatrixSet > QcTileMatrixSet

QcTileSpec > QcTileMatrixIndex

QcWmtsPluginManager

QcWmtsPlugin > QObject
QcWmtsPluginLayer > QObject

QcWmtsNetworkTileFetcher > QcWmtsTileFetcher
QcWmtsTileFetcher > QObject
QcWmtsNetworkReply > QcWmtsReply > QcNetworkReply

QcRetryFuture > QObject
QcWmtsRequestManager > QObject

QcWmtsManager > QObject
```
