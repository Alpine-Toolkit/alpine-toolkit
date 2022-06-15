# PROJ

## Release History

## 6.0.0 @ March 2019

A unified database of geodetic objects, coordinate reference systems and their metadata, and
coordinate operations between those CRS is now available in a **SQLite3 database file, proj.db**.

This includes definitions imported from the IOGP EPSG dataset (v9.6.0 release), the IGNF (French
national mapping agency) geodetic registry and the ESRI projection engine database. PROJ is now the
reference software in the “OSGeo C stack” for this CRS and coordinate operation database, whereas
previously this functionality was spread over PROJ, GDAL and libgeotiff, and used CSV or other adhoc
text-based formats.

## Build

* https://proj.org/install.html

**Build requirements**
* C99 compiler
* C++11 compiler
* CMake >= 3.9
* **SQLite3 >= 3.11**: headers and library for target architecture, and sqlite3 executable for build architecture.
* *libtiff >= 4.0 (optional but recommended)*
* *curl >= 7.29.0 (optional but recommended)*

## Resource file

* https://proj.org/resource_files.html
* https://proj.org/apps/projsync.html#projsync

See `/usr/share/proj/` (size on disk 570 MB)

* `proj.db`
  A proj installation includes a SQLite database of transformation information that must be
  accessible for the library to work properly.
  The library will print an error if the database can’t be found.

* `proj.ini`
  proj.ini is a text configuration file, mostly dedicated at setting up network related parameters.

* Transformation grids `*.tif`

## Usage

** https://proj.org/usage/index.html
** https://proj.org/usage/environmentvars.html
** https://proj.org/usage/network.html
