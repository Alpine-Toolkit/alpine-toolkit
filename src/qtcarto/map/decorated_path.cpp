/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "decorated_path.h"
#include "qtcarto.h"

#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QcDecoratedPathDouble::QcDecoratedPathDouble()
  : QcPathDouble(),
    m_attributes()
{}

QcDecoratedPathDouble::QcDecoratedPathDouble(const VertexListType & vertexes, bool closed)
  : QcPathDouble(vertexes, closed)
{
  set_attributes(AttributeType::Normal);
}

/*
QcDecoratedPathDouble::QcDecoratedPathDouble(const QcVectorDouble & coordinates, bool closed)
  : QcPathDouble(coordinates, closed)
{
  set_attributes(AttributeType::Normal);
}
*/

QcDecoratedPathDouble::QcDecoratedPathDouble(const QcDecoratedPathDouble & path)
  : QcPathDouble(path),
    m_attributes(path.m_attributes)
{}

QcDecoratedPathDouble::QcDecoratedPathDouble(const QcPathDouble & path)
  : QcPathDouble(path),
    m_attributes()
{
  set_attributes(AttributeType::Normal);
}

QcDecoratedPathDouble::~QcDecoratedPathDouble()
{}

QcDecoratedPathDouble &
QcDecoratedPathDouble::operator=(const QcDecoratedPathDouble & other)
{
  QcPathDouble::operator=(other);
  m_attributes = other.m_attributes;
  return *this;
}

QcDecoratedPathDouble &
QcDecoratedPathDouble::operator=(const QcPathDouble & other)
{
  QcPathDouble::operator=(other);
  set_attributes(AttributeType::Normal);
  return *this;
}

void
QcDecoratedPathDouble::clear()
{
  QcPathDouble::clear();
  m_attributes.clear();
}

void
QcDecoratedPathDouble::set_attributes(AttributeType value)
{
  m_attributes.clear();
  for (int i = 0; i < number_of_vertexes(); i++)
    m_attributes << value;
}

void
QcDecoratedPathDouble::add_vertex(const VertexType & vertex)
{
  QcPathDouble::add_vertex(vertex);
  m_attributes << AttributeType::Normal;
}

/**************************************************************************************************/

// QC_END_NAMESPACE
