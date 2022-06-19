/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "third_party_license_schema_manager.h"
#include "alpine_toolkit.h"

#include "third_party_license_sqlite_database.h"

#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QSet>
#include <QtDebug>

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

ThirdPartyLicenseSchemaManager::ThirdPartyLicenseSchemaManager()
  : SchemaManager(),
    m_json_path(),
    m_json_loaded(false),
    m_third_party_license_cache()
{}

ThirdPartyLicenseSchemaManager::ThirdPartyLicenseSchemaManager(const QString & json_path, bool lazy)
  : ThirdPartyLicenseSchemaManager()
{
  m_json_path = json_path;
  if (not lazy)
    SchemaManager::load_json(json_path);
}

/*
ThirdPartyLicenseSchemaManager::ThirdPartyLicenseSchemaManager(const QJsonDocument & json_document)
 : ThirdPartyLicenseSchemaManager()
{
  load_json_document(json_document);
}
*/

ThirdPartyLicenseSchemaManager::~ThirdPartyLicenseSchemaManager()
{}

void
ThirdPartyLicenseSchemaManager::load_json_document(const QJsonDocument & json_document)
{
  // qATInfo() << "Load Third Party Licenses JSON";

  QJsonArray array = json_document.array();

  for (const auto & json_value : array) {
    ThirdPartyLicensePtr third_party_license(json_value.toObject());
    // Fixme: keep one
    m_third_party_license_cache.add(third_party_license);
    m_third_party_licenses << third_party_license;
  }

  emit third_party_license_list_changed();
}

void
ThirdPartyLicenseSchemaManager::load_json()
{
  if (not (m_json_loaded or m_json_path.isEmpty())) {
    SchemaManager::load_json(m_json_path);
    m_json_loaded = true;
  }
}

QJsonDocument
ThirdPartyLicenseSchemaManager::to_json_document() // const
{
  QJsonArray array;

  for (const auto & third_party_license : m_third_party_license_cache.items())
    array << third_party_license->to_json();

  return QJsonDocument(array);
}

/*
void
ThirdPartyLicenseSchemaManager::to_sql(const QString & sqlite_path)
{
  // Fixme: has a cache
  ThirdPartyLicenseSqliteDatabase third_party_license_sqlite_database(sqlite_path);
  ThirdPartyLicenseDatabaseSchema & third_party_license_schema = third_party_license_sqlite_database.schema();

  // Fixme: if use cache, in an arbitrary order, and const issue
  // m_third_party_license_cache.items()

  // Run as transaction
  third_party_license_schema.add_row_ptrs(m_third_party_licenses);
}

void
ThirdPartyLicenseSchemaManager::from_sql(const QString & sqlite_path)
{
  // Fixme: has a cache
  ThirdPartyLicenseSqliteDatabase third_party_license_sqlite_database(sqlite_path);
  ThirdPartyLicenseDatabaseSchema & third_party_license_schema = third_party_license_sqlite_database.schema();

  qATInfo() << "Load third_party_licenses";
  ThirdPartyLicense::PtrList third_party_licenses = third_party_license_schema.query<ThirdPartyLicense>(false);
  for (const auto third_party_license : third_party_licenses)
    qATInfo() << third_party_license;
}
*/

QQmlListProperty<ThirdPartyLicense>
ThirdPartyLicenseSchemaManager::third_party_license_list_property()
{
  // Called at init or when the list change
  // qATInfo() << "ThirdPartyLicenseSchemaManager::third_party_license_list_property";
  return QQmlListProperty<ThirdPartyLicense>(this,
                                  nullptr, // data
                                  &ThirdPartyLicenseSchemaManager::third_party_license_list_property_count,
                                  &ThirdPartyLicenseSchemaManager::third_party_license_list_property_at);
}

qsizetype
ThirdPartyLicenseSchemaManager::third_party_license_list_property_count(QQmlListProperty<ThirdPartyLicense> * list)
{
  // Called several times
  // qATInfo() << "ThirdPartyLicenseSchemaManager::third_party_license_list_property_count";
  ThirdPartyLicenseSchemaManager * third_party_license_schema_manager = qobject_cast<ThirdPartyLicenseSchemaManager *>(list->object);
  return third_party_license_schema_manager->m_third_party_licenses.size();
}

ThirdPartyLicense *
ThirdPartyLicenseSchemaManager::third_party_license_list_property_at(QQmlListProperty<ThirdPartyLicense> * list, qsizetype index)
{
  // Called several times
  // qATInfo() << "ThirdPartyLicenseSchemaManager::third_party_license_list_property_at" << index;
  ThirdPartyLicenseSchemaManager * third_party_license_schema_manager = qobject_cast<ThirdPartyLicenseSchemaManager *>(list->object);
  ThirdPartyLicensePtr & third_party_license = third_party_license_schema_manager->m_third_party_licenses[index];
  return third_party_license.data();
}

/**************************************************************************************************/

// QC_END_NAMESPACE
