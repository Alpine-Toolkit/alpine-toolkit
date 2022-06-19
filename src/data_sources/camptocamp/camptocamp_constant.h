// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __CAMPTOCAMP_CONSTANT_H__
#define __CAMPTOCAMP_CONSTANT_H__

/**************************************************************************************************/

#include <QString>

/**************************************************************************************************/

namespace c2c {
  static const QString OFFICIAL_API_URL = "https://api.camptocamp.org";
  static const QString OFFICIAL_MEDIA_URL = "https://media.camptocamp.org/c2corg_active";

  static const QString ERROR = "error";
  static const QString ERRORS = "errors";
  static const QString MESSAGE = "message";

  static const QString AREAS = "areas";
  static const QString ARTICLES = "articles";
  static const QString BOOKS = "books";
  static const QString HEALTH = "health";
  static const QString IMAGES = "images";
  static const QString MAPS = "maps";
  static const QString OUTINGS = "outings";
  static const QString PROFILES = "profiles"; // ???
  static const QString ROUTES = "routes";
  static const QString USERPROFILES = "userprofiles";
  static const QString WAYPOINTS = "waypoints";
  static const QString XREPORTS = "xreports";

  static const QString DISCOURSE = "discourse";
  static const QString LOGIN = "login";
  static const QString PASSWORD = "password";
  static const QString REMEMBER = "remember";
  static const QString USERNAME = "username";
  static const QString USERS = "users";

  static const QString ACTIVITIES = "activities";
  static const QString ASSOCIATIONS = "associations";
  static const QString DESCRIPTION = "description";
  static const QString DOCUMENT = "document";
  static const QString DOCUMENTS = "documents";
  static const QString DOCUMENT_ID = "document_id";
  static const QString LANG = "lang";
  static const QString LOCALES = "locales";
  static const QString SEARCH = "search";
  static const QString STATUS = "status";
  static const QString TITLE = "title";
  static const QString TYPE = "type";

  static const QString PROTECTED = "protected";
  static const QString QUALITY = "quality";
  static const QString VERSION = "version";

  static const QString AID_RATING = "aid_rating";
  static const QString AVAILABLE_LANGS = "available_langs";
  static const QString CLIMBING_OUTDOOR_TYPE = "climbing_outdoor_type";
  static const QString CONFIGURATION = "configuration";
  static const QString DIFFICULTIES_HEIGHT = "difficulties_height";
  static const QString DURATIONS = "durations";
  static const QString ELEVATION_MAX = "elevation_max";
  static const QString ELEVATION_MIN = "elevation_min";
  static const QString ENGAGEMENT_RATING = "engagement_rating";
  static const QString EQUIPMENT_RATING = "equipment_rating";
  static const QString EXPOSITION_ROCK_RATING = "exposition_rock_rating";
  static const QString GLACIER_GEAR = "glacier_gear";
  static const QString GLOBAL_RATING = "global_rating";
  static const QString HEIGHT_DIFF_ACCESS = "height_diff_access";
  static const QString HEIGHT_DIFF_DIFFICULTIES = "height_diff_difficulties";
  static const QString HEIGHT_DIFF_DOWN = "height_diff_down";
  static const QString HEIGHT_DIFF_UP = "height_diff_up";
  static const QString LIFT_ACCESS = "lift_access";
  static const QString MAIN_WAYPOINT_ID = "main_waypoint_id";
  static const QString ORIENTATIONS = "orientations";
  static const QString RISK_RATING = "risk_rating";
  static const QString ROCK_FREE_RATING = "rock_free_rating";
  static const QString ROCK_REQUIRED_RATING = "rock_required_rating";
  static const QString ROCK_TYPES = "rock_types";
  static const QString ROUTE_TYPES = "route_types";

  static const QString AUTHOR = "author";
  static const QString FILENAME = "filename";

  // static const QString  = "";
};

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_CONSTANT_H__ */
