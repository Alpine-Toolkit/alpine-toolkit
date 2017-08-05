// -*- mode: c++ -*-

/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
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
** $ALPINE_TOOLKIT_END_LICENSE$
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
  Q_PROPERTY(QQmlListProperty<ThirdPartyLicense> third_party_licenses READ third_party_license_list_property NOTIFY third_party_licenseListChanged)

public:
  ThirdPartyLicenseSchemaManager();
  ThirdPartyLicenseSchemaManager(const QString & json_path);
  ThirdPartyLicenseSchemaManager(const QJsonDocument & json_document);
  // ThirdPartyLicenseSchemaManager(const class ThirdPartyLicenseSchemaManager & other);
  ~ThirdPartyLicenseSchemaManager();

  // ThirdPartyLicenseSchemaManager & operator=(const ThirdPartyLicenseSchemaManager & other);

  void load_json_document(const QJsonDocument & json_document);
  QJsonDocument to_json_document(); // const

  void to_sql(const QString & sqlite_path);
  void from_sql(const QString & sqlite_path);

  // Get third_party_licenses as a list
  const ThirdPartyLicense::PtrList third_party_licenses() const { return m_third_party_license_cache.items(); }

signals:
  void third_party_licenseListChanged();

private:
  // QQmlListProperty can only be used for lists of QObject-derived object pointers.
  // ThirdPartyLicenses must be registered
  QQmlListProperty<ThirdPartyLicense> third_party_license_list_property();
  static int third_party_license_list_property_count(QQmlListProperty<ThirdPartyLicense> * list);
  static ThirdPartyLicense * third_party_license_list_property_at(QQmlListProperty<ThirdPartyLicense> * list, int index);

private:
  ThirdPartyLicenseCache m_third_party_license_cache;
  ThirdPartyLicense::PtrList m_third_party_licenses; // ordered
};

/**************************************************************************************************/

// QC_END_NAMESPACE

#endif /* __THIRD_PARTY_LICENSE_SCHEMA_MANAGER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
