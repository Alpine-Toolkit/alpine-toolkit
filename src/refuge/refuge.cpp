/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire.
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

#include "refuge.h"

#include <algorithm>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

/**************************************************************************************************/

Refuge::Refuge(QObject * parent)
  : QObject(parent),
    m_name(),
    m_altitude(0),
    m_description(),
    m_guardian(),
    m_picture_path(),
    m_coordinate(),
    m_number_of_places(),
    m_region(),
    m_url(),
    m_phone()
{
}

Refuge::Refuge(const Refuge & other, QObject * parent)
  : QObject(parent),
    m_name(other.m_name),
    m_short_name(other.m_short_name),
    m_altitude(other.m_altitude),
    m_description(other.m_description),
    m_guardian(other.m_guardian),
    m_picture_path(other.m_picture_path),
    m_coordinate(other.m_coordinate),
    m_number_of_places(other.m_number_of_places),
    m_region(other.m_region),
    m_url(other.m_url),
    m_phone(other.m_phone)
{}

// Fixme: default
Refuge &
Refuge::operator=(const Refuge & other)
{
  if (this != &other) {
    // QObject::operator=(other); // ???
    m_name = other.m_name;
    m_short_name = other.m_short_name;
    m_altitude = other.m_altitude;
    m_description = other.m_description;
    m_guardian = other.m_guardian;
    m_picture_path = other.m_picture_path;
    m_coordinate = other.m_coordinate;
    m_number_of_places = other.m_number_of_places;
    m_region = other.m_region;
    m_url = other.m_url;
    m_phone = other.m_phone;
  }

  return *this;
}

bool
Refuge::operator<(const Refuge & other) const
{
  return m_short_name < other.m_short_name;
}

void
Refuge::set_name(const QString & name)
{
  m_name = name;
  emit nameChanged();
}

void
Refuge::set_short_name(const QString & short_name)
{
  m_short_name = short_name;
  emit short_nameChanged();
}

QChar
Refuge::first_letter() const
{
  return m_short_name.normalized(QString::NormalizationForm_D)[0].toUpper();
  // return m_short_name[0].toUpper();
}

void
Refuge::set_altitude(int altitude)
{
  m_altitude = altitude;
  emit altitudeChanged();
}

void
Refuge::set_description(const QString & description)
{
  m_description = description;
  emit descriptionChanged();
}

void
Refuge::set_guardian(const QString & guardian)
{
  m_guardian = guardian;
  emit guardianChanged();
}

void
Refuge::set_picture_path(const QString & picture_path)
{
  m_picture_path = picture_path;
  emit picture_pathChanged();
}

void
Refuge::set_coordinate(const QGeoCoordinate & coordinate)
{
  m_coordinate = coordinate;
  emit coordinateChanged();
}

void
Refuge::set_number_of_places(const QString & number_of_places)
{
  m_number_of_places = number_of_places;
  emit number_of_placesChanged();
}

void
Refuge::set_region(const QString & region)
{
  m_region = region;
  emit regionChanged();
}

void
Refuge::set_url(const QUrl & url)
{
  m_url = url;
  emit urlChanged();
}

void
Refuge::set_phone(const QString & phone)
{
  m_phone = phone;
  emit phoneChanged();
}

/**************************************************************************************************/

void
load_refuge_json(const QString & json_path, QList<Refuge> & refuges)
{
  QFile json_file(json_path);

  if (!json_file.exists()) {
    qWarning() << "JSON file does not exist";
  }
  if (!json_file.open(QIODevice::ReadOnly)) {
    qWarning("Couldn't open json file.");
  }

  QByteArray byte_array = json_file.readAll();
  QJsonDocument json_document(QJsonDocument::fromJson(byte_array));

  QJsonArray array = json_document.array();
  // refuges.reserve(array.size());
  for(const QJsonValueRef & ref : array) {
    QJsonObject json_refuge = ref.toObject();

    Refuge refuge;
    refuge.set_name(json_refuge["name"].toString());
    refuge.set_short_name(json_refuge["short_name"].toString());
    refuge.set_altitude(json_refuge["altitude"].toInt());
    refuge.set_description(json_refuge["description"].toString());
    refuge.set_guardian(json_refuge["guardian"].toString());
    refuge.set_picture_path(json_refuge["picture_path"].toString());
    float latitude = json_refuge["latitude"].toDouble();
    float longitude = json_refuge["longitude"].toDouble();
    refuge.set_coordinate(QGeoCoordinate(latitude, longitude));
    refuge.set_number_of_places(json_refuge["number_of_places"].toString());
    refuge.set_region(json_refuge["region"].toString());
    refuge.set_url(json_refuge["url"].toString());
    refuge.set_phone(json_refuge["phone"].toString());

    // QVector init in place ???
    refuges.append(refuge);
  }

  // std::sort(refuges.begin(), refuges.end()); // , qLess<Refuge *>()
}

/**************************************************************************************************/

// RefugeModel::RefugeModel()
//   : QAbstractListModel(nullptr),
//     m_refuges()
// {}

RefugeModel::RefugeModel(const QList<Refuge> & refuges, QObject * parent)
  : QAbstractListModel(parent),
    m_refuges(refuges)
{}

int
RefugeModel::rowCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);
  return m_refuges.size();
}

QVariant
RefugeModel::data(const QModelIndex & index, int role) const
{
  // qInfo() << index << role;

  if (!index.isValid() || index.row() < 0)
    return QVariant();

  if (index.row() >= m_refuges.count()) {
    qWarning() << "RefugeModel: Index out of bound";
    return QVariant();
  }

  const Refuge & refuge = m_refuges[index.row()];
  switch (role) {
  case NameRole:
    return refuge.name();
  case ShortNameRole:
    return refuge.short_name();
  case FirstLetterRole:
    return refuge.first_letter();
  case AltitudeRole:
    return refuge.altitude();
  case DescriptionRole:
    return refuge.description();
  case GuardianRole:
    return refuge.guardian();
  case PicturePathRole:
    return refuge.picture_path();
  case CoordinateRole:
    return QVariant(); // refuge.coordinate()
  case NumberOfPlacesRole:
    return refuge.number_of_places();
  case RegionRole:
    return refuge.region();
  case UrlRole:
    return refuge.url();
  case PhoneRole:
    return refuge.phone();
  default:
    break;
  }

  return QVariant();
}

QHash<int, QByteArray>
RefugeModel::roleNames() const
{
  QHash<int, QByteArray> role_names;
  role_names[NameRole] = "name";
  role_names[ShortNameRole] = "short_name";
  role_names[FirstLetterRole] = "first_letter";
  role_names[AltitudeRole] = "altitude";
  role_names[DescriptionRole] = "description";
  role_names[GuardianRole] = "guardian";
  role_names[PicturePathRole] = "picture_path";
  role_names[CoordinateRole] = "coordinate";
  role_names[NumberOfPlacesRole] = "number_of_places";
  role_names[RegionRole] = "region";
  role_names[UrlRole] = "url";
  role_names[PhoneRole] = "phone";
  return role_names;
}

/*
void
RefugeModel::componentComplete()
{
  m_componentCompleted = true;
}
*/

int
RefugeModel::entryCount() const
{
  return m_refuges.size();
}

void
RefugeModel::clearModel()
{
  beginResetModel();
  m_refuges.clear();
  endResetModel();
}

// Refuge &
// RefugeModel::at(int index)
// {
//   return m_refuges[index];
// }

// Refuge &
// RefugeModel::operator[](int index)
// {
//   return at(index);
// }

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
