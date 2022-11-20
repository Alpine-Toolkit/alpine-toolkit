# WMTS Cache

This module implements a WTMS tile cache.  So as to be memory efficient, the cache implements
several levels: decoded image on memory, encoded image on memory, image on disk for temporary and
offline use.

**Usage**
```
QString directory("...");
QcFileTileCache cache(directory);

cache.insert(tile_spec, bytes, format);

QSharedPointer<QcTileTexture> tile_texture = cache.get(tile_spec);
```

## TODO

* check API
  encapsulate (tile_spec, bytes, format)
  offline read/write incoherent API
* implements tools to manage the cache
