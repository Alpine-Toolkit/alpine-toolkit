/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "json_adaptator.h"
#include "alpine_toolkit.h"

/**************************************************************************************************/

#include <QByteArray>
#include <QFile>
#include <QtDebug>

/**************************************************************************************************/

void
QoJsonSchemaTraits::load_json(const QString & json_path)
{
  QFile json_file(json_path);

  if (json_file.open(QIODevice::ReadOnly)) {
    qATInfo() << "Load" << json_path;
    QByteArray json_data = json_file.readAll();
    QJsonParseError parse_error;
    QJsonDocument json_document = QJsonDocument::fromJson(json_data, &parse_error);
    if (parse_error.error == QJsonParseError::NoError)
      load_json_document(json_document);
    else
      qATCritical() << parse_error.errorString();
  } else {
    qATCritical() << QStringLiteral("Couldn't open file") << json_path;
    // throw std::invalid_argument("Couldn't open file."); // Fixme: ???
  }
}

void
QoJsonSchemaTraits::to_json(const QString & json_path) // const
{
  QFile json_file(json_path);

  if (json_file.open(QIODevice::WriteOnly)) {
    qATInfo() << "Write" << json_path;
    QJsonDocument json_document = to_json_document();
    json_file.write(json_document.toJson());
  } else {
    qATCritical() << QStringLiteral("Couldn't open file") << json_path;
    // throw std::invalid_argument("Couldn't open file."); // Fixme: ???
  }
}
