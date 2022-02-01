// This file was automatically generated by SqlOrm

/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine Toolkit software.
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
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "third_party_license_schema.h"
#include "alpine_toolkit.h"

#include "orm/database_query.h"
#include "orm/type_conversion.h"

#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE


ThirdPartyLicenseSchema::ThirdPartyLicenseSchema()
: QoSchema(QLatin1String("ThirdPartyLicense"), QLatin1String("third_party_license"))
{
  {
    QoSchemaPrimaryKey field(
      QLatin1String("id"),
      QLatin1String("int"),
      QLatin1String("integer"),
      QLatin1String("id"),
      QLatin1String("id"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    field.set_nullable(false);
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("used"),
      QLatin1String("bool"),
      QLatin1String("integer"),
      QLatin1String("used"),
      QLatin1String("used"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("show"),
      QLatin1String("bool"),
      QLatin1String("integer"),
      QLatin1String("show"),
      QLatin1String("show"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("third_party_name"),
      QLatin1String("QString"),
      QLatin1String("text"),
      QLatin1String("third_party_name"),
      QLatin1String("third_party_name"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("third_party_url"),
      QLatin1String("QUrl"),
      QLatin1String("text"),
      QLatin1String("third_party_url"),
      QLatin1String("third_party_url"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("third_party_version"),
      QLatin1String("QString"),
      QLatin1String("text"),
      QLatin1String("third_party_version"),
      QLatin1String("third_party_version"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("license_name"),
      QLatin1String("QString"),
      QLatin1String("text"),
      QLatin1String("license_name"),
      QLatin1String("license_name"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("license_url"),
      QLatin1String("QUrl"),
      QLatin1String("text"),
      QLatin1String("license_url"),
      QLatin1String("license_url"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("license_text"),
      QLatin1String("QString"),
      QLatin1String("text"),
      QLatin1String("license_text"),
      QLatin1String("license_text"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
  {
    QoSchemaField field(
      QLatin1String("license_note"),
      QLatin1String("QString"),
      QLatin1String("text"),
      QLatin1String("license_note"),
      QLatin1String("license_note"),
      QLatin1String(""),
      QLatin1String(""));
    // Optional parameters
    add_field(field);
  }
}

ThirdPartyLicenseSchema::~ThirdPartyLicenseSchema()
{}

/**************************************************************************************************/

ThirdPartyLicense::ThirdPartyLicense()
  : QObject(),
    QoRow<ThirdPartyLicenseSchema>(),
    m_id(),
    m_used(),
    m_show(),
    m_third_party_name(),
    m_third_party_url(),
    m_third_party_version(),
    m_license_name(),
    m_license_url(),
    m_license_text(),
    m_license_note()
{
}

ThirdPartyLicense::ThirdPartyLicense(const ThirdPartyLicense & other)
  : QObject(),
    QoRow<ThirdPartyLicenseSchema>(other),
    m_id(other.m_id),
    m_used(other.m_used),
    m_show(other.m_show),
    m_third_party_name(other.m_third_party_name),
    m_third_party_url(other.m_third_party_url),
    m_third_party_version(other.m_third_party_version),
    m_license_name(other.m_license_name),
    m_license_url(other.m_license_url),
    m_license_text(other.m_license_text),
    m_license_note(other.m_license_note)
{
}

ThirdPartyLicense::ThirdPartyLicense(const QJsonObject & json_object)
 : ThirdPartyLicense()
{
  m_id = json_object[QLatin1String("id")].toInt();
  m_used = json_object[QLatin1String("used")].toBool();
  m_show = json_object[QLatin1String("show")].toBool();
  m_third_party_name = json_object[QLatin1String("third_party_name")].toString();
  m_third_party_url = json_object[QLatin1String("third_party_url")].toString();
  m_third_party_version = json_object[QLatin1String("third_party_version")].toString();
  m_license_name = json_object[QLatin1String("license_name")].toString();
  m_license_url = json_object[QLatin1String("license_url")].toString();
  m_license_text = json_object[QLatin1String("license_text")].toString();
  m_license_note = json_object[QLatin1String("license_note")].toString();
}

ThirdPartyLicense::ThirdPartyLicense(const QVariantHash & variant_hash)
 : ThirdPartyLicense()
{
  m_id = variant_hash[QLatin1String("id")].toInt();
  m_used = variant_hash[QLatin1String("used")].toBool();
  m_show = variant_hash[QLatin1String("show")].toBool();
  m_third_party_name = variant_hash[QLatin1String("third_party_name")].toString();
  m_third_party_url = variant_hash[QLatin1String("third_party_url")].toUrl();
  m_third_party_version = variant_hash[QLatin1String("third_party_version")].toString();
  m_license_name = variant_hash[QLatin1String("license_name")].toString();
  m_license_url = variant_hash[QLatin1String("license_url")].toUrl();
  m_license_text = variant_hash[QLatin1String("license_text")].toString();
  m_license_note = variant_hash[QLatin1String("license_note")].toString();
}

ThirdPartyLicense::ThirdPartyLicense(const QVariantList & variants)
 : ThirdPartyLicense()
{
  m_id = variants[0].toInt();
  m_used = variants[1].toBool();
  m_show = variants[2].toBool();
  m_third_party_name = variants[3].toString();
  m_third_party_url = variants[4].toUrl();
  m_third_party_version = variants[5].toString();
  m_license_name = variants[6].toString();
  m_license_url = variants[7].toUrl();
  m_license_text = variants[8].toString();
  m_license_note = variants[9].toString();
}

ThirdPartyLicense::ThirdPartyLicense(const QSqlRecord & record)
 : QoRow<ThirdPartyLicenseSchema>(record)
{
  m_id = record.value(0).toInt();
  m_used = record.value(1).toBool();
  m_show = record.value(2).toBool();
  m_third_party_name = record.value(3).toString();
  m_third_party_url = record.value(4).toUrl();
  m_third_party_version = record.value(5).toString();
  m_license_name = record.value(6).toString();
  m_license_url = record.value(7).toUrl();
  m_license_text = record.value(8).toString();
  m_license_note = record.value(9).toString();
}

ThirdPartyLicense::ThirdPartyLicense(const QSqlQuery & query, int offset)
 : QoRow<ThirdPartyLicenseSchema>(query)
{
  m_id = query.value(offset++).toInt();
  m_used = query.value(offset++).toBool();
  m_show = query.value(offset++).toBool();
  m_third_party_name = query.value(offset++).toString();
  m_third_party_url = query.value(offset++).toUrl();
  m_third_party_version = query.value(offset++).toString();
  m_license_name = query.value(offset++).toString();
  m_license_url = query.value(offset++).toUrl();
  m_license_text = query.value(offset++).toString();
  m_license_note = query.value(offset).toString();
}

ThirdPartyLicense::~ThirdPartyLicense()
{
// qATInfo() << "--- Delete" << "ThirdPartyLicense" << *this;
}

// bit array ?
ThirdPartyLicense &
ThirdPartyLicense::operator=(const ThirdPartyLicense & other)
{
  if (this != &other) {
    QoRow<ThirdPartyLicenseSchema>::operator=(other);
    m_id = other.m_id;
    m_used = other.m_used;
    m_show = other.m_show;
    m_third_party_name = other.m_third_party_name;
    m_third_party_url = other.m_third_party_url;
    m_third_party_version = other.m_third_party_version;
    m_license_name = other.m_license_name;
    m_license_url = other.m_license_url;
    m_license_text = other.m_license_text;
    m_license_note = other.m_license_note;
  }

  return *this;
}

// bit array ?
bool
ThirdPartyLicense::operator==(const ThirdPartyLicense & other) const
{
  if (not QoRow<ThirdPartyLicenseSchema>::operator==(other))
    return false;
  if (m_id != other.m_id)
    return false;
  if (m_used != other.m_used)
    return false;
  if (m_show != other.m_show)
    return false;
  if (m_third_party_name != other.m_third_party_name)
    return false;
  if (m_third_party_url != other.m_third_party_url)
    return false;
  if (m_third_party_version != other.m_third_party_version)
    return false;
  if (m_license_name != other.m_license_name)
    return false;
  if (m_license_url != other.m_license_url)
    return false;
  if (m_license_text != other.m_license_text)
    return false;
  if (m_license_note != other.m_license_note)
    return false;

  return true;
}

void
ThirdPartyLicense::set_id(int value)
{
  if (m_id != value) {
    m_id = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::ID);

    emit idChanged();
    if (not is_changed)
      emit changed();
  }
}

void
ThirdPartyLicense::set_used(bool value)
{
  if (m_used != value) {
    m_used = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::USED);

    emit usedChanged();
    if (not is_changed)
      emit changed();
  }
}

void
ThirdPartyLicense::set_show(bool value)
{
  if (m_show != value) {
    m_show = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::SHOW);

    emit showChanged();
    if (not is_changed)
      emit changed();
  }
}

void
ThirdPartyLicense::set_third_party_name(const QString & value)
{
  if (m_third_party_name != value) {
    m_third_party_name = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::THIRD_PARTY_NAME);

    emit third_party_nameChanged();
    if (not is_changed)
      emit changed();
  }
}

void
ThirdPartyLicense::set_third_party_url(const QUrl & value)
{
  if (m_third_party_url != value) {
    m_third_party_url = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::THIRD_PARTY_URL);

    emit third_party_urlChanged();
    if (not is_changed)
      emit changed();
  }
}

void
ThirdPartyLicense::set_third_party_version(const QString & value)
{
  if (m_third_party_version != value) {
    m_third_party_version = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::THIRD_PARTY_VERSION);

    emit third_party_versionChanged();
    if (not is_changed)
      emit changed();
  }
}

void
ThirdPartyLicense::set_license_name(const QString & value)
{
  if (m_license_name != value) {
    m_license_name = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::LICENSE_NAME);

    emit license_nameChanged();
    if (not is_changed)
      emit changed();
  }
}

void
ThirdPartyLicense::set_license_url(const QUrl & value)
{
  if (m_license_url != value) {
    m_license_url = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::LICENSE_URL);

    emit license_urlChanged();
    if (not is_changed)
      emit changed();
  }
}

void
ThirdPartyLicense::set_license_text(const QString & value)
{
  if (m_license_text != value) {
    m_license_text = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::LICENSE_TEXT);

    emit license_textChanged();
    if (not is_changed)
      emit changed();
  }
}

void
ThirdPartyLicense::set_license_note(const QString & value)
{
  if (m_license_note != value) {
    m_license_note = value;

    bool is_changed = is_modified();
    set_bit(Schema::Fields::LICENSE_NOTE);

    emit license_noteChanged();
    if (not is_changed)
      emit changed();
  }
}

QJsonObject
ThirdPartyLicense::to_json(bool only_changed) const
{
  QJsonObject json_object;

 if (only_changed) {
    if (is_used_modified())
      json_object.insert(QLatin1String("used"), QJsonValue(m_used));
    if (is_show_modified())
      json_object.insert(QLatin1String("show"), QJsonValue(m_show));
    if (is_third_party_name_modified())
      json_object.insert(QLatin1String("third_party_name"), QJsonValue(m_third_party_name));
    if (is_third_party_url_modified())
      json_object.insert(QLatin1String("third_party_url"), orm_type_conversion::dump_url(m_third_party_url));
    if (is_third_party_version_modified())
      json_object.insert(QLatin1String("third_party_version"), QJsonValue(m_third_party_version));
    if (is_license_name_modified())
      json_object.insert(QLatin1String("license_name"), QJsonValue(m_license_name));
    if (is_license_url_modified())
      json_object.insert(QLatin1String("license_url"), orm_type_conversion::dump_url(m_license_url));
    if (is_license_text_modified())
      json_object.insert(QLatin1String("license_text"), QJsonValue(m_license_text));
    if (is_license_note_modified())
      json_object.insert(QLatin1String("license_note"), QJsonValue(m_license_note));
  } else {
    json_object.insert(QLatin1String("used"), QJsonValue(m_used));
    json_object.insert(QLatin1String("show"), QJsonValue(m_show));
    json_object.insert(QLatin1String("third_party_name"), QJsonValue(m_third_party_name));
    json_object.insert(QLatin1String("third_party_url"), orm_type_conversion::dump_url(m_third_party_url));
    json_object.insert(QLatin1String("third_party_version"), QJsonValue(m_third_party_version));
    json_object.insert(QLatin1String("license_name"), QJsonValue(m_license_name));
    json_object.insert(QLatin1String("license_url"), orm_type_conversion::dump_url(m_license_url));
    json_object.insert(QLatin1String("license_text"), QJsonValue(m_license_text));
    json_object.insert(QLatin1String("license_note"), QJsonValue(m_license_note));
  }

  return json_object;
}

QVariantHash
ThirdPartyLicense::to_variant_hash(bool only_changed) const
{
  QVariantHash variant_hash;

  if (only_changed) {
    if (is_id_modified())
      variant_hash[QLatin1String("id")] = m_id;
    if (is_used_modified())
      variant_hash[QLatin1String("used")] = m_used;
    if (is_show_modified())
      variant_hash[QLatin1String("show")] = m_show;
    if (is_third_party_name_modified())
      variant_hash[QLatin1String("third_party_name")] = m_third_party_name;
    if (is_third_party_url_modified())
      variant_hash[QLatin1String("third_party_url")] = m_third_party_url;
    if (is_third_party_version_modified())
      variant_hash[QLatin1String("third_party_version")] = m_third_party_version;
    if (is_license_name_modified())
      variant_hash[QLatin1String("license_name")] = m_license_name;
    if (is_license_url_modified())
      variant_hash[QLatin1String("license_url")] = m_license_url;
    if (is_license_text_modified())
      variant_hash[QLatin1String("license_text")] = m_license_text;
    if (is_license_note_modified())
      variant_hash[QLatin1String("license_note")] = m_license_note;
  } else {
    variant_hash[QLatin1String("id")] = m_id;
    variant_hash[QLatin1String("used")] = m_used;
    variant_hash[QLatin1String("show")] = m_show;
    variant_hash[QLatin1String("third_party_name")] = m_third_party_name;
    variant_hash[QLatin1String("third_party_url")] = m_third_party_url;
    variant_hash[QLatin1String("third_party_version")] = m_third_party_version;
    variant_hash[QLatin1String("license_name")] = m_license_name;
    variant_hash[QLatin1String("license_url")] = m_license_url;
    variant_hash[QLatin1String("license_text")] = m_license_text;
    variant_hash[QLatin1String("license_note")] = m_license_note;
  }

  return variant_hash;
}

QVariantList
ThirdPartyLicense::to_variant_list() const
{
  QVariantList variants;

  variants << m_id;
  variants << m_used;
  variants << m_show;
  variants << m_third_party_name;
  variants << m_third_party_url;
  variants << m_third_party_version;
  variants << m_license_name;
  variants << m_license_url;
  variants << m_license_text;
  variants << m_license_note;

  return variants;
}

QVariantHash
ThirdPartyLicense::to_variant_hash_sql(bool only_changed, bool duplicate) const
{
  QVariantHash variant_hash;

  if (only_changed) {
    if (is_id_modified())
      variant_hash[QLatin1String("id")] = m_id;
    if (is_used_modified())
      variant_hash[QLatin1String("used")] = m_used;
    if (is_show_modified())
      variant_hash[QLatin1String("show")] = m_show;
    if (is_third_party_name_modified())
      variant_hash[QLatin1String("third_party_name")] = m_third_party_name;
    if (is_third_party_url_modified())
      variant_hash[QLatin1String("third_party_url")] = m_third_party_url;
    if (is_third_party_version_modified())
      variant_hash[QLatin1String("third_party_version")] = m_third_party_version;
    if (is_license_name_modified())
      variant_hash[QLatin1String("license_name")] = m_license_name;
    if (is_license_url_modified())
      variant_hash[QLatin1String("license_url")] = m_license_url;
    if (is_license_text_modified())
      variant_hash[QLatin1String("license_text")] = m_license_text;
    if (is_license_note_modified())
      variant_hash[QLatin1String("license_note")] = m_license_note;
  } else {
    if (duplicate)
      variant_hash[QLatin1String("id")] = m_id;
    variant_hash[QLatin1String("used")] = m_used;
    variant_hash[QLatin1String("show")] = m_show;
    variant_hash[QLatin1String("third_party_name")] = m_third_party_name;
    variant_hash[QLatin1String("third_party_url")] = m_third_party_url;
    variant_hash[QLatin1String("third_party_version")] = m_third_party_version;
    variant_hash[QLatin1String("license_name")] = m_license_name;
    variant_hash[QLatin1String("license_url")] = m_license_url;
    variant_hash[QLatin1String("license_text")] = m_license_text;
    variant_hash[QLatin1String("license_note")] = m_license_note;
  }

  return variant_hash;
}

QVariantList
ThirdPartyLicense::to_variant_list_sql(bool duplicate) const
{
  QVariantList variants;

  if (duplicate)
    variants << m_id;
  variants << m_used;
  variants << m_show;
  variants << m_third_party_name;
  variants << m_third_party_url;
  variants << m_third_party_version;
  variants << m_license_name;
  variants << m_license_url;
  variants << m_license_text;
  variants << m_license_note;

  return variants;
}

QVariant
ThirdPartyLicense::field(int position) const
{
  switch(position) {
   case Schema::Fields::ID:
     return m_id;
   case Schema::Fields::USED:
     return m_used;
   case Schema::Fields::SHOW:
     return m_show;
   case Schema::Fields::THIRD_PARTY_NAME:
     return m_third_party_name;
   case Schema::Fields::THIRD_PARTY_URL:
     return m_third_party_url;
   case Schema::Fields::THIRD_PARTY_VERSION:
     return m_third_party_version;
   case Schema::Fields::LICENSE_NAME:
     return m_license_name;
   case Schema::Fields::LICENSE_URL:
     return m_license_url;
   case Schema::Fields::LICENSE_TEXT:
     return m_license_text;
   case Schema::Fields::LICENSE_NOTE:
     return m_license_note;
   default:
     return QVariant(); // error
  }
}

void
ThirdPartyLicense::set_field(int position, const QVariant & value)
{
  switch(position) {
   case Schema::Fields::ID: {
     m_id = value.toInt();
     break;
   }
   case Schema::Fields::USED: {
     m_used = value.toBool();
     break;
   }
   case Schema::Fields::SHOW: {
     m_show = value.toBool();
     break;
   }
   case Schema::Fields::THIRD_PARTY_NAME: {
     m_third_party_name = value.toString();
     break;
   }
   case Schema::Fields::THIRD_PARTY_URL: {
     m_third_party_url = value.toUrl();
     break;
   }
   case Schema::Fields::THIRD_PARTY_VERSION: {
     m_third_party_version = value.toString();
     break;
   }
   case Schema::Fields::LICENSE_NAME: {
     m_license_name = value.toString();
     break;
   }
   case Schema::Fields::LICENSE_URL: {
     m_license_url = value.toUrl();
     break;
   }
   case Schema::Fields::LICENSE_TEXT: {
     m_license_text = value.toString();
     break;
   }
   case Schema::Fields::LICENSE_NOTE: {
     m_license_note = value.toString();
     break;
   }
  }
}

void
ThirdPartyLicense::set_insert_id(int id)
{
  set_id(id);

}

bool
ThirdPartyLicense::can_update() const
{
  return m_id > 0;
}

QVariantHash
ThirdPartyLicense::rowid_kwargs() const // To update row
{
  QVariantHash where_kwargs;
  where_kwargs[QLatin1String("id")] = m_id;
  return where_kwargs;
}

QDataStream &
operator<<(QDataStream & out, const ThirdPartyLicense & obj)
{
  out << obj.id();
  out << obj.used();
  out << obj.show();
  out << obj.third_party_name();
  out << obj.third_party_url();
  out << obj.third_party_version();
  out << obj.license_name();
  out << obj.license_url();
  out << obj.license_text();
  out << obj.license_note();

  return out;
}

QDataStream &
operator>>(QDataStream & in, ThirdPartyLicense & obj)
{
  QString _QString;
  QUrl _QUrl;
  bool _bool;
  int _int;
  in >> _int;
  obj.set_id(_int);
  in >> _bool;
  obj.set_used(_bool);
  in >> _bool;
  obj.set_show(_bool);
  in >> _QString;
  obj.set_third_party_name(_QString);
  in >> _QUrl;
  obj.set_third_party_url(_QUrl);
  in >> _QString;
  obj.set_third_party_version(_QString);
  in >> _QString;
  obj.set_license_name(_QString);
  in >> _QUrl;
  obj.set_license_url(_QUrl);
  in >> _QString;
  obj.set_license_text(_QString);
  in >> _QString;
  obj.set_license_note(_QString);

  return in;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const ThirdPartyLicense & obj)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  // Fixme: quote string !
  debug.nospace() << QStringLiteral("ThirdPartyLicense(");
  debug << obj.id();
  debug << QStringLiteral(", ");
  debug << obj.used();
  debug << QStringLiteral(", ");
  debug << obj.show();
  debug << QStringLiteral(", ");
  debug << obj.third_party_name();
  debug << QStringLiteral(", ");
  debug << obj.third_party_url();
  debug << QStringLiteral(", ");
  debug << obj.third_party_version();
  debug << QStringLiteral(", ");
  debug << obj.license_name();
  debug << QStringLiteral(", ");
  debug << obj.license_url();
  debug << QStringLiteral(", ");
  debug << obj.license_text();
  debug << QStringLiteral(", ");
  debug << obj.license_note();
  debug << ')';

  return debug;
}
#endif

/**************************************************************************************************/

#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const ThirdPartyLicensePtr & obj)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.noquote() << QStringLiteral("ThirdPartyLicensePtr ->");
  if (obj)
    debug << *obj;
   else
  debug  << QStringLiteral("NULL");

  return debug;
}
#endif

/**************************************************************************************************/

ThirdPartyLicenseCache::ThirdPartyLicenseCache()
 : m_loaded_instances(),
   m_modified_instances()
{}

ThirdPartyLicenseCache::~ThirdPartyLicenseCache()
{}

void
ThirdPartyLicenseCache::add(ThirdPartyLicensePtr & ptr)
{
  m_loaded_instances.insert(ptr.data(), ptr);
  QObject::connect(ptr.data(), &ThirdPartyLicense::changed,
                   this, &ThirdPartyLicenseCache::on_changed);
}

void
ThirdPartyLicenseCache::remove(ThirdPartyLicensePtr & ptr)
{
  Q_UNUSED(ptr);
}

void
ThirdPartyLicenseCache::on_changed()
{
  ThirdPartyLicense * row = qobject_cast<ThirdPartyLicense *>(QObject::sender());
  qATInfo() << "On changed" << row;
  ThirdPartyLicensePtr row_ptr = m_loaded_instances[row];
  if (row_ptr)
    m_modified_instances.insert(row, row_ptr);
}

/**************************************************************************************************/

ThirdPartyLicenseModel::ThirdPartyLicenseModel()
  : QAbstractListModel(),
    m_items()
{}

ThirdPartyLicenseModel::ThirdPartyLicenseModel(const ItemList & items)
  : QAbstractListModel(),
    m_items(items)
{}

ThirdPartyLicenseModel::~ThirdPartyLicenseModel()
{}

int
ThirdPartyLicenseModel::rowCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent);
  return m_items.size();
}

QVariant
ThirdPartyLicenseModel::data(const QModelIndex & index, int role) const
{
  if (!index.isValid() || index.row() < 0)
    return QVariant();

  if (index.row() >= m_items.count()) {
    qWarning() << "ThirdPartyLicenseModel: Index out of bound";
    return QVariant();
  }

  const Item & item = m_items[index.row()];
  switch (role) {
  case ID:
    return item->id();
  case USED:
    return item->used();
  case SHOW:
    return item->show();
  case THIRD_PARTY_NAME:
    return item->third_party_name();
  case THIRD_PARTY_URL:
    return item->third_party_url();
  case THIRD_PARTY_VERSION:
    return item->third_party_version();
  case LICENSE_NAME:
    return item->license_name();
  case LICENSE_URL:
    return item->license_url();
  case LICENSE_TEXT:
    return item->license_text();
  case LICENSE_NOTE:
    return item->license_note();
  default:
    break;
  }

  return QVariant();
}

QHash<int, QByteArray>
ThirdPartyLicenseModel::roleNames() const
{
  // Fixme: cache ???
  QHash<int, QByteArray> role_names;
  role_names[ID] = QStringLiteral("id").latin1();
  role_names[USED] = QStringLiteral("used").latin1();
  role_names[SHOW] = QStringLiteral("show").latin1();
  role_names[THIRD_PARTY_NAME] = QStringLiteral("third_party_name").latin1();
  role_names[THIRD_PARTY_URL] = QStringLiteral("third_party_url").latin1();
  role_names[THIRD_PARTY_VERSION] = QStringLiteral("third_party_version").latin1();
  role_names[LICENSE_NAME] = QStringLiteral("license_name").latin1();
  role_names[LICENSE_URL] = QStringLiteral("license_url").latin1();
  role_names[LICENSE_TEXT] = QStringLiteral("license_text").latin1();
  role_names[LICENSE_NOTE] = QStringLiteral("license_note").latin1();

  return role_names;
}

void
ThirdPartyLicenseModel::clear_items()
{
  beginResetModel();
  m_items.clear();
  endResetModel();
}

void
ThirdPartyLicenseModel::set_items(const ItemList & items)
{
  beginResetModel();
  m_items = items;
  endResetModel();
}
ThirdPartyLicenseDatabaseSchema::ThirdPartyLicenseDatabaseSchema(QoDatabase & database)
  : QoDatabaseSchema(database),
    m_third_party_license(nullptr),
    m_third_party_license_cache()
{
  m_third_party_license = &register_table(ThirdPartyLicenseSchema::instance());
}

ThirdPartyLicenseDatabaseSchema::~ThirdPartyLicenseDatabaseSchema()
{}

template<>
void
ThirdPartyLicenseDatabaseSchema::register_row<ThirdPartyLicense>(ThirdPartyLicensePtr & row)
{
  qATInfo() << "Register in cache" << row;
  m_third_party_license_cache.add(row);
}

/**************************************************************************************************/
// QC_END_NAMESPACE