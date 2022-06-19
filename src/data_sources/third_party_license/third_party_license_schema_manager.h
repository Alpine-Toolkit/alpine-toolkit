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

#ifndef __THIRD_PARTY_LICENSE_SCHEMA_MANAGER_H__
#define __THIRD_PARTY_LICENSE_SCHEMA_MANAGER_H__

/**************************************************************************************************/

#include "orm/schema_manager.h"
#include "third_party_license/third_party_license_schema.h"

#include <QQmlListProperty>
#include<QHash>
#include<QJsonDocument>
#include<QObject>
#include<QString>

/**************************************************************************************************/

// Q_DECLARE_METATYPE(ThirdPartyLicense)
// Q_DECLARE_METATYPE(ThirdPartyLicense*)

/**************************************************************************************************/

class ThirdPartyLicenseSchemaManager : public SchemaManager
{
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<ThirdPartyLicense> third_party_licenses READ third_party_license_list_property NOTIFY third_party_license_list_changed)

public:
  ThirdPartyLicenseSchemaManager();
  ThirdPartyLicenseSchemaManager(const QString & json_path, bool lazy = true);
  // ThirdPartyLicenseSchemaManager(const QJsonDocument & json_document);
  // ThirdPartyLicenseSchemaManager(const class ThirdPartyLicenseSchemaManager & other);
  ~ThirdPartyLicenseSchemaManager();

  // ThirdPartyLicenseSchemaManager & operator=(const ThirdPartyLicenseSchemaManager & other);

  const QString & json_path() const { return m_json_path; }
  void set_json_path(const QString & json_path) { m_json_path = json_path; }
  Q_INVOKABLE bool is_json_loaded() const { return m_json_loaded; }
  Q_INVOKABLE void load_json();

  QJsonDocument to_json_document(); // const

  // void to_sql(const QString & sqlite_path);
  // void from_sql(const QString & sqlite_path);

  // Get third_party_licenses as a list
  const ThirdPartyLicense::PtrList third_party_licenses() const { return m_third_party_license_cache.items(); }

signals:
  void third_party_license_list_changed();

private:
  void load_json_document(const QJsonDocument & json_document);
  // QQmlListProperty can only be used for lists of QObject-derived object pointers.
  // ThirdPartyLicenses must be registered
  QQmlListProperty<ThirdPartyLicense> third_party_license_list_property();
  static qsizetype third_party_license_list_property_count(QQmlListProperty<ThirdPartyLicense> * list);
  static ThirdPartyLicense * third_party_license_list_property_at(QQmlListProperty<ThirdPartyLicense> * list, qsizetype index);

private:
  QString m_json_path;
  bool m_json_loaded = true;
  ThirdPartyLicenseCache m_third_party_license_cache;
  ThirdPartyLicense::PtrList m_third_party_licenses; // ordered
};

/**************************************************************************************************/

// QC_END_NAMESPACE

#endif /* __THIRD_PARTY_LICENSE_SCHEMA_MANAGER_H__ */
