####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

output = ('unit-tests', 'orm', 'blog')

####################################################################################################

from CodeGenerator.Orm import SchemaRepository, Schema, Field, ForeignKey, RelationShip
from CodeGenerator.Orm.StandardType import Integer, String, DateTime

####################################################################################################

# class Sex(enum.Enum):
#     male = 1
#     female = 2

####################################################################################################

class Author(Schema):

    __table_name__ = 'authors'

    __order__ = ( # Fixme: without => rowid is not @0
        'id',
        'name',
        'birthdate',
        # 'sex',
        )

    id = Field(Integer, primary_key=True)
    # id = Field(String, primary_key=True)
    name = Field(String)
    birthdate = Field(DateTime)
    # sex = Field(Enum(Sex))

    blogs = RelationShip('Blog', order_by='Blog.id', back_populates='author') # one-to-many RelationShip

####################################################################################################

# category_blog_table = Table('category_blog', Base.metadata,
#                             Field('left_id', Integer, ForeignKey('categories.id')),
#                             Field('right_id', Integer, ForeignKey('blogs.id')))

####################################################################################################

class Category(Schema):

    __table_name__ = 'categories'

    __order__ = (
        'id',
        'name',
        'description',
        )

    id = Field(Integer, primary_key=True)
    name = Field(String)
    description = Field(String)

    # blogs = RelationShip('Blog',
    #                      secondary=category_blog_table,
    #                      back_populates='categories')

####################################################################################################

class Blog(Schema):

    __table_name__ = 'blogs'

    __order__ = (
        'id',
        'text',
        'date',
        'author_id',
        )

    id = Field(Integer, primary_key=True)
    text = Field(String)
    date = Field(DateTime)
    author_id = Field(Integer, ForeignKey('authors.id'))

    author = RelationShip('Author', back_populates='blogs') # many-to-one RelationShip
    # comments = RelationShip('Comment', order_by='Comment.id', back_populates='blog') # one-to-many RelationShip
    # categories = RelationShip('Category',
    #                           secondary=category_blog_table,
    #                           back_populates='blogs')

####################################################################################################

class Comment(Schema):

    __table_name__ = 'comments'

    __order__ = (
        'id',
        'text',
        'date',
        'blog_id',
        )

    id = Field(Integer, primary_key=True)
    text = Field(String)
    date = Field(DateTime)
    blog_id = Field(Integer, ForeignKey('blogs.id'))

    # blog = RelationShip('Blog', back_populates='comments') # many-to-one RelationShip

####################################################################################################

class BlogApplicationSchema(SchemaRepository):

    __schemas__ = (
        Author,
        Category,
        Blog,
        Comment,
    )
