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

#include <QtTest/QtTest>

/**************************************************************************************************/

#include "blog_database.h"

#include <QFile>
#include <QJsonDocument>
#include <QtDebug>

/***************************************************************************************************/

class TestBlog: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestBlog::constructor()
{
  QString sqlite_path("blog.sqlite"); // Fixme:
  QFile file(sqlite_path);
  if (file.exists())
    file.remove();
  BlogDatabase blog_database(sqlite_path);
  BlogDatabase::DatabaseSchema & database_schema = blog_database.schema();

  QVariantHash kwargs;

  kwargs.clear();
  kwargs["name"] = "fabrice";
  // QSharedPointer<Author> fabrice(new Author(kwargs)); // else delete fails (Fixme: stack vs QSharedPointer)
  AuthorPtr fabrice(kwargs);
  fabrice->set_birthdate(QDateTime::currentDateTime());
  // Author fabrice(kwargs);
  // fabrice.set_name("fabrice");

  kwargs.clear();
  kwargs["name"] = "john doe";
  // QSharedPointer<Author> john(new Author(kwargs));
  AuthorPtr john(kwargs);
  // Author john(kwargs);

  // kwargs.clear();
  // kwargs["name"] = "computer";
  // Category computer(kwargs);

  // kwargs.clear();
  // kwargs["name"] = "science";
  // Category science(kwargs);

  kwargs.clear();
  kwargs["text"] = "bla bla";
  BlogPtr blog1(kwargs);
  // QSharedPointer<Blog> blog1(new Blog(kwargs));
  // blog1->set_author(fabrice); // Fixme: pass ref ???
  blog1.set_author(fabrice);

  database_schema.add(fabrice.ptr()); // Fixme: recursively add
  database_schema.add(john.ptr());
}

/***************************************************************************************************/

QTEST_MAIN(TestBlog)
#include "test_blog.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
