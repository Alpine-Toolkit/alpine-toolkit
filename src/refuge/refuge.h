// -*- mode: c++ -*-

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

#ifndef REFUGE_MODEL_H
#define REFUGE_MODEL_H

/**************************************************************************************************/

#include <QAbstractListModel>
#include <QGeoCoordinate>
#include <QList>
#include <QSet>
#include <QString>
#include <QUrl>
// #include <QtQml/QQmlParserStatus>
#include <QtQml/qqml.h>

/**************************************************************************************************/

class Refuge : public QObject
{
  Q_OBJECT // Q_GADGET ?

  Q_PROPERTY(QString name READ name WRITE set_name NOTIFY nameChanged)
  Q_PROPERTY(QString short_name READ short_name WRITE set_short_name NOTIFY short_nameChanged)
  Q_PROPERTY(QChar first_letter READ first_letter)
  Q_PROPERTY(int altitude READ altitude WRITE set_altitude NOTIFY altitudeChanged)
  Q_PROPERTY(QString description READ description WRITE set_description NOTIFY descriptionChanged)
  Q_PROPERTY(QString guardian READ guardian WRITE set_guardian NOTIFY guardianChanged)
  Q_PROPERTY(QString picture_path READ picture_path WRITE set_picture_path NOTIFY picture_pathChanged)
  Q_PROPERTY(QGeoCoordinate coordinate READ coordinate WRITE set_coordinate NOTIFY coordinateChanged)
  Q_PROPERTY(QString number_of_places READ number_of_places WRITE set_number_of_places NOTIFY number_of_placesChanged)
  Q_PROPERTY(QString region READ region WRITE set_region NOTIFY regionChanged)
  Q_PROPERTY(QUrl url READ url WRITE set_url NOTIFY urlChanged)
  Q_PROPERTY(QString phone READ phone WRITE set_phone NOTIFY phoneChanged)

public:
  explicit Refuge(QObject *parent = nullptr);
  Refuge(const Refuge & refuge, QObject *parent = nullptr);

  Refuge & operator=(const Refuge & other); // not required for QML

  bool operator<(const Refuge & other) const;

  QString name() const;
  void set_name(const QString & name);

  QString short_name() const;
  void set_short_name(const QString & short_name);

  QChar first_letter() const;

  int altitude() const;
  void set_altitude(int altitude);

  QString description() const;
  void set_description(const QString & description);

  QString guardian() const;
  void set_guardian(const QString & guardian);

  QString picture_path() const;
  void set_picture_path(const QString & picture_path);

  QGeoCoordinate coordinate() const;
  void set_coordinate(const QGeoCoordinate & coordinate);

  QString number_of_places() const;
  void set_number_of_places(const QString & number_of_places);

  QString region() const;
  void set_region(const QString & region);

  QUrl url() const;
  void set_url(const QUrl & url);

  QString phone() const;
  void set_phone(const QString & phone);

signals:
  void nameChanged();
  void short_nameChanged();
  void altitudeChanged();
  void descriptionChanged();
  void guardianChanged();
  void picture_pathChanged();
  void coordinateChanged();
  void number_of_placesChanged();
  void regionChanged();
  void urlChanged();
  void phoneChanged();

private:
  QString m_name;
  QString m_short_name;
  int m_altitude;
  QString m_description;
  QString m_guardian;
  QString m_picture_path;
  QGeoCoordinate m_coordinate;
  QString m_number_of_places;
  QString m_region;
  QUrl m_url;
  QString m_phone;
};

/**************************************************************************************************/

class RefugeModel : public QAbstractListModel //, public QQmlParserStatus
{
  Q_OBJECT
  Q_PROPERTY(int entryCount READ entryCount NOTIFY entryCountChanged)
  // Q_INTERFACES(QQmlParserStatus)

public:
  explicit RefugeModel(QObject * parent = 0);

  enum Roles {
    NameRole = Qt::UserRole + 1,
    AltitudeRole,
    DescriptionRole,
    GuardianRole,
    PicturePathRole,
    CoordinateRole,
    NumberOfPlacesRole,
    RegionRole,
    UrlRole,
  };
  Q_ENUMS(Roles)

  // From QAbstractListModel
  int rowCount(const QModelIndex & parent) const;
  QVariant data(const QModelIndex & index, int role) const;
  QHash<int, QByteArray> roleNames() const;

  // From QQmlParserStatus
  // void classBegin() {}
  // void componentComplete();

  int entryCount() const;

  // bool load_json(const QString & json_path);

signals:
  void entryCountChanged();

public slots:
  void clearModel();

private:
  QList<Refuge> m_refuges;
};

/**************************************************************************************************/

void load_refuge_json(const QString & json_path, QList<Refuge *> & refuges);

/**************************************************************************************************/

// Q_DECLARE_TYPEINFO(Refuge, Q_COMPLEX_TYPE); // Q_MOVABLE_TYPE
Q_DECLARE_METATYPE(Refuge)

// QML_DECLARE_TYPE(Refuge) // required ???
QML_DECLARE_TYPE(RefugeModel)

/**************************************************************************************************/

#endif // REFUGE_MODEL_H

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
