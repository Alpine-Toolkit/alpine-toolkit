/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include <QtTest/QtTest>

/**************************************************************************************************/

#include "orm/database.h"
#include "orm/database_query.h"
#include "orm/database_table.h"

/***************************************************************************************************/

class TestQuery: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
  void check_sql(const QcSqlExpressionPtr & expression, const QString & sql_query);
  void check_sql(const QoSqlQuery & query, const QString & sql_query);
};

void
TestQuery::check_sql(const QcSqlExpressionPtr & expression, const QString & sql_query_truth)
{
  QString sql_query = expression->to_sql(SqlFlavour::ANSI);
  qInfo().noquote() << sql_query; // << sql_query_truth;
  QVERIFY(sql_query == sql_query_truth);
}

void
TestQuery::check_sql(const QoSqlQuery & query, const QString & sql_query_truth)
{
  QString sql_query = query.to_sql();
  if (sql_query_truth.isEmpty())
    QVERIFY(sql_query.isEmpty());
  else {
    qInfo().noquote() << sql_query; // << sql_query_truth;
    QVERIFY(sql_query == sql_query_truth);
  }
}

void TestQuery::constructor()
{
  QoSqlField field1("field1");
  QoSqlField field2("field2");
  QoSqlField field3("field3");

  check_sql(field1 == 1, "field1 = 1");
  check_sql(field1 != 1, "field1 != 1");
  check_sql(field1 < 1, "field1 < 1");
  check_sql(field1 > 1, "field1 > 1");
  check_sql(field1 <= 1, "field1 <= 1");
  check_sql(field1 >= 1, "field1 >= 1");

  // check_sql(not field1 == 1, "(NOT field1 = 1)");
  check_sql(Not(field1 == 1), "(NOT field1 = 1)");
  check_sql(field1 == 1 and field2 == 2, "(field1 = 1 AND field2 = 2)");
  check_sql(field1 == 1 or field2 == 2, "(field1 = 1 OR field2 = 2)");
  check_sql((field1 == 1 and field2 == 2) or field3 == 3,
            "((field1 = 1 AND field2 = 2) OR field3 = 3)");

  QoDatabase database; // Flavour is ANSI
  QoDatabaseTable table(&database, "table");

  check_sql(table.sql_query(), "");

  check_sql(table.sql_query().all(), "SELECT * FROM table;");
  check_sql(table.sql_query().add_column(field1).all(), "SELECT field1 FROM table;");
  check_sql(table.sql_query().add_column(field1).add_column(field2).all().filter(field1 > 1),
            "SELECT field1, field2 FROM table WHERE field1 > 1;");
  check_sql(table.sql_query().add_column(field1).add_column(field2).all().filter((field1 > 1 and field1 < 10) or field2 > 2),
            "SELECT field1, field2 FROM table WHERE ((field1 > 1 AND field1 < 10) OR field2 > 2);");
  check_sql(table.sql_query().order_by(field1).all(),
            "SELECT * FROM table ORDER BY field1;");
  check_sql(table.sql_query().order_by(field1.desc()).all(),
            "SELECT * FROM table ORDER BY field1 DESC;");

  // Fixme: ->as
  check_sql(table.sql_query().add_column(Min(field1)->as("min_field1")).all(),
            "SELECT MIN(field1) AS min_field1 FROM table;");

  // Fixme: INSERT INTO table VALUES (?, ...);
  check_sql(table.sql_query().add_column(field1).insert(),
            "INSERT INTO table (field1) VALUES (?);");
  check_sql(table.sql_query().add_column(field1).add_column(field2).insert(),
            "INSERT INTO table (field1, field2) VALUES (?, ?);");

  check_sql(table.sql_query().add_column(field1).update().filter(field1 > 1),
            "UPDATE table SET field1 = ? WHERE field1 > 1;");
  check_sql(table.sql_query().add_column(field1).add_column(field2).update().filter(field1 > 1),
            "UPDATE table SET field1 = ?, field2 = ? WHERE field1 > 1;");

  check_sql(table.sql_query().delete_().filter(field1 > 1),
            "DELETE FROM table WHERE field1 > 1;");

  check_sql(table.sql_query().add_column(ST_AsBinary(field1)).all(),
            "SELECT ST_AsBinary(field1) FROM table;");
  check_sql(table.sql_query().add_column(field1).add_column(field2, ST_GeomFromWKB()).insert(),
            "INSERT INTO table (field1, field2) VALUES (?, ST_GeomFromWKB(?, 4326));");
}

/***************************************************************************************************/

QTEST_MAIN(TestQuery)
#include "test_query.moc"
