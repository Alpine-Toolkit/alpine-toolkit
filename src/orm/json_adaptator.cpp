/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the QtCarto library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $QTCARTO_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "json_adaptator.h"

/**************************************************************************************************/

#include <QByteArray>
#include <QFile>
#include <QtDebug>

/**************************************************************************************************/

void
QcJsonSchemaTraits::load_json(const QString & json_path)
{
  QFile json_file(json_path);

  if (json_file.open(QIODevice::ReadOnly)) {
    qInfo() << "Load" << json_path;
    QByteArray json_data = json_file.readAll();
    QJsonParseError parse_error;
    QJsonDocument json_document = QJsonDocument::fromJson(json_data, &parse_error);
    if (parse_error.error == QJsonParseError::NoError)
      load_json_document(json_document);
    else
      qCritical() << parse_error.errorString();
  } else {
    qCritical() << QStringLiteral("Couldn't open file") << json_path;
    // throw std::invalid_argument("Couldn't open file."); // Fixme: ???
  }
}

void
QcJsonSchemaTraits::to_json(const QString & json_path) // const
{
  QFile json_file(json_path);

  if (json_file.open(QIODevice::WriteOnly)) {
    qInfo() << "Write" << json_path;
    QJsonDocument json_document = to_json_document();
    json_file.write(json_document.toJson());
  } else {
    qCritical() << QStringLiteral("Couldn't open file") << json_path;
    // throw std::invalid_argument("Couldn't open file."); // Fixme: ???
  }
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
