/**************************************************************************************************/

#include "refuge.h"

#include <algorithm>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

/**************************************************************************************************/

Refuge::Refuge(QObject *parent)
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

Refuge::Refuge(const Refuge & other, QObject *parent)
  : QObject(parent),
    m_name(other.m_name),
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

QString
Refuge::name() const
{
  return m_name;
}

void
Refuge::set_name(const QString & name)
{
  m_name = name;
  emit nameChanged();
}

QString
Refuge::short_name() const
{
  return m_short_name;
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
}

int
Refuge::altitude() const
{
  return m_altitude;
}

void
Refuge::set_altitude(int altitude)
{
  m_altitude = altitude;
  emit altitudeChanged();
}

QString
Refuge::description() const
{
  return m_description;
}

void
Refuge::set_description(const QString & description)
{
  m_description = description;
  emit descriptionChanged();
}

QString
Refuge::guardian() const
{
  return m_guardian;
}

void
Refuge::set_guardian(const QString & guardian)
{
  m_guardian = guardian;
  emit guardianChanged();
}

QString
Refuge::picture_path() const
{
  return m_picture_path;
}

void
Refuge::set_picture_path(const QString & picture_path)
{
  m_picture_path = picture_path;
  emit picture_pathChanged();
}

QGeoCoordinate
Refuge::coordinate() const
{
  return m_coordinate;
}

void
Refuge::set_coordinate(const QGeoCoordinate & coordinate)
{
  m_coordinate = coordinate;
  emit coordinateChanged();
}

QString
Refuge::number_of_places() const
{
  return m_number_of_places;
}

void
Refuge::set_number_of_places(const QString & number_of_places)
{
  m_number_of_places = number_of_places;
  emit number_of_placesChanged();
}

QString
Refuge::region() const
{
  return m_region;
}

void
Refuge::set_region(const QString & region)
{
  m_region = region;
  emit regionChanged();
}

QUrl
Refuge::url() const
{
  return m_url;
}

void
Refuge::set_url(const QUrl & url)
{
  m_url = url;
  emit urlChanged();
}

QString
Refuge::phone() const
{
  return m_phone;
}

void
Refuge::set_phone(const QString & phone)
{
  m_phone = phone;
  emit phoneChanged();
}

/**************************************************************************************************/

void
load_refuge_json(const QString & json_path, QList<Refuge *> & refuges)
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
  for(const QJsonValueRef & ref : array) {
    QJsonObject json_refuge = ref.toObject();

    Refuge * refuge = new Refuge();
    refuge->set_name(json_refuge["name"].toString());
    refuge->set_short_name(json_refuge["short_name"].toString());
    refuge->set_altitude(json_refuge["altitude"].toInt());
    refuge->set_description(json_refuge["description"].toString());
    refuge->set_guardian(json_refuge["guardian"].toString());
    refuge->set_picture_path(json_refuge["picture_path"].toString());
    float latitude = json_refuge["latitude"].toDouble();
    float longitude = json_refuge["longitude"].toDouble();
    refuge->set_coordinate(QGeoCoordinate(latitude, longitude));
    refuge->set_number_of_places(json_refuge["number_of_places"].toString());
    refuge->set_region(json_refuge["region"].toString());
    refuge->set_url(json_refuge["url"].toString());
    refuge->set_phone(json_refuge["phone"].toString());

    refuges.append(refuge);
  }

  std::sort(refuges.begin(), refuges.end()); // , qLess<Refuge>()
}

/**************************************************************************************************/

RefugeModel::RefugeModel(QObject * parent)
  : QAbstractListModel(parent),
    m_refuges()
{}

// bool
// RefugeModel::load_json(const QString & json_path)
// {}

int
RefugeModel::rowCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);
  return m_refuges.count();
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

  const Refuge & refuge = m_refuges.at(index.row());
  switch (role) {
  case NameRole:
    return refuge.name();
  default:
    break;
  }

  return QVariant();
}

QHash<int, QByteArray>
RefugeModel::roleNames() const
{
  QHash<int, QByteArray> roleNames;
  roleNames.insert(NameRole, "name");
  roleNames.insert(AltitudeRole, "altitude");
  roleNames.insert(DescriptionRole, "description");
  roleNames.insert(GuardianRole, "guardian");
  roleNames.insert(PicturePathRole, "picture_path");
  roleNames.insert(CoordinateRole, "coordinate");
  roleNames.insert(NumberOfPlacesRole, "number of places");
  roleNames.insert(RegionRole, "region");
  roleNames.insert(UrlRole, "url");
  return roleNames;
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
  return m_refuges.count();
}

void
RefugeModel::clearModel()
{
  beginResetModel();
  m_refuges.clear();
  endResetModel();
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
