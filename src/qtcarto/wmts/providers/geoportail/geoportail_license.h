// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __QC_GEOPORTAIL_LICENSE_H__
#define __QC_GEOPORTAIL_LICENSE_H__

/**************************************************************************************************/

#include <QString>
#include <QJsonObject>

#include "qtcarto_global.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/// The QcGeoportailWmtsLicense class defines a Geoportail license
class QC_EXPORT QcGeoportailWmtsLicense
{
 public:
  QcGeoportailWmtsLicense(const QString & json_path);
  QcGeoportailWmtsLicense(const QString & user,
                          const QString & password,
                          const QString & api_key,
			  unsigned int offline_cache_limit);
  QcGeoportailWmtsLicense(const QcGeoportailWmtsLicense & other);

  QcGeoportailWmtsLicense & operator=(const QcGeoportailWmtsLicense & other);

  inline const QString & user() const { return m_user; }
  inline const QString & password() const { return m_password; }
  inline const QString & api_key() const { return m_api_key; }
  inline unsigned int offline_cache_limit() const { return m_offline_cache_limit; }

  bool operator==(const QcGeoportailWmtsLicense & rhs) const;

 private:
  void load_json(const QString & json_path);
  void read_json(const QJsonObject & json);

 private:
  QString m_user;
  QString m_password;
  QString m_api_key;
  unsigned int m_offline_cache_limit;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_GEOPORTAIL_LICENSE_H__ */
