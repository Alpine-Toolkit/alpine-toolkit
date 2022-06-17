# SpatiaLite

SpatiaLite is an open source library intended to extend the SQLite core to support fully fledged Spatial SQL capabilities.

## Reference

* https://www.gaia-gis.it/fossil/libspatialite/index
  current version is 5.0.1 (released on 2021-02-07)
* https://www.gaia-gis.it/gaia-sins/splite-doxy-5.0.1/index.html

## Building

* https://www.gaia-gis.it/gaia-sins/libspatialite-5.0.1.tar.gz

**SpatiaLite depends on the following open source libraries:**

* SQlite3
* PROJ.4
  Spatial Reference System handling [coordinate re-projection]
* GNU ICONV
  locale charset encodings support
* GEOS
  Geometry engine
* FreeXL
  Spreadsheet input support [.xls format]

```
../spatialite.git/configure --disable-freexl --disable-rttopo --disable-minizip

--disable-libxml2
--disable-rttopo --disable-gcp # imply GPLv2+
```

### Configure

```
`configure' configures libspatialite 5.0.1 to adapt to many kinds of systems.

Usage: ../spatialite.git/configure [OPTION]... [VAR=VALUE]...

To assign environment variables (e.g., CC, CFLAGS...), specify them as
VAR=VALUE.  See below for descriptions of some of the useful variables.

Defaults for the options are specified in brackets.

Configuration:
  -h, --help              display this help and exit
      --help=short        display options specific to this package
      --help=recursive    display the short help of all the included packages
  -V, --version           display version information and exit
  -q, --quiet, --silent   do not print `checking ...' messages
      --cache-file=FILE   cache test results in FILE [disabled]
  -C, --config-cache      alias for `--cache-file=config.cache'
  -n, --no-create         do not create output files
      --srcdir=DIR        find the sources in DIR [configure dir or `..']

Installation directories:
  --prefix=PREFIX         install architecture-independent files in PREFIX
                          [/usr/local]
  --exec-prefix=EPREFIX   install architecture-dependent files in EPREFIX
                          [PREFIX]

By default, `make install' will install all the files in
`/usr/local/bin', `/usr/local/lib' etc.  You can specify
an installation prefix other than `/usr/local' using `--prefix',
for instance `--prefix=$HOME'.

For better control, use the options below.

Fine tuning of the installation directories:
  --bindir=DIR            user executables [EPREFIX/bin]
  --sbindir=DIR           system admin executables [EPREFIX/sbin]
  --libexecdir=DIR        program executables [EPREFIX/libexec]
  --sysconfdir=DIR        read-only single-machine data [PREFIX/etc]
  --sharedstatedir=DIR    modifiable architecture-independent data [PREFIX/com]
  --localstatedir=DIR     modifiable single-machine data [PREFIX/var]
  --libdir=DIR            object code libraries [EPREFIX/lib]
  --includedir=DIR        C header files [PREFIX/include]
  --oldincludedir=DIR     C header files for non-gcc [/usr/include]
  --datarootdir=DIR       read-only arch.-independent data root [PREFIX/share]
  --datadir=DIR           read-only architecture-independent data [DATAROOTDIR]
  --infodir=DIR           info documentation [DATAROOTDIR/info]
  --localedir=DIR         locale-dependent data [DATAROOTDIR/locale]
  --mandir=DIR            man documentation [DATAROOTDIR/man]
  --docdir=DIR            documentation root [DATAROOTDIR/doc/libspatialite]
  --htmldir=DIR           html documentation [DOCDIR]
  --dvidir=DIR            dvi documentation [DOCDIR]
  --pdfdir=DIR            pdf documentation [DOCDIR]
  --psdir=DIR             ps documentation [DOCDIR]

Program names:
  --program-prefix=PREFIX            prepend PREFIX to installed program names
  --program-suffix=SUFFIX            append SUFFIX to installed program names
  --program-transform-name=PROGRAM   run sed PROGRAM on installed program names

System types:
  --build=BUILD     configure for building on BUILD [guessed]
  --host=HOST       cross-compile to build programs to run on HOST [BUILD]

Optional Features:
  --disable-option-checking  ignore unrecognized --enable/--with options
  --disable-FEATURE       do not include FEATURE (same as --enable-FEATURE=no)
  --enable-FEATURE[=ARG]  include FEATURE [ARG=yes]
  --enable-silent-rules   less verbose build output (undo: "make V=1")
  --disable-silent-rules  verbose build output (undo: "make V=0")
  --enable-maintainer-mode
                          enable make rules and dependencies not useful (and
                          sometimes confusing) to the casual installer
  --enable-dependency-tracking
                          do not reject slow dependency extractors
  --disable-dependency-tracking
                          speeds up one-time build
  --enable-shared[=PKGS]  build shared libraries [default=yes]
  --enable-static[=PKGS]  build static libraries [default=yes]
  --enable-fast-install[=PKGS]
                          optimize for fast installation [default=yes]
  --disable-libtool-lock  avoid locking (might break parallel builds)
  --enable-mathsql        enables SQL math functions [default=yes]
  --enable-geocallbacks   enables geometry callbacks [default=no]
  --enable-knn            enables KNN support [default=yes]
  --enable-proj           enables PROJ.4 inclusion [default=yes]
  --enable-iconv          enables ICONV inclusion [default=yes]
  --enable-freexl         enables FreeXL inclusion [default=yes]
  --enable-epsg           enables full EPSG dataset support [default=yes]
  --enable-geos           enables GEOS inclusion [default=yes]
  --enable-gcp            enables Control Points (from Grass GIS) [default=yes]
  --enable-geosadvanced   enables GEOS advanced features [default=yes]
  --enable-geosreentrant  enables GEOS reentrant (fully thread safe) [default=yes]
  --enable-geos370        enables GEOS 3.7.0 features [default=yes]
  --enable-rttopo         enables RTTOPO support [default=yes]
  --enable-libxml2        enables libxml2 inclusion [default=yes]
  --enable-minizip        enables MiniZIP inclusion [default=yes]
  --enable-geopackage     enables GeoPackage support [default=yes]
  --enable-gcov           turn on code coverage analysis tools
  --enable-examples       enables building examples [default=yes]
  --enable-module-only    builds only mod_spatialite alone [default=no]

Optional Packages:
  --with-PACKAGE[=ARG]    use PACKAGE [ARG=yes]
  --without-PACKAGE       do not use PACKAGE (same as --with-PACKAGE=no)
  --with-pic              try to use only PIC/non-PIC objects [default=use
                          both]
  --with-gnu-ld           assume the C compiler uses GNU ld [default=no]
  --with-sysroot=DIR Search for dependent libraries within DIR
                        (or the compiler's sysroot if not specified).
  --with-geosconfig=FILE  specify an alternative geos-config file
  --with-geosonlyreentrant
                          completely disables GEOS non-thread safe API
                          [default=no]

Some influential environment variables:
  CC          C compiler command
  CFLAGS      C compiler flags
  LDFLAGS     linker flags, e.g. -L<lib dir> if you have libraries in a
              nonstandard directory <lib dir>
  LIBS        libraries to pass to the linker, e.g. -l<library>
  CPPFLAGS    (Objective) C/C++ preprocessor flags, e.g. -I<include dir> if
              you have headers in a nonstandard directory <include dir>
  CPP         C preprocessor
  CXX         C++ compiler command
  CXXFLAGS    C++ compiler flags
  CXXCPP      C++ preprocessor
  PKG_CONFIG  path to pkg-config utility
  PKG_CONFIG_PATH
              directories to add to pkg-config's search path
  PKG_CONFIG_LIBDIR
              path overriding pkg-config's built-in search path
  LIBXML2_CFLAGS
              C compiler flags for LIBXML2, overriding pkg-config
  LIBXML2_LIBS
              linker flags for LIBXML2, overriding pkg-config

Use these variables to override the choices made by `configure' or to help
it to find libraries and programs with nonstandard names/locations.

Report bugs to <a.furieri@lqt.it>.
```
