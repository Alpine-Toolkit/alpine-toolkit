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

#include "bleaudb.h"

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

BleauPlace::BleauPlace(QObject * parent)
  : QObject(parent),
    m_coordinate(),
    m_name(),
    m_category(),
    m_note()
{}

BleauPlace::BleauPlace(const BleauPlace & other, QObject * parent)
  : QObject(parent),
    m_coordinate(other.m_coordinate),
    m_name(other.m_name),
    m_category(other.m_category),
    m_note(other.m_note)
{}

BleauPlace::~BleauPlace()
{}

BleauPlace &
BleauPlace::operator=(const BleauPlace & other)
{
  if (this != &other) {
    m_coordinate = other.m_coordinate;
    m_name = other.m_name;
    m_category = other.m_category;
    m_note = other.m_note;
  }

  return *this;
}

void
BleauPlace::set_coordinate(const QGeoCoordinate & coordinate)
{
  m_coordinate = coordinate;
  emit coordinateChanged();
}

void
BleauPlace::set_name(const QString & name)
{
  m_name = name;
  emit nameChanged();
}

void
BleauPlace::set_category(BleauPlaceCategory category)
{
  m_category = category;
  emit categoryChanged();
}

void
BleauPlace::set_note(const QString & note)
{
  m_note = note;
  emit noteChanged();
}

/**************************************************************************************************/

BleauMassif::BleauMassif(QObject * parent)
  : QObject(parent),
    m_coordinate(),
    m_name(),
    m_access(),
    m_alternative_name(),
    m_chaos_type(),
    m_note(),
    m_parcelles(),
    m_rdv(),
    m_secteur(),
    m_velo()
{}

BleauMassif::BleauMassif(const BleauMassif & other, QObject * parent)
  : QObject(parent),
    m_coordinate(other.m_coordinate),
    m_name(other.m_name),
    m_access(other.m_access),
    m_alternative_name(other.m_alternative_name),
    m_chaos_type(other.m_chaos_type),
    m_note(other.m_note),
    m_parcelles(other.m_parcelles),
    m_rdv(other.m_rdv),
    m_secteur(other.m_secteur),
    m_velo(other.m_velo)
{}

BleauMassif::~BleauMassif()
{}

BleauMassif &
BleauMassif::operator=(const BleauMassif & other)
{
  if (this != &other) {
    m_coordinate = other.m_coordinate;
    m_name = other.m_name;
    m_access = other.m_access;
    m_alternative_name = other.m_alternative_name;
    m_chaos_type = other.m_chaos_type;
    m_note = other.m_note;
    m_parcelles = other.m_parcelles;
    m_rdv = other.m_rdv;
    m_secteur = other.m_secteur;
    m_velo = other.m_velo;
  }

  return *this;
}

void
BleauMassif::set_coordinate(const QGeoCoordinate & coordinate)
{
  m_coordinate = coordinate;
  emit coordinateChanged();
}

void
BleauMassif::set_name(const QString & name)
{
  m_name = name;
  emit nameChanged();
}

void
BleauMassif::set_access(const QString & access)
{
  m_access = access;
  emit accessChanged();
}

void
BleauMassif::set_alternative_name(const QString & alternative_name)
{
  m_alternative_name = alternative_name;
  emit alternative_nameChanged();
}

void
BleauMassif::set_chaos_type(BleauChaosType chaos_type)
{
  m_chaos_type = chaos_type;
  emit chaos_typeChanged();
}

void
BleauMassif::set_note(const QString & note)
{
  m_note = note;
  emit noteChanged();
}

void
BleauMassif::set_parcelles(const QString & parcelles)
{
  m_parcelles = parcelles;
  emit parcellesChanged();
}

void
BleauMassif::set_rdv(const QString & rdv)
{
  m_rdv = rdv;
  emit rdvChanged();
}

void
BleauMassif::set_secteur(const QString & secteur)
{
  m_secteur = secteur;
  emit secteurChanged();
}

void
BleauMassif::set_velo(const QString & velo)
{
  m_velo = velo;
  emit veloChanged();
}

/**************************************************************************************************/

BleauBoulder::BleauBoulder(QObject * parent)
  : QObject(parent),
    m_coordinate(),
    m_name(),
    m_comment(),
    m_grade(),
    m_number()
{}

BleauBoulder::BleauBoulder(const BleauBoulder & other, QObject * parent)
  : QObject(parent),
    m_coordinate(other.m_coordinate),
    m_name(other.m_name),
    m_comment(other.m_comment),
    m_grade(other.m_grade),
    m_number(other.m_number)
{}

BleauBoulder::~BleauBoulder()
{}

BleauBoulder &
BleauBoulder::operator=(const BleauBoulder & other)
{
  if (this != &other) {
    m_coordinate = other.m_coordinate;
    m_name = other.m_name;
    m_comment = other.m_comment;
    m_grade = other.m_grade;
    m_number = other.m_number;
  }

  return *this;
}

void
BleauBoulder::set_coordinate(const QGeoCoordinate & coordinate)
{
  m_coordinate = coordinate;
  emit coordinateChanged();
}

void
BleauBoulder::set_name(const QString & name)
{
  m_name = name;
  emit nameChanged();
}

void
BleauBoulder::set_comment(const QString & comment)
{
  m_comment = comment;
  emit commentChanged();
}

void
BleauBoulder::set_grade(BleauGrade grade)
{
  m_grade = grade;
  emit gradeChanged();
}

void
BleauBoulder::set_number(BleauWayNumber number)
{
  m_number = number;
  emit numberChanged();
}

/**************************************************************************************************/

BleauCircuit::BleauCircuit(QObject * parent)
  : QObject(parent),
    m_coordinate(),
    m_boulders(),
    m_colour(),
    m_creation_date(),
    m_gestion(),
    m_grade(),
    m_massif(nullptr),
    m_note(),
    m_number(),
    m_opener(),
    m_refection_date(),
    m_refection_note(),
    m_status(),
    m_topos()
{}

BleauCircuit::BleauCircuit(const BleauCircuit & other, QObject * parent)
  : QObject(parent),
    m_coordinate(other.m_coordinate),
    m_boulders(other.m_boulders),
    m_colour(other.m_colour),
    m_creation_date(other.m_creation_date),
    m_gestion(other.m_gestion),
    m_grade(other.m_grade),
    m_massif(other.m_massif),
    m_note(other.m_note),
    m_number(other.m_number),
    m_opener(other.m_opener),
    m_refection_date(other.m_refection_date),
    m_refection_note(other.m_refection_note),
    m_status(other.m_status),
    m_topos(other.m_topos)
{}

BleauCircuit::~BleauCircuit()
{}

BleauCircuit &
BleauCircuit::operator=(const BleauCircuit & other)
{
  if (this != &other) {
    m_coordinate = other.m_coordinate;
    m_boulders = other.m_boulders;
    m_colour = other.m_colour;
    m_creation_date = other.m_creation_date;
    m_gestion = other.m_gestion;
    m_grade = other.m_grade;
    m_massif = other.m_massif;
    m_note = other.m_note;
    m_number = other.m_number;
    m_opener = other.m_opener;
    m_refection_date = other.m_refection_date;
    m_refection_note = other.m_refection_note;
    m_status = other.m_status;
    m_topos = other.m_topos;
  }

  return *this;
}

void
BleauCircuit::set_coordinate(const QGeoCoordinate & coordinate)
{
  m_coordinate = coordinate;
  emit coordinateChanged();
}

// void
// BleauCircuit::set_boulders(BleauBoulderList boulders)
// {
//   m_boulders = boulders;
//   emit bouldersChanged();
// }

void
BleauCircuit::add_boulder(const BleauBoulder & boulder)
{
  m_boulders.append(boulder);
  // emit bouldersChanged();
}

void
BleauCircuit::set_colour(const QString & colour)
{
  m_colour = colour;
  emit colourChanged();
}

void
BleauCircuit::set_creation_date(unsigned int creation_date)
{
  m_creation_date = creation_date;
  emit creation_dateChanged();
}

void
BleauCircuit::set_gestion(const QString & gestion)
{
  m_gestion = gestion;
  emit gestionChanged();
}

void
BleauCircuit::set_grade(BleauAlpineGrade grade)
{
  m_grade = grade;
  emit gradeChanged();
}

void
BleauCircuit::set_massif(BleauMassif * massif)
{
  m_massif = massif;
  emit massifChanged();
}

void
BleauCircuit::set_note(const QString & note)
{
  m_note = note;
  emit noteChanged();
}

void
BleauCircuit::set_number(unsigned int number)
{
  m_number = number;
  emit numberChanged();
}

void
BleauCircuit::set_opener(BleauOpeners opener)
{
  m_opener = opener;
  emit openerChanged();
}

void
BleauCircuit::set_refection_date(unsigned int refection_date)
{
  m_refection_date = refection_date;
  emit refection_dateChanged();
}

void
BleauCircuit::set_refection_note(BleauRefectionNote refection_note)
{
  m_refection_note = refection_note;
  emit refection_noteChanged();
}

void
BleauCircuit::set_status(const QString & status)
{
  m_status = status;
  emit statusChanged();
}

void
BleauCircuit::set_topos(const QList<QString> & topos)
{
  m_topos = topos;
  emit toposChanged();
}

/**************************************************************************************************/

BleauDB::BleauDB(QObject * parent)
  : QObject(parent),
    m_places(),
    m_massifs(),
    m_circuits()
{}

// BleauDB::BleauDB(const BleauDB & other, QObject * parent)
//   : QObject(parent),
//     m_places(other.m_places),
//     m_massifs(other.m_massifs),
//     m_circuits(other.m_circuits)
// {}

BleauDB::~BleauDB()
{}

// BleauDB &
// BleauDB::operator=(const BleauDB & other)
// {
//   if (this != &other) {
//     m_places = other.m_places;
//     m_massifs = other.m_massifs;
//     m_circuits = other.m_circuits;
//   }

//   return *this;
// }

void
BleauDB::add_place(const BleauPlace & place)
{
  m_places.insert(place.name(), place);
  // emit placesChanged();
}

void
BleauDB::add_massif(const BleauMassif & massif)
{
  m_massifs.insert(massif.name(), massif);
  // emit massifsChanged();
}

void
BleauDB::add_circuit(const BleauCircuit & circuit)
{
  m_circuits.append(circuit);
  // emit circuitsChanged();
}

/**************************************************************************************************/

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
