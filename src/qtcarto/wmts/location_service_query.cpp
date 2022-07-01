/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "location_service_query.h"
#include "qtcarto.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QcLocationServiceQueryBase::QcLocationServiceQueryBase()
  : m_maximum_responses(),
    m_request_id()
    // m_srs_name()
{}

QcLocationServiceQueryBase::QcLocationServiceQueryBase(const QcLocationServiceQueryBase & other)
  : m_maximum_responses(other.m_maximum_responses),
    m_request_id(other.m_request_id)
    // m_srs_name(other.m_srs_name)
{}

QcLocationServiceQueryBase::~QcLocationServiceQueryBase()
{}

QcLocationServiceQueryBase &
QcLocationServiceQueryBase::operator=(const QcLocationServiceQueryBase & other)
{
  if (this != &other) {
    m_maximum_responses = other.m_maximum_responses;
    m_request_id = other.m_request_id;
    // m_srs_name = other.m_srs_name;
  }

  return *this;
}

/**************************************************************************************************/

QcLocationServiceQuery::QcLocationServiceQuery()
  : QcLocationServiceQueryBase(),
    m_srs_name(),
    m_country_code(),
    m_free_form_address(),
    m_street(),
    m_postale_code(),
    m_place(),
    m_bounding_box()
{}

QcLocationServiceQuery::QcLocationServiceQuery(const QcLocationServiceQuery & other)
  : QcLocationServiceQueryBase(other),
    m_srs_name(other.m_srs_name),
    m_country_code(other.m_country_code),
    m_free_form_address(other.m_free_form_address),
    m_street(other.m_street),
    m_postale_code(other.m_postale_code),
    m_place(other.m_place),
    m_bounding_box(other.m_bounding_box)
{}

QcLocationServiceQuery::~QcLocationServiceQuery()
{}

QcLocationServiceQuery &
QcLocationServiceQuery::operator=(const QcLocationServiceQuery & other)
{
  if (this != &other) {
    QcLocationServiceQueryBase::operator=(other);
    m_country_code = other.m_country_code;
    m_free_form_address = other.m_free_form_address;
    m_place = other.m_place;
    m_postale_code = other.m_postale_code;
    m_srs_name = other.m_srs_name;
    m_street = other.m_street;
    m_bounding_box = other.m_bounding_box;
  }

  return *this;
}

void
QcLocationServiceQuery::set_country_code(const QString & country_code)
{
  m_country_code = country_code;
}

void
QcLocationServiceQuery::set_free_form_address(const QString & free_form_address)
{
  m_free_form_address = free_form_address;
}

void
QcLocationServiceQuery::set_srs_name(const QString & srs_name)
{
  m_srs_name = srs_name;
}

void
QcLocationServiceQuery::set_postale_code(const QString & postale_code)
{
  m_postale_code = postale_code;
}

void
QcLocationServiceQuery::set_street(const QString & street)
{
  m_street = street;
}

void
QcLocationServiceQuery::add_place(const QString & type, const QString & place)
{
  m_place.insert(type, place);
}

void
QcLocationServiceQuery::set_bounding_box(const QcInterval2DDouble & bounding_box)
{
  m_bounding_box = bounding_box;
}

/**************************************************************************************************/

QcLocationServiceReverseQuery::QcLocationServiceReverseQuery()
  : QcLocationServiceQueryBase(),
    m_coordinate(),
    m_radius(.0)
{}

QcLocationServiceReverseQuery::QcLocationServiceReverseQuery(const QcLocationServiceReverseQuery & other)
  : QcLocationServiceQueryBase(other),
    m_coordinate(other.m_coordinate),
    m_radius(other.m_radius)
{}

QcLocationServiceReverseQuery::~QcLocationServiceReverseQuery()
{}

QcLocationServiceReverseQuery &
QcLocationServiceReverseQuery::operator=(const QcLocationServiceReverseQuery & other)
{
  if (this != &other) {
    QcLocationServiceQueryBase::operator=(other);
    m_coordinate = other.m_coordinate;
    m_radius = other.m_radius;
  }

  return *this;
}

void
QcLocationServiceReverseQuery::set_coordinate(const QcWgsCoordinate & coordinate)
{
  m_coordinate = coordinate;
}

void
QcLocationServiceReverseQuery::set_radius(int radius)
{
  m_radius = radius;
}

/**************************************************************************************************/

// QC_END_NAMESPACE
