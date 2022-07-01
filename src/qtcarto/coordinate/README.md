# Coordinate API

# Coordinate Reference Systems

## Geographic

* longitude is the W-E position ranging in [-180 W, 180 E]
* latitude  is the S-N position ranging in [- 90 S,  90 N]

**Convert to sexagecimal**
```
'{0:.5}'.format(degree + minute/60 + second/60**2)
```

### WGS 84 — EPSG:4326 — World Geodetic System 1984, used in GPS 

* https://epsg.io/4326

** EPSG Definition**
* Unit: degree (supplier to define representation)
* Geodetic CRS: WGS 84
* Datum: World Geodetic System 1984
* Ellipsoid: WGS 84
* Prime meridian: Greenwich
* Data source: OGP
* Information source: EPSG. See 3D CRS for original information source.
* Revision date: 2007-08-27
* Scope: Horizontal component of 3D system. Used by the GPS satellite navigation system and for NATO military geodetic surveying.
* Area of use: World.
* Coordinate system: Ellipsoidal 2D CS. Axes: latitude, longitude. Orientations: north, east. UoM: degree
* Center coordinates: 0 0
* WGS84 bounds: (-180.0, -90.0) (180.0, 90.0)
* World

#### WKT Definition

```
GEOGCS["WGS 84",
    DATUM["WGS_1984",
        SPHEROID["WGS 84",6378137,298.257223563,
            AUTHORITY["EPSG","7030"]],
        AUTHORITY["EPSG","6326"]],
    PRIMEM["Greenwich",0,
        AUTHORITY["EPSG","8901"]],
    UNIT["degree",0.0174532925199433,
        AUTHORITY["EPSG","9122"]],
    AUTHORITY["EPSG","4326"]]
```

### Web Mercator / Pseudo Mercator — EPSG:3857

This is projected coordinate system used for rendering maps in Google Maps, OpenStreetMap, etc.

The Web Mercator / Pseudo Mercator projection is a cylindrical map projection. This is a variant of
the regular Mercator projection, except that the computation is done on a sphere, using the
semi-major axis of the ellipsoid.

* http://epsg.io/3857
* https://proj.org/operations/projections/webmerc.html
* https://github.com/OSGeo/PROJ/blob/master/docs/old/libproj.pdf
* https://en.wikipedia.org/wiki/Mercator_projection
* https://en.wikipedia.org/wiki/Web_Mercator_projection
* https://mathworld.wolfram.com/MercatorProjection.html

** EPSG Definition**
* Unit: metre
* Geodetic CRS: WGS 84
* Datum: World Geodetic System 1984
* Ellipsoid: WGS 84
* Prime meridian: Greenwich
* Data source: OGP
* Information source: Microsoft.
* Revision date: 2015-11-25
* Scope: Certain Web mapping and visualisation applications. It is not a recognised geodetic system:
  for that see ellipsoidal Mercator CRS code 3395 (WGS 84 / World Mercator).
* Remarks: Uses spherical development of ellipsoidal coordinates. Relative to WGS 84 / World
  Mercator (CRS code 3395) errors of 0.7 percent in scale and differences in northing of up to 43km
  in the map (equivalent to 21km on the ground) may arise.
* Area of use: World between 85.06°S and 85.06°N.
* Coordinate system: Cartesian 2D CS. Axes: easting, northing (X,Y). Orientations: east, north. UoM: m.
* Center coordinates: 0.00 -0.00
* Projected bounds:
  (-20026376.39, -20048966.10)
  ( 20026376.39,  20048966.10)
  **Note: those bounds looks wrong** `20048966.104014594 = math.log(math.tan(math.pi/4 + math.radians(85.06)/2 )) * 6378137`
* WGS84 bounds: (-180.0, -85.06) (180.0, 85.06)
* World between 85.06°S and 85.06°N.

#### Mathematical definition

Where λ is the longitude in radians and φ is geodetic latitude in radians.

For EPSG:3857, x and y must be scaled by the earth radius.

**Forward Mercator Projection**

\f[
\begin{align}
  x &= \lambda \\
  y &= \ln \left[ \tan \left( \frac{\pi}{4} + \frac{\varphi}{2} \right) \right] = \frac{1}{2} \ln \left( \frac{1 + \sin \varphi}{1 - \sin \varphi} \right)
\end{align}
\f]

**Inverse Mercator projection**

\f[
\begin{align}
  \lambda &= x \\
  \varphi &= 2 \arctan \left( e^{y} \right) - \frac{\pi}{2} = \arctan ( \sinh y )
\end{align}
\f]

**Forward Web Mercator Projection to pixel unit**

\f[
\begin{align}
  x_{px} &= \left\lfloor \frac{256}{2\pi} 2^{\text{zoom level}} (x + \pi) \right\rfloor \\
  y_{px} &= \left\lfloor \frac{256}{2\pi} 2^{\text{zoom level}} \left( \pi - y \right) \right\rfloor
\end{align}
\f]

#### WKT Definition

```
PROJCS["WGS 84 / Pseudo-Mercator",
    GEOGCS["WGS 84",
        DATUM["WGS_1984",
            SPHEROID["WGS 84",6378137,298.257223563,
                AUTHORITY["EPSG","7030"]],
            AUTHORITY["EPSG","6326"]],
        PRIMEM["Greenwich",0,
            AUTHORITY["EPSG","8901"]],
        UNIT["degree",0.0174532925199433,
            AUTHORITY["EPSG","9122"]],
        AUTHORITY["EPSG","4326"]],
    PROJECTION["Mercator_1SP"],
    PARAMETER["central_meridian",0],
    PARAMETER["scale_factor",1],
    PARAMETER["false_easting",0],
    PARAMETER["false_northing",0],
    UNIT["metre",1,
        AUTHORITY["EPSG","9001"]],
    AXIS["X",EAST],
    AXIS["Y",NORTH],
    EXTENSION["PROJ4","+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +wktext  +no_defs"],
    AUTHORITY["EPSG","3857"]]
```

## Coordinates Examples

**France Point Zero** ( Measured on 10 November 2006)
* Paris — Parvis Notre-Dame
* 48° 51′ 12.24845″ N / 2° 20′ 55.62563″ E
* Latitude: 48.85340 Longitude: 2.34878
* Lambert9312: X = 652 215.52 ; Y = 6 861 681.77 ; Z = 35.64 [m]
 
## Glossary

* **CRS** : Coordinate Reference Systems

* **Latitude** (φ) is a geographic coordinate that specifies the north-south position of a point on
 the Earth's surface. Latitude is an angle which ranges from 0° at the Equator to 90° (North or
 South) at the poles. Lines of constant latitude, or parallels, run east-west as circles parallel to
 the equator. The North Pole has a latitude of 90° north (written 90° N or +90°), and the South Pole
 has a latitude of 90° south (written 90° S or −90°).

* **Longitude** (λ) is a geographic coordinate that specifies the east-west position of a point on
  the Earth's surface. Meridians (lines running from the North Pole to the South Pole) connect
  points with the same longitude. By convention, one of these, the Prime Meridian, which passes
  through the Royal Observatory, Greenwich, England, was allocated the position of zero degrees
  longitude. The longitude of other places is measured as the angle east or west from the Prime
  Meridian, ranging from 0° at the Prime Meridian to +180° eastward and −180° westward.

## Web Tools

* https://www.fcc.gov/media/radio/dms-decimal
