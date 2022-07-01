/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include <QDir>
#include <QtDebug>
#include <QtTest/QtTest>

/**************************************************************************************************/

#include "wmts/providers/geoportail/geoportail_license.h"

/***************************************************************************************************/

class TestQcGeoportailWmtsLicense: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestQcGeoportailWmtsLicense::constructor()
{
  QString json_path = QDir::homePath() + "/.local/share/alpine-toolkit/geoportail-license.json";
  QcGeoportailWmtsLicense geoportail_license(json_path);
  qInfo() << geoportail_license.user()
	  << geoportail_license.password()
	  << geoportail_license.api_key()
    	  << geoportail_license.offline_cache_limit();
}

/***************************************************************************************************/

QTEST_MAIN(TestQcGeoportailWmtsLicense)
#include "test_geoportail_license.moc"
