/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "path_property.h"
#include "qtcarto.h"

#include <QtDebug>

/**************************************************************************************************/

QcPathProperty::QcPathProperty(QObject * parent)
  : QObject(parent),
    m_length(),
    m_area()
{}

QcPathProperty::QcPathProperty(const QcPathProperty & other, QObject * parent)
  : QObject(parent),
    m_length(other.m_length),
    m_area(other.m_area)
{}

QcPathProperty::~QcPathProperty()
{}

QcPathProperty &
QcPathProperty::operator=(const QcPathProperty & other)
{
  if (this != &other) {
    m_length = other.m_length;
    m_area = other.m_area;
  }

  return *this;
}

void
QcPathProperty::set_length(double length)
{
  if (!qFuzzyCompare(length, m_length)) {
    m_length = length;
    emit length_changed();
  };
}

void
QcPathProperty::set_area(double area)
{
  if (!qFuzzyCompare(area, m_area)) {
    m_area = area;
    emit area_changed();
  }
}

/**************************************************************************************************/

// QC_END_NAMESPACE
