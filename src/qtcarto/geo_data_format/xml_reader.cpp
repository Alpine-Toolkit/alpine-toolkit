/***************************************************************************************************
 **
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 **
 ***************************************************************************************************/

/**************************************************************************************************/

#include "xml_reader.h"
#include "qtcarto.h"

#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

bool
QcXmlStreamReader::read_match_start_element(const QString & _name)
{
  return (readNext() == QXmlStreamReader::StartElement
          and name() == _name);
}

bool
QcXmlStreamReader::read_match_end_element(const QString & _name)
{
  return (readNext() == QXmlStreamReader::EndElement
          and name() == _name);
}

bool
QcXmlStreamReader::match_start_element(const QString & _name)
{
  return (tokenType() == QXmlStreamReader::StartElement
          and name() == _name);
}

bool
QcXmlStreamReader::match_end_element(const QString & _name)
{
  return (tokenType() == QXmlStreamReader::EndElement
          and name() == _name);
}

bool
QcXmlStreamReader::read_match_empty()
{
  return (readNext() == QXmlStreamReader::Characters
          and isWhitespace());
}

bool
QcXmlStreamReader::match_empty()
{
  return (tokenType() == QXmlStreamReader::Characters
          and isWhitespace());
}

void
QcXmlStreamReader::read_until_start_of(const QString & _name)
{
  while (! (readNext() == QXmlStreamReader::StartElement
            and name() == _name))
    {}
}

void
QcXmlStreamReader::read_until_end_of(const QString & _name)
{
  while (! (readNext() == QXmlStreamReader::EndElement
            and name() == _name))
    {}
}

void
QcXmlStreamReader::read_until_empty()
{
  while (readNext() == QXmlStreamReader::Characters
         and isWhitespace())
    {}
}

QDateTime
QcXmlStreamReader::read_date()
{
  QString s = readElementText();
  return QDateTime::fromString(s, Qt::ISODate);
}

int
QcXmlStreamReader::read_int()
{
  return readElementText().toInt();
}

double
QcXmlStreamReader::read_double()
{
  return readElementText().toDouble();
}

QString
QcXmlStreamReader::get_attribute(QString attribute)
{
  return attributes().value(attribute).toString();
}

int
QcXmlStreamReader::get_int_attribute(QString attribute)
{
  return get_attribute(attribute).toInt();
}

double
QcXmlStreamReader::get_double_attribute(QString attribute)
{
  return get_attribute(attribute).toDouble();
}


/**************************************************************************************************/

// QC_END_NAMESPACE
