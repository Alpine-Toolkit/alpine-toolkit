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

#ifndef __QC_PATH_PROPERTY_H__
#define __QC_PATH_PROPERTY_H__

/**************************************************************************************************/

#include <QObject>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QcPathProperty : public QObject
{
  Q_OBJECT
  // FIXME: CONSTANT
  Q_PROPERTY(double length READ length WRITE set_length NOTIFY length_changed)
  Q_PROPERTY(double area READ area WRITE set_area NOTIFY area_changed)

public:
  QcPathProperty(QObject * parent = nullptr);
  QcPathProperty(const QcPathProperty & other, QObject * parent = nullptr);
  ~QcPathProperty();

  QcPathProperty & operator=(const QcPathProperty & other);

  double length() const { return m_length; }
  void set_length(double length);

  double area() const { return m_area; }
  void set_area(double area);

signals:
  void length_changed();
  void area_changed();

private:
  double m_length;
  double m_area;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

Q_DECLARE_METATYPE(QcPathProperty)

/**************************************************************************************************/

#endif /* __QC_PATH_PROPERTY_H__ */
