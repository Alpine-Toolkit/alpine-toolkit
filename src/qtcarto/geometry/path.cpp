/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "path.h"
#include "qtcarto.h"

#include "polygon_seidler_triangulation.h"

/**************************************************************************************************/

template<>
QcPathDouble::QcPath(const QVector<double> & coordinates, bool closed)
  : m_vertexes(),
    m_edges(),
    m_interval(),
    m_closed(closed)
{
  int number_of_coordinates = coordinates.size();
  int dimension = QcVectorDouble::dimension();
  if (number_of_coordinates % dimension == 1) {
    // throw std::invalid_argument("Odd number of coordinates");
    qQCCritical() << QLatin1String("Odd number of coordinates");
    return;
  }

  for (int i = 0; i < number_of_coordinates; i += dimension)
    add_vertex(VertexType(coordinates[i], coordinates[i+1]));
}

template<>
QcPath3DDouble::QcPath(const QVector<double> & coordinates, bool closed)
  : m_vertexes(),
    m_edges(),
    m_interval(),
    m_closed(closed)
{
  int number_of_coordinates = coordinates.size();
  int dimension = QcVector3DDouble::dimension();
  if (number_of_coordinates % dimension == 1) {
    // throw std::invalid_argument("Odd number of coordinates");
    qQCCritical() << QLatin1String("Odd number of coordinates");
    return;
  }

  for (int i = 0; i < number_of_coordinates; i += dimension)
    add_vertex(VertexType(coordinates[i], coordinates[i+1], coordinates[i+2]));
}

/*
QcPolygonTriangulation
QcPath::triangulate() const
{
  return QcPolygonTriangulation(*this);
}
*/

/**************************************************************************************************/

QcTriangleVertex::QcTriangleVertex()
  : p1(), p2(), p3()
{}

QcTriangleVertex::QcTriangleVertex(const QcVectorDouble & p1,
                                   const QcVectorDouble & p2,
                                   const QcVectorDouble & p3)
  : p1(p1), p2(p2), p3(p3)
{}

QcTriangleVertex::QcTriangleVertex(const QcTriangleVertex & other)
  : p1(other.p1),
    p2(other.p2),
    p3(other.p3)
{}

QcTriangleVertex::~QcTriangleVertex()
{}

QcTriangleVertex &
QcTriangleVertex::operator=(const QcTriangleVertex & other)
{
  if (this != &other) {
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
  }

  return *this;
}

QcPolygonTriangulation::QcPolygonTriangulation(const QcPathDouble & path)
  : m_path(path)
{
  int number_of_vertexes = path.number_of_vertexes();
  int number_of_segments = number_of_vertexes -2; // Fixme: true ?

  double vertexes[number_of_vertexes][2];
  int i = 0;
  for (const auto & vertex : path.vertexes()) {
    qQCInfo() << vertex;
    vertexes[i][0] = vertex.x();
    vertexes[i][1] = vertex.y();
    i++;
  }

  int triangles[number_of_segments][3];
  for (int i = 0; i < number_of_segments; i++) {
    for (int j = 0; j < 3; j++)
      triangles[i][j] = 0;
  }

  QcSeidlerPolygonTriangulation triangulation(number_of_vertexes, vertexes, triangles);

  for (int i = 0; i < number_of_segments; i++) {
    qQCInfo() << triangles[i][0] << triangles[i][1] << triangles[i][2];
    m_triangles << QcTriangleIndex(triangles[i][0] -1,
                                   triangles[i][1] -1,
                                   triangles[i][2] -1);
  }
}

QList<QcTriangleVertex>
QcPolygonTriangulation::triangle_vertexes() const
{
  QList<QcTriangleVertex> triangle_vertexes;
  for (const auto & triangle: m_triangles) {
    qQCInfo() << triangle.p1 << triangle.p2 << triangle.p3;
    qQCInfo() << m_path.vertex_at(triangle.p1);
    qQCInfo() << m_path.vertex_at(triangle.p2);
    qQCInfo() << m_path.vertex_at(triangle.p3);
    triangle_vertexes << QcTriangleVertex(m_path.vertex_at(triangle.p1),
                                          m_path.vertex_at(triangle.p2),
                                          m_path.vertex_at(triangle.p3));
  }
  return triangle_vertexes;
}
