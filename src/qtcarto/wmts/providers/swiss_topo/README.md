# Swiss Topo Plugin

https://www.swisstopo.admin.ch/fr/geodata/maps.html

https://www.swisstopo.admin.ch/fr/geodata/maps/smr/smr10.html
Swiss Map Raster 10 est la carte topographique de plus grande échelle produite par swisstopo. Elle
représente avec un grand niveau de détails les réseaux de transport, les localités, le terrain, la
végétation, ainsi que des écritures encore plus denses. Le contenu est complété avec la
représentation des rochers et du relief.

https://www.swisstopo.admin.ch/fr/geodata/maps/smv/smv10.html
Swiss Map Vector 10 est la carte nationale suisse 1:10 000 sous forme vectorielle. La carte
topographique de plus grande échelle produite par swisstopo représente avec un grand niveau de
détails les réseaux de transport, les localités, le terrain, la végétation, ainsi que des écritures
encore plus denses. **Des données Raster pour le relief et les falaises complètent les données
vectorielles.**

https://www.swisstopo.admin.ch/fr/geodata/maps/smw/smw_lightbase.html
La Light Base Map est une carte d’arrière-plan qui permet de donner à un thème de premier plan une
orientation spatiale optimale. La conception graphique de cette carte web basée sur la technologie
des tuiles vectorielles est donc discrète et son contenu réduit.

# WTMS

https://wmts.geo.admin.ch/1.0.0/WMTSCapabilities.xml
https://wmts.geo.admin.ch/1.0.0/WMTSCapabilities.xml?lang=fr
https://wmts.geo.admin.ch/EPSG/2056/1.0.0/WMTSCapabilities.xml
https://wmts.geo.admin.ch/EPSG/3857/1.0.0/WMTSCapabilities.xml

https://api3.geo.admin.ch/index.html
The GeoAdmin API allows the integration in web pages of geospatial information provided by the Swiss Confederation.

https://www.geo.admin.ch/fr/geo-services-proposes/geoservices/services-de-consultation-applications-cartographie-en-ligne-sig-web/web-map-tiling-services-wmts.html
https://api3.geo.admin.ch/services/sdiservices.html#wmts

* https://wmts100.geo.admin.ch/1.0.0/ch.swisstopo.pixelkarte-farbe/default/current/2056/23/312/469.jpeg
  Cartes nationales (couleur)
  2056 : EPSG code for LV03/CH1903
─ `<ResourceURL format="image/jpeg" resourceType="tile" template="https://wmts.geo.admin.ch/1.0.0/ch.swisstopo.pixelkarte-farbe/default/{Time}/21781/{TileMatrix}/{TileRow}/{TileCol}.jpeg"/>`
  256x256px
* https://wmts.geo.admin.ch/1.0.0/ch.swisstopo.pixelkarte-farbe/default/current/3857/9/266/180.jpeg

  https://wmts.geo.admin.ch/1.0.0/ch.swisstopo.pixelkarte-farbe/default/current/3857/16/34055/23318.jpeg
  https://wxs.ign.fr/an7nvfzojv5wa96dsga5nk8w/geoportail/wmts?layer=GEOGRAPHICALGRIDSYSTEMS.MAPS.SCAN25TOUR.CV&style=normal&tilematrixset=PM&Service=WMTS&Request=GetTile&Version=1.0.0&Format=image%2Fjpeg&TileMatrix=16&TileCol=34055&TileRow=23318

  https://wmts.geo.admin.ch/1.0.0/ch.swisstopo.pixelkarte-farbe/default/current/3857/14/8510/5825.jpeg
  https://wxs.ign.fr/an7nvfzojv5wa96dsga5nk8w/geoportail/wmts?layer=GEOGRAPHICALGRIDSYSTEMS.MAPS.SCAN25TOUR.CV&style=normal&tilematrixset=PM&Service=WMTS&Request=GetTile&Version=1.0.0&Format=image%2Fjpeg&TileMatrix=14&TileCol=8510&TileRow=5825
  
  https://wmts.geo.admin.ch/1.0.0/ch.swisstopo.pixelkarte-farbe/default/current/3857/16/34064/23307.jpeg
  https://wxs.ign.fr/an7nvfzojv5wa96dsga5nk8w/geoportail/wmts?layer=GEOGRAPHICALGRIDSYSTEMS.MAPS.SCAN25TOUR.CV&style=normal&tilematrixset=PM&Service=WMTS&Request=GetTile&Version=1.0.0&Format=image%2Fjpeg&TileMatrix=16&TileCol=34064&TileRow=23307

# GeoTIFF

https://en.wikipedia.org/wiki/GeoTIFF
https://github.com/KipCrossing/geotiff/blob/main/docs/geotif_spec.md

http://www.libtiff.org

https://github.com/OSGeo/libgeotiff

https://github.com/KipCrossing/geotiff

https://github.com/cgohlke/tifffile/
https://zarr.readthedocs.io/en/stable/

# ...

https://data.geo.admin.ch/ch.swisstopo.landeskarte-farbe-10/swiss-map-raster10_2021_1347-1/swiss-map-raster10_2021_1347-1_krel_0.5_2056.tif

```
swiss-map-raster10_2021_1347-1_krel_0.5_2056.tif 346M
``

```
>tiffinfo -D swiss-map-raster10_2021_1347-1_krel_0.5_2056.tif

TIFFReadDirectory: Warning, Unknown field with tag 33550 (0x830e) encountered.
TIFFReadDirectory: Warning, Unknown field with tag 33922 (0x8482) encountered.
TIFFReadDirectory: Warning, Unknown field with tag 34735 (0x87af) encountered.
TIFFReadDirectory: Warning, Unknown field with tag 34737 (0x87b1) encountered.

TIFF Directory at offset 0xc0 (192)
  Image Width: 17500 Image Length: 12000
  Tile Width: 512 Tile Length: 512
  Resolution: 508, 508 pixels/inch
  Bits/Sample: 8
  Sample Format: unsigned integer
  Compression Scheme: LZW
  Photometric Interpretation: RGB color
  Samples/Pixel: 3
  Planar Configuration: single image plane
  Tag 33550: 0.500000,0.500000,0.000000
  Tag 33922: 0.000000,0.000000,0.000000,2602500.000000,1098000.000000,0.000000
  Tag 34735: 1,1,0,7,1024,0,1,1,1025,0,1,1,1026,34737,15,0,2049,34737,8,15,2054,0,1,9102,3072,0,1,2056,3076,0,1,9001
  Tag 34737: CH1903+ / LV95|CH1903+|
  Predictor: none 1 (0x1)

TIFF Directory at offset 0x272 (626)
  Subfile Type: reduced-resolution image (1 = 0x1)
  Image Width: 8750 Image Length: 6000
  Tile Width: 512 Tile Length: 512
  Bits/Sample: 8
  Sample Format: unsigned integer
  Compression Scheme: LZW
  Photometric Interpretation: RGB color
  Samples/Pixel: 3
  Planar Configuration: single image plane
  Predictor: none 1 (0x1)

TIFF Directory at offset 0x32c (812)
  Subfile Type: reduced-resolution image (1 = 0x1)
  Image Width: 4375 Image Length: 3000
  Tile Width: 512 Tile Length: 512
  Bits/Sample: 8
  Sample Format: unsigned integer
  Compression Scheme: LZW
  Photometric Interpretation: RGB color
  Samples/Pixel: 3
  Planar Configuration: single image plane
  Predictor: none 1 (0x1)

TIFF Directory at offset 0x3e6 (998)
  Subfile Type: reduced-resolution image (1 = 0x1)
  Image Width: 2188 Image Length: 1500
  Tile Width: 512 Tile Length: 512
  Bits/Sample: 8
  Sample Format: unsigned integer
  Compression Scheme: LZW
  Photometric Interpretation: RGB color
  Samples/Pixel: 3
  Planar Configuration: single image plane
  Predictor: none 1 (0x1)

TIFF Directory at offset 0x4a0 (1184)
  Subfile Type: reduced-resolution image (1 = 0x1)
  Image Width: 1094 Image Length: 750
  Tile Width: 512 Tile Length: 512
  Bits/Sample: 8
  Sample Format: unsigned integer
  Compression Scheme: LZW
  Photometric Interpretation: RGB color
  Samples/Pixel: 3
  Planar Configuration: single image plane
  Predictor: none 1 (0x1)

TIFF Directory at offset 0x55a (1370)
  Subfile Type: reduced-resolution image (1 = 0x1)
  Image Width: 547 Image Length: 375
  Tile Width: 512 Tile Length: 512
  Bits/Sample: 8
  Sample Format: unsigned integer
  Compression Scheme: LZW
  Photometric Interpretation: RGB color
  Samples/Pixel: 3
  Planar Configuration: single image plane
  Predictor: none 1 (0x1)

TIFF Directory at offset 0x614 (1556)
  Subfile Type: reduced-resolution image (1 = 0x1)
  Image Width: 274 Image Length: 188
  Tile Width: 512 Tile Length: 512
  Bits/Sample: 8
  Sample Format: unsigned integer
  Compression Scheme: LZW
  Photometric Interpretation: RGB color
  Samples/Pixel: 3
  Planar Configuration: single image plane
  Predictor: none 1 (0x1)
```

```
> listgeo swiss-map-raster10_2021_1347-1_krel_0.5_2056.tif
Geotiff_Information:
   Version: 1
   Key_Revision: 1.0
   Tagged_Information:
      ModelTiepointTag (2,3):
         0                 0                 0
         2602500           1098000           0
      ModelPixelScaleTag (1,3):
         0.5               0.5               0
      End_Of_Tags.
   Keyed_Information:
      GTModelTypeGeoKey (Short,1): ModelTypeProjected
      GTRasterTypeGeoKey (Short,1): RasterPixelIsArea
      GTCitationGeoKey (Ascii,15): "CH1903+ / LV95"
      GeogCitationGeoKey (Ascii,8): "CH1903+"
      GeogAngularUnitsGeoKey (Short,1): Angular_Degree
      ProjectedCSTypeGeoKey (Short,1): Code-2056 (CH1903+ / LV95)
      ProjLinearUnitsGeoKey (Short,1): Linear_Meter
      End_Of_Keys.
   End_Of_Geotiff.

PCS = 2056 (CH1903+ / LV95)
Projection = 19950 (Swiss Oblique Mercator 1995)
Projection Method: CT_HotineObliqueMercatorAzimuthCenter
   ProjCenterLatGeoKey: 46.952406 ( 46d57' 8.66"N)
   ProjCenterLongGeoKey: 7.439583 (  7d26'22.50"E)
   ProjAzimuthAngleGeoKey: 90.000000 ( 90d 0' 0.00"N)
   ProjRectifiedGridAngleGeoKey: 90.000000 ( 90d 0' 0.00"N)
   ProjScaleAtCenterGeoKey: 1.000000
   ProjFalseEastingGeoKey: 2600000.000000 m
   ProjFalseNorthingGeoKey: 1200000.000000 m
GCS: 4150/CH1903+
Datum: 6150/CH1903+
Ellipsoid: 7004/Bessel 1841 (6377397.16,6356078.96)
Prime Meridian: 8901/Greenwich (0.000000/  0d 0' 0.00"E)
Projection Linear Units: 9001/metre (1.000000m)

Corner Coordinates:
Upper Left    ( 2602500.000, 1098000.000)  (  7d28'18.76"E, 46d 2' 5.10"N)
Lower Left    ( 2602500.000, 1092000.000)  (  7d28'18.64"E, 45d58'50.77"N)
Upper Right   ( 2611250.000, 1098000.000)  (  7d35' 5.65"E, 46d 2' 4.78"N)
Lower Right   ( 2611250.000, 1092000.000)  (  7d35' 5.14"E, 45d58'50.45"N)
Center        ( 2606875.000, 1095000.000)  (  7d31'42.05"E, 46d 0'27.83"N)
```

# Lidar

https://www.swisstopo.admin.ch/fr/geodata/height/alti3d.html
swissALTI3D est un modèle altimétrique numérique très précis, qui décrit la surface de la Suisse
sans végétation ni constructions. Il est mis à jour selon un cycle de six ans.

https://www.swisstopo.admin.ch/fr/connaissances-faits/geoinformation/donnees-lidar.html

https://www.swisstopo.admin.ch/fr/geodata/height/surface3d.html

