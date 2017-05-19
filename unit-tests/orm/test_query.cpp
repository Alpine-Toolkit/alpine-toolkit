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

#include <QtTest/QtTest>

/**************************************************************************************************/

#include "orm/database_query.h"

/***************************************************************************************************/

class TestQuery: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
  void check_sql(const QcSqlExpressionPtr & expression, const QString & sql_query);
  void check_sql(const QcSqlQuery & query, const QString & sql_query);
};

void
TestQuery::check_sql(const QcSqlExpressionPtr & expression, const QString & sql_query_truth)
{
  QString sql_query = expression->to_sql(SqlFlavour::ANSI);
  qInfo().noquote() << sql_query; // << sql_query_truth;
  QVERIFY(sql_query == sql_query_truth);
}

void
TestQuery::check_sql(const QcSqlQuery & query, const QString & sql_query_truth)
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
  QcSqlField field1("field1");
  QcSqlField field2("field2");
  QcSqlField field3("field3");

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

  check_sql(QcSqlQuery("table"), "");

  check_sql(QcSqlQuery("table").all(), "SELECT * FROM table;");
  check_sql(QcSqlQuery("table").add_column(field1).all(), "SELECT field1 FROM table;");
  check_sql(QcSqlQuery("table").add_column(field1).add_column(field2).all().filter(field1 > 1),
            "SELECT field1, field2 FROM table WHERE field1 > 1;");
  check_sql(QcSqlQuery("table").add_column(field1).add_column(field2).all().filter(field1 > 1 and field1 < 10 or field2 > 2),
            "SELECT field1, field2 FROM table WHERE ((field1 > 1 AND field1 < 10) OR field2 > 2);");
  check_sql(QcSqlQuery("table").order_by(field1).all(),
            "SELECT * FROM table ORDER BY field1;");
  check_sql(QcSqlQuery("table").order_by(field1.desc()).all(),
            "SELECT * FROM table ORDER BY field1 DESC;");

  check_sql(QcSqlQuery("table").delete_().filter(field1 > 1),
            "DELETE FROM table WHERE field1 > 1;");

  // INSERT
  // UPDATE
}

/***************************************************************************************************/

QTEST_MAIN(TestQuery)
#include "test_query.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
