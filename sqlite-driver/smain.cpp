// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <qsqldriverplugin.h>
#include <qstringlist.h>
#include "qsql_sqlite_at_p.h"

QT_BEGIN_NAMESPACE

using namespace Qt::StringLiterals;

class QSQLiteATDriverPlugin : public QSqlDriverPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QSqlDriverFactoryInterface" FILE "sqlite-at.json")

public:
    QSQLiteATDriverPlugin();

    QSqlDriver* create(const QString &) override;
};

QSQLiteATDriverPlugin::QSQLiteATDriverPlugin()
    : QSqlDriverPlugin()
{
}

QSqlDriver* QSQLiteATDriverPlugin::create(const QString &name)
{
    if (name == "QSQLITE-AT"_L1) {
        QSQLiteATDriver* driver = new QSQLiteATDriver();
        return driver;
    }
    return 0;
}

QT_END_NAMESPACE

#include "smain.moc"
