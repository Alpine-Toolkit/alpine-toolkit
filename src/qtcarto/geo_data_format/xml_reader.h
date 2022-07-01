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

#ifndef __QC_QcXmlStreamReader_H__
#define __QC_QcXmlStreamReader_H__

/**************************************************************************************************/

#include <QDateTime>
#include <QIODevice>
#include <QString>
#include <QXmlStreamReader>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QcXmlStreamReader : public QXmlStreamReader
{
public:
  bool read_match_start_element(const QString & name);
  bool read_match_end_element(const QString & name);
  bool match_start_element(const QString & name);
  bool match_end_element(const QString & name);
  bool read_match_empty();
  bool match_empty();

  void read_until_start_of(const QString & name);
  void read_until_end_of(const QString & name);
  void read_until_empty();

  QDateTime read_date();
  int read_int();
  double read_double();

  QString get_attribute(QString attribute);
  int get_int_attribute(QString attribute);
  double get_double_attribute(QString attribute);
};

// QC_END_NAMESPACE

#endif /* __QC_QcXmlStreamReader_H__ */
