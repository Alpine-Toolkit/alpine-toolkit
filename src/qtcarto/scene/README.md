# QtCarto Scene

```
QcMapScene > QObject
    -1-> QcViewport
    -1-> QcLocationCircleData
    -1-> QcDecoratedPathDouble
    -*-> QcMapLayerScene > QObject
        -1-> QcWmtsPluginLayer
        -1-> QcViewport
        -1-> QcTileMatrixSet
        -1-> QcTileMatrixSet "visible tiles"
        -1-> QcMapLayerRootNode > QSGOpacityNode
            -1-> QcViewport
            -1-> QcTileMatrixSet
            -*-> QHash<QcTileSpec, QSGTexture *> "textures"
            -1-> QcMapSideNode > QSGTransformNode "west, central, east"
                -1-> QHash<QcTileSpec, QSGSimpleTextureNode *> "texture nodes"

QcMapRootNode > QSGClipNode
    -1-> QcViewport
    -1-> QSGGeometry
    -1-> QSGTransformNode "root"
    -1-> QcLocationCircleNode
    -1-> QcPathNode
    -1-> QHash<QString, QcMapLayerRootNode *> "layers"
```

```
QcMapItem > QQuickItem
    -1-> QcMapGestureArea
    -1-> QcWmtsPluginManager
    -1-> QcMapPathEditor
    -1-> QcMapEventRouter
    -1-> QcMapView
    -1-> QcViewport
    -1-> QHash<QString, QVariantList> "plugin layers"
```

```
QcMapItem root node is
    QSGSimpleRectNode
        # QcMapView::update_scene_graph() -> QcMapScene::update_scene_graph()
        QcMapRootNode > QSGClipNode
            QSGTransformNode
                QcLocationCircleNode > QSGOpacityNode
                    QSGGeometryNode
                QcPathNode
```
