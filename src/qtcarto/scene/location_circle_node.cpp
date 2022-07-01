/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "location_circle_node.h"
#include "qtcarto.h"

#include <QColor>
#include <QSGMaterial>
#include <QSGMaterialShader>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/// The QcLocationCircleMaterialShader holds shader to paint location circle.
class LocationCircleMaterialShader : public QSGMaterialShader
{
public:
  LocationCircleMaterialShader() {
    setShaderFileName(VertexStage,   QLatin1String(":/scene/shaders/location_circle.vert.qsb"));
    setShaderFileName(FragmentStage, QLatin1String(":/scene/shaders/location_circle.frag.qsb"));
  }

  bool updateUniformData(RenderState & state, QSGMaterial * new_material, QSGMaterial * old_material) override;
};

/**************************************************************************************************/

class LocationCircleMaterial : public QSGMaterial
{
public:
  LocationCircleMaterial() {
    setFlag(Blending);
  }

  QSGMaterialType *type() const override {
    static QSGMaterialType type;
    return &type;
  }

  QSGMaterialShader *createShader(QSGRendererInterface::RenderMode) const override {
    return new LocationCircleMaterialShader;
  }

  int compare(const QSGMaterial *material) const override {
    auto other = static_cast<const LocationCircleMaterial *>(material);

    // if diff is non-zero
    if (int diff = int(state.cone_color.rgb()) - int(other->state.cone_color.rgb()))
      return diff;

    if (int diff = int(state.accuracy_color.rgb()) - int(other->state.accuracy_color.rgb()))
      return diff;

    return 0; // equal
  }

  // Shader state
  struct {
    QColor cone_color;
    QColor accuracy_color;
  } state;
};

/**************************************************************************************************/

bool
LocationCircleMaterialShader::updateUniformData(RenderState & state, QSGMaterial * new_material, QSGMaterial * old_material)
{
  qQCDebug();

  // layout(std140, binding = 0) uniform buf {
  //   highp mat4 qt_Matrix;       // 4*4*4 = 64
  //   lowp float qt_Opacity;      //     4      @68
  //   lowp vec4 cone_colour;      //   4*4 = 16 @ 4
  //   lowp vec4 accuracy_colour;  //   4*4 = 16 @
  // };

  constexpr qsizetype stride_opacity = 4;
  constexpr qsizetype stride_color = 4*4;
  constexpr qsizetype stride_matrix = 4*4*4;
  constexpr qsizetype stride_uniform = stride_matrix + stride_opacity + 2*stride_color; // 112

  bool changed = false;

  QByteArray * buffer = state.uniformData();
  auto buffer_ptr = buffer->data();
  // qQCDebug() << "buffer size" << buffer->size();
  Q_ASSERT(buffer->size() >= stride_uniform);

  if (state.isMatrixDirty()) {
    const QMatrix4x4 matrice = state.combinedMatrix();
    memcpy(buffer_ptr, matrice.constData(), stride_matrix);
  }

  size_t stride_offset = stride_matrix;
  if (state.isOpacityDirty()) {
    const float opacity = state.opacity();
    memcpy(buffer_ptr + stride_offset, &opacity, stride_opacity);
  }

  auto material = static_cast<LocationCircleMaterial *>(new_material);

  stride_offset += stride_opacity;
  float c[4];
  material->state.cone_color.getRgbF(&c[0], &c[1], &c[2], &c[3]);
  memcpy(buffer_ptr + stride_offset, c, stride_color);

  stride_offset += stride_color;
  material->state.accuracy_color.getRgbF(&c[0], &c[1], &c[2], &c[3]);
  memcpy(buffer_ptr + stride_offset, c, stride_color);

  // Fixme: qt6
  return true;
}

/**************************************************************************************************/

struct LocationCircleVertex {
  float x;
  float y;
  float u;
  float v;
  float cone_radius;
  float dot_radius;
  float accuracy_radius;
  float angle;
  // float r;
  // float g;
  // float b;
  // float a;

  inline void set(const QcVectorDouble & point,
                  const QcVectorDouble & uv,
                  float _cone_radius,
                  float _dot_radius,
                  float _accuracy_radius,
                  float _angle
                  ) {
    x = point.x();
    y = point.y();
    u = uv.x();
    v = uv.y();
    cone_radius = _cone_radius;
    dot_radius = _dot_radius;
    accuracy_radius = _accuracy_radius;
    angle = _angle;
    // r;
    // g;
    // b;
    // a;
  }
};

/**************************************************************************************************/

static const
QSGGeometry::AttributeSet & attributes()
{
  static QSGGeometry::Attribute attr[] = {
    // layout(location = 0) in highp vec4 a_vertex;
    QSGGeometry::Attribute::create(0, 2, QSGGeometry::FloatType, true),  // xy
    // layout(location = 1) in highp vec2 a_tex_coord;
    QSGGeometry::Attribute::create(1, 2, QSGGeometry::FloatType, false), // uv
    // layout(location = 2) in highp vec3 a_radius;
    QSGGeometry::Attribute::create(2, 3, QSGGeometry::FloatType, false), // radius
    // layout(location = 3) in highp float a_angle;
    QSGGeometry::Attribute::create(3, 1, QSGGeometry::FloatType, false)  // angle
    // QSGGeometry::Attribute::create(5, 4, QSGGeometry::FloatType, false)  // color
  };

  static QSGGeometry::AttributeSet set = {
    4, // count
    sizeof(LocationCircleVertex), // stride
    attr
  };

  return set;
}

/**************************************************************************************************/

QcLocationCircleNode::QcLocationCircleNode(const QcViewport * viewport)
  : QSGOpacityNode(),
    m_viewport(viewport),
    m_geometry_node(new QSGGeometryNode())
{
  qQCDebug();

  setOpacity(.25); // 1. black

  QSGGeometry * geometry = new QSGGeometry(attributes(), 0);
  geometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
  m_geometry_node->setGeometry(geometry);
  m_geometry_node->setFlag(QSGNode::OwnsGeometry);

  auto material = new LocationCircleMaterial;
  material->state.cone_color = QColor(0, 0, 255, 255);
  material->state.accuracy_color = QColor(255, 0, 0, 255);
  m_geometry_node->setMaterial(material);
  m_geometry_node->setFlag(QSGNode::OwnsMaterial);

  appendChildNode(m_geometry_node);
}

void
QcLocationCircleNode::update(const QcLocationCircleData & location_circle_data)
{
  qQCDebug();

  // Fixme: redo...
  //   m_geometry.allocate(4);
  QSGGeometry * geometry = new QSGGeometry(attributes(), 4);
  geometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
  m_geometry_node->setGeometry(geometry);
  m_geometry_node->setFlag(QSGNode::OwnsGeometry);

  auto vertices = static_cast<LocationCircleVertex *>(geometry->vertexData());
  float x, y;
  if (location_circle_data.visible()) {
    QcVectorDouble screen_coordinate = m_viewport->coordinate_to_screen(location_circle_data.coordinate());
    x = screen_coordinate.x();
    y = screen_coordinate.y();
    qQCDebug() << screen_coordinate;
  } else {
    x = .5 * m_viewport->width(); // Fixme: vector
    y = .5 * m_viewport->height();
  }
  float accuracy_radius = m_viewport->to_px(location_circle_data.horizontal_precision());
  constexpr float dot_radius_minimum = 10.;
  constexpr float cone_scale_factor = 5.;
  float dot_radius = qMax(accuracy_radius, dot_radius_minimum);
  float radius = cone_scale_factor * dot_radius_minimum;
  float margin = 10;
  float size = radius + margin;
  float angle = location_circle_data.bearing() + 90.; // North point to y
  vertices[0].set(QcVectorDouble(x - size, y - size), QcVectorDouble(-size, -size), radius, dot_radius, accuracy_radius, angle);
  vertices[1].set(QcVectorDouble(x - size, y + size), QcVectorDouble(-size,  size), radius, dot_radius, accuracy_radius, angle);
  vertices[2].set(QcVectorDouble(x + size, y - size), QcVectorDouble( size, -size), radius, dot_radius, accuracy_radius, angle);
  vertices[3].set(QcVectorDouble(x + size, y + size), QcVectorDouble( size,  size), radius, dot_radius, accuracy_radius, angle);

  markDirty(QSGNode::DirtyGeometry);
}

/**************************************************************************************************/

// QC_END_NAMESPACE

