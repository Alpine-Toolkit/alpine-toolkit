/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
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
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include "projection.h"
#include "qtcarto.h"
#include "config.h" // for PROJ4_DATA_PATH

#include "laea.h"
#include "mercator.h"
#include "wgs84.h"

#include <QtMath>

#include <proj.h>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/*
void
proj4_logger(void * context, int error, const char * message)
{
  qWarning() << context << error << message;
}
*/

class QC_EXPORT QcProjection4
{
 public:
  QcProjection4(const QString & definition);
  ~QcProjection4();

  void transform(const QcProjection4 & proj2, double & x, double & y) const;
  void transform(const QcProjection4 & proj2, double & x, double & y, double & z) const;

 private:
  QString m_definition;
  PJ * m_crs;
};

QcProjection4::QcProjection4(const QString & definition)
  : m_definition(definition)
  , m_crs(nullptr)
{
  // cf. https://trac.osgeo.org/proj/wiki/ThreadSafety

#ifdef ON_ANDROID
    // Set search path so as to find (epsg) date files
    // setenv("PROJ_LIB", proj4_data_path, 1); // must be set before to load the proj4 library
    const char *paths[] = { PROJ4_DATA_PATH };
    // void proj_context_set_search_paths(PJ_CONTEXT * ctx, int count_paths, const char *const * paths)
    proj_context_set_search_paths((PJ_DEFAULT_CTX, 1, paths);
#endif

  // pj_ctx_set_logger(context, proj4_logger);

  qQCInfo() << "Create proj crs for" << definition;
  auto str_definition = definition.toStdString();
  const char * c_definition = str_definition.c_str();
  // PJ * proj_create(PJ_CONTEXT * ctx, const char * definition)
  m_crs = proj_create(PJ_DEFAULT_CTX, c_definition);
  if (!m_crs)
    qWarning() << "Proj crs creation failed for" << definition;
}

QcProjection4::~QcProjection4()
{
  qQCInfo() << m_definition;
  // Fixme: segfault
  // if (m_projection)
  //   pj_free(m_projection);
}

void
QcProjection4::transform(const QcProjection4 & proj2, double & x, double & y) const
{
  double z = .0;
  return transform(proj2, x, y, z);
}

void
QcProjection4::transform(const QcProjection4 & proj2, double & x, double & y, double & z) const
{
  // PJ * proj_create_crs_to_crs_from_pj(PJ_CONTEXT * ctx, PJ * source_crs, PJ * target_crs, PJ_AREA * area, const char * const * options)
  PJ * transformation = proj_create_crs_to_crs_from_pj(PJ_DEFAULT_CTX, m_crs, proj2.m_crs, NULL,NULL);
  if (!transformation) {
    qWarning() << "Proj transformation creation failed";
    return;
  }
  // Fixme: always required ???
  // This will ensure that the order of coordinates for the input CRS will be longitude, latitude,
  //   whereas EPSG:4326 mandates latitude, longitude
  PJ * normalised_transformation = proj_normalize_for_visualization(PJ_DEFAULT_CTX, transformation);
  if (normalised_transformation == NULL) {
    qWarning() << "Failed to normalize transformation object";
    return;
  }
  proj_destroy(transformation);
  transformation = normalised_transformation;

  PJ_COORD coordinate1 = proj_coord(x, y, z, 0);
  PJ_COORD coordinate2 = proj_trans(transformation, PJ_FWD, coordinate1);
  proj_destroy(transformation);

  x = coordinate2.xy.x;
  y = coordinate2.xy.y;
  z = coordinate2.xyz.z;
}

/**************************************************************************************************/

// Fixme: check API

QMap<QString, QcProjection *> QcProjection::m_instances;
QMap<QString, QcProjection4 *> QcProjection::m_projection4_instances;

const QcProjection *
QcProjection::by_srid(const QString & srid)
{
  if (m_instances.isEmpty())
    init();
  if (m_instances.contains(srid))
    return m_instances.value(srid);
  else {
    qWarning() << "SRID not found";
    return nullptr;
  }
}

void
QcProjection::init()
{
  register_projection(new QcWgs84Projection());
  register_projection(new QcWebMercatorProjection());
  register_projection(new QcLaeaProjection_3571());
}

void
QcProjection::register_projection(QcProjection * projection)
{
  const QString & srid = projection->srid();
  if (!m_instances.contains(srid))
    m_instances.insert(srid, projection);
}

/**************************************************************************************************/

QcProjection::QcProjection()
  : m_srid(),
    m_projected_interval(),
    m_preserve_bit(),
    m_projection4()
{}

QcProjection::QcProjection(const QString & srid,
                           const QString & title,
                           const QcVectorDouble & wgs84_origin, // QcWgsCoordinate is not yet defined
                           // const QcVectorDouble & x_axis_orientation,
                           // const QcVectorDouble & y_axis_orientation,
                           const QcInterval2DDouble & wgs84_interval,
                           const QcInterval2DDouble & projected_interval,
                           const QString & unit,
                           ProjectionSurface projection_surface,
                           PreserveBit preserve_bit,
                           bool proj4_support
                           )
  : m_srid(srid),
    m_title(title),
    m_wgs84_origin(wgs84_origin),
    m_wgs84_interval(wgs84_interval),
    m_projected_interval(projected_interval),
    m_unit(unit),
    m_projection_surface(projection_surface),
    m_preserve_bit(preserve_bit),
    m_projection4(nullptr)
{
  if (proj4_support) {
    const QString & definition = proj4_definition();
    // qQCInfo() << definition << m_projection4_instances;
    // if (! m_projection4_instances.contains(definition))
    //   m_projection4_instances.insert(definition, new QcProjection4(definition));
    // m_projection4 = m_projection4_instances.value(definition);
    m_projection4 = new QcProjection4(definition);
  }

  // qQCInfo() << "Build " + srid + " projection";
}

QcProjection::QcProjection(const QcProjection & other)
  : m_srid(other.m_srid),
    m_title(other.m_title),
    m_wgs84_origin(other.m_wgs84_origin),
    m_wgs84_interval(other.m_wgs84_interval),
    m_projected_interval(other.m_projected_interval),
    m_projection_surface(other.m_projection_surface),
    m_preserve_bit(other.m_preserve_bit),
    m_projection4(other.m_projection4)
{}

// Fixme: default
QcProjection &
QcProjection::operator=(const QcProjection & other)
{
  if (this != &other) {
    m_srid = other.m_srid;
    m_title = other.m_title;
    m_wgs84_origin = other.m_wgs84_origin;
    m_wgs84_interval = other.m_wgs84_interval;
    m_projected_interval = other.m_projected_interval;
    m_projection_surface = other.m_projection_surface;
    m_preserve_bit = other.m_preserve_bit;
    m_projection4 = other.m_projection4;
  }

  return *this;
}

bool
QcProjection::operator==(const QcProjection & other) const
{
  return m_srid == other.m_srid; // Fixme: and ...
}

QcGeoCoordinate
QcProjection::coordinate(double x, double y) const
{
  return QcGeoCoordinate(this, x, y);
}

QString
QcProjection::proj4_definition() const
{
  // Fixme: still required since new Proj API ?
  return srid();
}

/**************************************************************************************************/

QcGeoCoordinateTrait::QcGeoCoordinateTrait()
  : m_x(qQNaN()), m_y(qQNaN())
{}

QcGeoCoordinateTrait::QcGeoCoordinateTrait(const QcGeoCoordinateTrait & other)
  : m_x(other.m_x), m_y(other.m_y)
{}

// Fixme: default
QcGeoCoordinateTrait &
QcGeoCoordinateTrait::operator=(const QcGeoCoordinateTrait & other)
{
  if (this != &other) {
    m_x = other.m_x;
    m_y = other.m_y;
  }

  return *this;
}

bool
QcGeoCoordinateTrait::operator==(const QcGeoCoordinateTrait & other) const
{
  bool x_equal = ((qIsNaN(m_x) and qIsNaN(other.m_x))
                  || qFuzzyCompare(m_x, other.m_x));
  bool y_equal = ((qIsNaN(m_y) and qIsNaN(other.m_y))
                  || qFuzzyCompare(m_y, other.m_y));

  return (x_equal and y_equal);
}

bool
QcGeoCoordinateTrait::is_valid() const
{
  return !(qIsNaN(m_x) or qIsNaN(m_y));
}

void
QcGeoCoordinateTrait::transform(const QcProjection & projection_to, double & to_x, double & to_y) const
{
  const QcProjection4 * projection4_from = projection().projection4();
  const QcProjection4 * projection4_to = projection_to.projection4();
  if (projection4_from and projection4_to) {
    double _x = x(); // longitude fro WGS84
    double _y = y(); // latitude
    projection4_from->transform(*projection4_to, _x, _y);
    to_x = _x;
    to_y = _y;
  } else {
    to_x = qQNaN();
    to_y = qQNaN();
  }
}

void
QcGeoCoordinateTrait::transform(QcGeoCoordinateTrait & other) const
{
  double x, y;
  transform(other.projection(), x, y);
  other.set_x(x);
  other.set_y(y);
}

QcVectorDouble
QcGeoCoordinateTrait::transform(const QcProjection & projection_to) const
{
  double x, y;
  transform(projection_to, x, y);
  return {x, y};
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, const QcGeoCoordinateTrait & coordinate)
{
  QDebugStateSaver saver(debug);
  double x = coordinate.x();
  double y = coordinate.y();
  QString class_name = QStringLiteral("QcGeoCoordinate<") + coordinate.projection().srid() + QStringLiteral(">(");

  debug.nospace() << class_name.toStdString().c_str();
  if (qIsNaN(x))
    debug << '?';
  else
    debug << x;
  debug << ", ";
  if (qIsNaN(y))
    debug << '?';
  else
    debug << y;
  debug << ')';

  return debug;
}
#endif

#ifndef QT_NO_DATASTREAM
QDataStream & operator<<(QDataStream & stream, const QcGeoCoordinateTrait & coordinate)
{
  stream << coordinate.x();
  stream << coordinate.y();
  return stream;
}

QDataStream & operator>>(QDataStream & stream, QcGeoCoordinateTrait & coordinate)
{
  double value;
  stream >> value;
  coordinate.set_x(value);
  stream >> value;
  coordinate.set_y(value);
  return stream;
}
#endif

/**************************************************************************************************/

QcGeoCoordinate::QcGeoCoordinate(const QcProjection * projection, double x, double y)
  // Fixme: * or & projection ?
  : QcGeoCoordinateTrait(),
    m_projection(projection)
{
  if (m_projection->is_valid_xy(x, y)) {
    set_x(x);
    set_y(y);
  } else {
    qQCCritical() << "Invalid coordinate" << projection->srid()
                  << static_cast<int>(x) << m_projection->is_valid_x(x)
                  << static_cast<int>(y) << m_projection->is_valid_y(y);
    // Fixme: nan ?
    // throw std::invalid_argument("Invalid coordinate");
  }
}

QcGeoCoordinate::QcGeoCoordinate(const QcProjection * projection, const QcVectorDouble & vector)
  : QcGeoCoordinate(projection, vector.x(), vector.y())
{}

QcGeoCoordinate
QcGeoCoordinate::transform(const QcProjection * projection) const
{
  QcVectorDouble projected = QcGeoCoordinateTrait::transform(*projection);
  return QcGeoCoordinate(projection, projected);
}

/**************************************************************************************************/

// QC_END_NAMESPACE
