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

  int fabrice_id;

  {
    QVariantHash kwargs;

    kwargs.clear();
    kwargs["name"] = "fabrice";
    // Feature: Build a row from kwargs
    AuthorPtr fabrice(kwargs);
    // Feature: Set a field
    fabrice->set_birthdate(QDateTime::currentDateTime());

    kwargs.clear();
    kwargs["name"] = "john doe";
    AuthorPtr john(kwargs);

    // kwargs.clear();
    // kwargs["name"] = "computer";
    // Category computer(kwargs);

    // kwargs.clear();
    // kwargs["name"] = "science";
    // Category science(kwargs);

    kwargs.clear();
    kwargs["text"] = "bla bla1";
    BlogPtr blog1(kwargs);
    // Feature: Set a relation Blog * <-> 1 Author
    blog1.set_author(fabrice);
    // Feature: access a relation
    qInfo() << blog1 << "has author" << blog1->author();

    // Feature: cannot save row with undefined foreign keys
    database_schema.add_ptr(blog1);

    kwargs.clear();
    kwargs["text"] = "bla bla2";
    BlogPtr blog2(kwargs);
    blog2.set_author(fabrice);

    // Feature: append object to one-to-many
    // Fixme: author.blogs() << blog

    qInfo() << "\n\nAuthor -> Blogs";
    qInfo() << fabrice->exists_on_database() << fabrice;
    // Feature: List relation one-to-many
    for (const auto & blog : fabrice->blogs())
      qInfo() << blog->exists_on_database() << blog;

    // Feature: Save object and their relations recursively
    //          Set ids and foreign keys
    qInfo() << "\n\nInsert";
    database_schema.add_ptr(fabrice);
    database_schema.add_ptr(john, true);

    // Now objects are saved and all ids and foreign keys are set
    qInfo() << "\n\nSaved Author -> Blogs";
    qInfo() << fabrice->exists_on_database() << fabrice;
    for (const auto & blog : fabrice->blogs())
      qInfo() << blog->exists_on_database() << blog;

    fabrice_id = fabrice->id();

    qInfo() << "\n\nDestroy local objects";
  }

  {
    // Feature: Load object by id
    qInfo() << "\n\nReload by id";
    AuthorPtr reloaded_fabrice = database_schema.query_by_id<Author>(fabrice_id);
    qInfo() << reloaded_fabrice;
  }

  {
    // Feature: Load objects and their relations lazily
    // Fixme: iterator ?
    qInfo() << "\n\nLoad Authors";
    Author::PtrList authors = database_schema.query<Author>();
    for (const auto author : authors)
      qInfo() << author;
    // Fixme: load lazily author.blogs()
  }

  {
    // Feature: Load objects and their relations
    // Fixme: iterator ?
    qInfo() << "\n\nLoad Authors";
    Author::PtrList authors = database_schema.query<Author>(false);
    for (const auto author : authors) {
      qInfo() << author;
      for (const auto blog : author->Author::blogs())
        qInfo() << blog;
    }
  }

  {
    // Feature: Load object and their relations lazily
    qInfo() << "\n\nLoad Blogs";
    Blog::PtrList blogs = database_schema.query<Blog>();
    for (const auto blog : blogs) {
      AuthorPtr author = blog->author();
      qInfo() << blog << "\n" << author;
    }
  }

  {
    // Feature: Load object and their relations
    qInfo() << "\n\nLoad Blogs";
    Blog::PtrList blogs = database_schema.query<Blog>(false);
    for (const auto blog : blogs) {
      AuthorPtr author = blog->author();
      qInfo() << blog << "\n" << author;
    }
  }

  {
    // Feature: Update object and save
    qInfo() << "\n\nReload by id";
    AuthorPtr reloaded_fabrice = database_schema.query_by_id<Author>(fabrice_id);
    qInfo() << reloaded_fabrice << reloaded_fabrice->is_modified();
    reloaded_fabrice->set_birthdate(QDateTime::fromString("2017-01-01T12:00:00.000", Qt::ISODate));
    qInfo() << reloaded_fabrice << reloaded_fabrice->is_modified();
    qInfo() << reloaded_fabrice->to_variant_hash_sql(true);
    database_schema.update_ptr(reloaded_fabrice);
  }

  qInfo() << "\n\nDestroy remaining objects";
  // Feature: All objects are detroyed when reference counter is null
}

/***************************************************************************************************/

QTEST_MAIN(TestBlog)
#include "test_blog.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
