// -*- mode: c++ -*-

/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the QtCarto library.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __BLEAUDB_H__
#define __BLEAUDB_H__

/**************************************************************************************************/

#include <QGeoCoordinate>
#include <QHash>
#include <QList>
#include <QObject>
#include <QString>

// #include "map/geo_coordinate.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

// class BleauPlaceCategory : public QString
// {};

// class BleauAlpineGrade : public QString
// {};

// class BleauGrade : public QString
// {};

// class BleauWayNumber : public QString
// {};

// class BleauRefectionNote : public QString
// {};

// class BleauOpeners : public QString
// {};

// class BleauChaosType : public QString
// {};

// class BleauPlaceCategory : public QString
// {};

#define BleauAlpineGrade QString
#define BleauGrade QString
#define BleauWayNumber QString
#define BleauRefectionNote QString
#define BleauOpeners QString
#define BleauChaosType QString
#define BleauPlaceCategory QString

/**************************************************************************************************/

class BleauPlace : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QGeoCoordinate coordinate READ coordinate WRITE set_coordinate NOTIFY coordinateChanged)
  Q_PROPERTY(QString name READ name WRITE set_name NOTIFY nameChanged)
  Q_PROPERTY(BleauPlaceCategory category READ category WRITE set_category NOTIFY categoryChanged)
  Q_PROPERTY(QString note READ note WRITE set_note NOTIFY noteChanged)

public:
  BleauPlace(QObject * parent = 0);
  BleauPlace(const BleauPlace & other, QObject * parent = 0);
  ~BleauPlace();

  BleauPlace & operator=(const BleauPlace & other);

  const QGeoCoordinate & coordinate() const { return m_coordinate; }
  void set_coordinate(const QGeoCoordinate & coordinate);

  const QString & name() const { return m_name; }
  void set_name(const QString & name);

  BleauPlaceCategory category() const { return m_category; }
  void set_category(BleauPlaceCategory category);

  const QString & note() const { return m_note; }
  void set_note(const QString & note);

signals:
  void coordinateChanged();
  void nameChanged();
  void categoryChanged();
  void noteChanged();

private:
  QGeoCoordinate m_coordinate;
  QString m_name;
  BleauPlaceCategory m_category;
  QString m_note;
};

/**************************************************************************************************/

class BleauMassif : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QGeoCoordinate coordinate READ coordinate WRITE set_coordinate NOTIFY coordinateChanged)
  Q_PROPERTY(QString name READ name WRITE set_name NOTIFY nameChanged)
  Q_PROPERTY(QString access READ access WRITE set_access NOTIFY accessChanged)
  Q_PROPERTY(QString alternative_name READ alternative_name WRITE set_alternative_name NOTIFY alternative_nameChanged)
  Q_PROPERTY(BleauChaosType chaos_type READ chaos_type WRITE set_chaos_type NOTIFY chaos_typeChanged)
  Q_PROPERTY(QString note READ note WRITE set_note NOTIFY noteChanged)
  Q_PROPERTY(QString parcelles READ parcelles WRITE set_parcelles NOTIFY parcellesChanged)
  Q_PROPERTY(QString rdv READ rdv WRITE set_rdv NOTIFY rdvChanged)
  Q_PROPERTY(QString secteur READ secteur WRITE set_secteur NOTIFY secteurChanged)
  Q_PROPERTY(QString velo READ velo WRITE set_velo NOTIFY veloChanged)

public:
  BleauMassif(QObject * parent = nullptr);
  BleauMassif(const BleauMassif & other, QObject * parent = nullptr);
  ~BleauMassif();

  BleauMassif & operator=(const BleauMassif & other);

  const QGeoCoordinate & coordinate() const { return m_coordinate; }
  void set_coordinate(const QGeoCoordinate & coordinate);

  const QString & name() const { return m_name; }
  void set_name(const QString & name);

  const QString & access() const { return m_access; }
  void set_access(const QString & access);

  const QString & alternative_name() const { return m_alternative_name; }
  void set_alternative_name(const QString & alternative_name);

  BleauChaosType chaos_type() const { return m_chaos_type; }
  void set_chaos_type(BleauChaosType chaos_type);

  const QString & note() const { return m_note; }
  void set_note(const QString & note);

  const QString & parcelles() const { return m_parcelles; }
  void set_parcelles(const QString & parcelles);

  const QString & rdv() const { return m_rdv; }
  void set_rdv(const QString & rdv);

  const QString & secteur() const { return m_secteur; }
  void set_secteur(const QString & secteur);

  const QString & velo() const { return m_velo; }
  void set_velo(const QString & velo);

signals:
  void coordinateChanged();
  void nameChanged();
  void accessChanged();
  void alternative_nameChanged();
  void chaos_typeChanged();
  void noteChanged();
  void parcellesChanged();
  void rdvChanged();
  void secteurChanged();
  void veloChanged();

private:
  QGeoCoordinate m_coordinate;
  QString m_name;
  QString m_access;
  QString m_alternative_name;
  BleauChaosType m_chaos_type;
  QString m_note;
  QString m_parcelles;
  QString m_rdv;
  QString m_secteur;
  QString m_velo;
};

/**************************************************************************************************/

class BleauBoulder : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QGeoCoordinate coordinate READ coordinate WRITE set_coordinate NOTIFY coordinateChanged)
  Q_PROPERTY(QString name READ name WRITE set_name NOTIFY nameChanged)
  Q_PROPERTY(QString comment READ comment WRITE set_comment NOTIFY commentChanged)
  Q_PROPERTY(BleauGrade grade READ grade WRITE set_grade NOTIFY gradeChanged)
  Q_PROPERTY(BleauWayNumber number READ number WRITE set_number NOTIFY numberChanged)

public:
  BleauBoulder(QObject * parent = nullptr);
  BleauBoulder(const class BleauBoulder & other, QObject * parent = nullptr);
  ~BleauBoulder();

  class BleauBoulder & operator=(const class BleauBoulder & other);

  const QGeoCoordinate & coordinate() const { return m_coordinate; }
  void set_coordinate(const QGeoCoordinate & coordinate);

  const QString & name() const { return m_name; }
  void set_name(const QString & name);

  const QString & comment() const { return m_comment; }
  void set_comment(const QString & comment);

  BleauGrade grade() const { return m_grade; }
  void set_grade(BleauGrade grade);

  BleauWayNumber number() const { return m_number; }
  void set_number(BleauWayNumber number);

signals:
  void coordinateChanged();
  void nameChanged();
  void commentChanged();
  void gradeChanged();
  void numberChanged();

private:
  QGeoCoordinate m_coordinate;
  QString m_name;
  QString m_comment;
  BleauGrade m_grade;
  BleauWayNumber m_number;
};

typedef QList<BleauBoulder> BleauBoulderList;

/**************************************************************************************************/

class BleauCircuit : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QGeoCoordinate coordinate READ coordinate WRITE set_coordinate NOTIFY coordinateChanged)
  // Q_PROPERTY(BleauBoulderList boulders READ boulders WRITE set_boulders NOTIFY bouldersChanged)
  Q_PROPERTY(BleauBoulderList boulders READ boulders)
  Q_PROPERTY(QString colour READ colour WRITE set_colour NOTIFY colourChanged)
  Q_PROPERTY(unsigned int creation_date READ creation_date WRITE set_creation_date NOTIFY creation_dateChanged)
  Q_PROPERTY(QString gestion READ gestion WRITE set_gestion NOTIFY gestionChanged)
  Q_PROPERTY(BleauAlpineGrade grade READ grade WRITE set_grade NOTIFY gradeChanged)
  // Q_PROPERTY(BleauMassif * massif READ massif WRITE set_massif NOTIFY massifChanged)
  Q_PROPERTY(QString note READ note WRITE set_note NOTIFY noteChanged)
  Q_PROPERTY(unsigned int number READ number WRITE set_number NOTIFY numberChanged)
  Q_PROPERTY(BleauOpeners opener READ opener WRITE set_opener NOTIFY openerChanged)
  Q_PROPERTY(unsigned int refection_date READ refection_date WRITE set_refection_date NOTIFY refection_dateChanged)
  Q_PROPERTY(BleauRefectionNote refection_note READ refection_note WRITE set_refection_note NOTIFY refection_noteChanged)
  Q_PROPERTY(QString status READ status WRITE set_status NOTIFY statusChanged)
  Q_PROPERTY(QList<QString> topos READ topos WRITE set_topos NOTIFY toposChanged)

public:
  BleauCircuit(QObject * parent = nullptr);
  BleauCircuit(const class BleauCircuit & other, QObject * parent = nullptr);
  ~BleauCircuit();

  class BleauCircuit & operator=(const class BleauCircuit & other);

  const QGeoCoordinate & coordinate() const { return m_coordinate; }
  void set_coordinate(const QGeoCoordinate & coordinate);

  BleauBoulderList boulders() const { return m_boulders; }
  // void set_boulders(BleauBoulderList boulders);
  void add_boulder(const BleauBoulder & boulder);

  const QString & colour() const { return m_colour; }
  void set_colour(const QString & colour);

  unsigned int creation_date() const { return m_creation_date; }
  void set_creation_date(unsigned int creation_date);

  const QString & gestion() const { return m_gestion; }
  void set_gestion(const QString & gestion);

  BleauAlpineGrade grade() const { return m_grade; }
  void set_grade(BleauAlpineGrade grade);

  const BleauMassif * massif() const { return m_massif; }
  void set_massif(BleauMassif * massif);

  const QString & note() const { return m_note; }
  void set_note(const QString & note);

  unsigned int number() const { return m_number; }
  void set_number(unsigned int number);

  BleauOpeners opener() const { return m_opener; }
  void set_opener(BleauOpeners opener);

  unsigned int refection_date() const { return m_refection_date; }
  void set_refection_date(unsigned int refection_date);

  BleauRefectionNote refection_note() const { return m_refection_note; }
  void set_refection_note(BleauRefectionNote refection_note);

  const QString & status() const { return m_status; }
  void set_status(const QString & status);

  const QList<QString> & topos() const { return m_topos; }
  void set_topos(const QList<QString> & topos);

signals:
  void coordinateChanged();
  void bouldersChanged();
  void colourChanged();
  void creation_dateChanged();
  void gestionChanged();
  void gradeChanged();
  void massifChanged();
  void noteChanged();
  void numberChanged();
  void openerChanged();
  void refection_dateChanged();
  void refection_noteChanged();
  void statusChanged();
  void toposChanged();

private:
  QGeoCoordinate m_coordinate;
  BleauBoulderList m_boulders;
  QString m_colour;
  unsigned int m_creation_date;
  QString m_gestion;
  BleauAlpineGrade m_grade;
  BleauMassif * m_massif;
  QString m_note;
  unsigned int m_number;
  BleauOpeners m_opener;
  unsigned int m_refection_date;
  BleauRefectionNote m_refection_note;
  QString m_status;
  QList<QString> m_topos;
};

/**************************************************************************************************/

class BleauDB : public QObject
{
  Q_OBJECT
  // Q_PROPERTY(BleauPlaceList places READ places WRITE set_places NOTIFY placesChanged)
  // Q_PROPERTY(BleauPlaceList places READ places)
  // Q_PROPERTY(QList<BleauPlace> places READ places WRITE set_places NOTIFY placesChanged)
  // Q_PROPERTY(QList<BleauMassif> massifs READ massifs WRITE set_massifs NOTIFY massifsChanged)
  // Q_PROPERTY(QList<BleauCircuit> circuits READ circuits WRITE set_circuits NOTIFY circuitsChanged)

public:
  BleauDB(QObject * parent = nullptr);
  // BleauDB(const class BleauDB & other, QObject * parent = nullptr);
  ~BleauDB();

  // BleauDB & operator=(const BleauDB & other);

  QHash<QString, BleauPlace> & places() { return m_places; }
  void add_place(const BleauPlace & place);

  QHash<QString, BleauMassif> & massifs() { return m_massifs; }
  void add_massif(const BleauMassif & massif);

  QList<BleauCircuit> & circuits() { return m_circuits; }
  void add_circuit(const BleauCircuit & circuit);

// signals:
//   void placesChanged();
//   void massifsChanged();
//   void circuitsChanged();

private:
  QHash<QString, BleauPlace> m_places;
  QHash<QString, BleauMassif> m_massifs;
  QList<BleauCircuit> m_circuits;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

#endif /* __BLEAUDB_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
