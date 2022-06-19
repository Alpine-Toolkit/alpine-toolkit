/***************************************************************************************************
 **
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 **
 ***************************************************************************************************/

/**************************************************************************************************/

#include "camptocamp/camptocamp_search_settings.h"
#include "alpine_toolkit.h"

/**************************************************************************************************/

C2cSearchSettings::C2cSearchSettings()
  : QObject()
  //   m_limit(7),
  //   m_area(false),
  //   m_article(false),
  //   m_book(false),
  //   m_image(false),
  //   m_map(false),
  //   m_outing(false),
  //   m_route(false),
  //   m_userprofile(false),
  //   m_waypoint(false),
  //   m_xreport(false),
  //   m_language(QStringLiteral("fr")),
  //   m_filters()
{
  reset();
}

C2cSearchSettings::C2cSearchSettings(const C2cSearchSettings & other)
  : QObject(),
    m_limit(other.m_limit),
    m_area(other.m_area),
    m_article(other.m_article),
    m_book(other.m_book),
    m_image(other.m_image),
    m_map(other.m_map),
    m_outing(other.m_outing),
    m_route(other.m_route),
    m_userprofile(other.m_userprofile),
    m_waypoint(other.m_waypoint),
    m_xreport(other.m_xreport),
    m_language(other.m_language),
    m_filters()
{}

C2cSearchSettings::~C2cSearchSettings()
{}

void
C2cSearchSettings::reset()
{
  m_limit = 7;
  m_area = false;
  m_article = false;
  m_book = false;
  m_image = false;
  m_map = false;
  m_outing = false;
  m_route = false;
  m_userprofile = false;
  m_waypoint = false;
  m_xreport = false;
  m_language = QStringLiteral("fr");
  m_filters.clear();
}

C2cSearchSettings &
C2cSearchSettings::operator=(const C2cSearchSettings & other)
{
  if (this != &other) {
    m_limit = other.m_limit;
    m_area = other.m_area;
    m_article = other.m_article;
    m_book = other.m_book;
    m_image = other.m_image;
    m_map = other.m_map;
    m_outing = other.m_outing;
    m_route = other.m_route;
    m_userprofile = other.m_userprofile;
    m_waypoint = other.m_waypoint;
    m_xreport = other.m_xreport;
    m_language = other.m_language;
    m_filters = other.m_filters;
  }

  return *this;
}

QString
C2cSearchSettings::type_letters() const
{
  QStringList letters;
  if (m_area)
    letters << QStringLiteral("a");
  if (m_article)
    letters << QStringLiteral("c");
  if (m_book)
    letters << QStringLiteral("b");
  if (m_image)
    letters << QStringLiteral("i");
  if (m_map)
    letters << QStringLiteral("m");
  if (m_outing)
    letters << QStringLiteral("o");
  if (m_route)
    letters << QStringLiteral("r");
  if (m_userprofile)
    letters << QStringLiteral("u");
  if (m_xreport)
    letters << QStringLiteral("x");
  if (m_waypoint)
    letters << QStringLiteral("w");

  return letters.join(',');
}

void
C2cSearchSettings::add_int_filter(const QString & filter_name, int value)
{
  m_filters.insert(filter_name, QVariant(value));
}

void
C2cSearchSettings::add_int_pair_filter(const QString & filter_name, int value_min, int value_max)
{
  QStringList string_list;
  string_list << QString::number(value_min) << QString::number(value_max);
  add_string_list_filter(filter_name, string_list);
}

void
C2cSearchSettings::add_string_filter(const QString & filter_name, const QString & value)
{
  m_filters.insert(filter_name, QVariant(value));
}

void
C2cSearchSettings::add_string_list_filter(const QString & filter_name, const QStringList & value)
{
  m_filters.insert(filter_name, QVariant(value));
}
