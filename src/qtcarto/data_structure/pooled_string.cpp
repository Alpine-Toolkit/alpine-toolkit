/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "pooled_string.h"
#include "qtcarto.h"

#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

QMutex QcPooledString::m_mutex;
QcPooledString::IdType QcPooledString::m_last_id = 1;
QMap<QcPooledString::IdType, QcPooledString::QcPooledStringData *> QcPooledString::m_id_map;
QMap<QString, QcPooledString::QcPooledStringData *> QcPooledString::m_string_map;

QString QcPooledString::UndefinedString;

/**************************************************************************************************/

bool
QcPooledString::has_string(const QString & string)
{
  m_mutex.lock();
  bool rc = m_string_map.contains(string);
  m_mutex.unlock();
  return rc;
}

/**************************************************************************************************/

QcPooledString::QcPooledString()
  : m_data(nullptr)
{}

QcPooledString::QcPooledString(const QString & string)
{
  m_mutex.lock();
  if (m_string_map.contains(string)) {
    m_data = m_string_map[string];
    // if (is_defined())
    increment_ref_counter(m_data);
  } else {
    IdType id = m_last_id++;
    m_data = new QcPooledStringData(id, string);
    m_id_map.insert(id, m_data);
    m_string_map.insert(string, m_data);
    qQCDebug() << "Added" << string << m_id_map.keys() << m_string_map.keys();
  }
  m_mutex.unlock();
}

QcPooledString::QcPooledString(const QcPooledString & other)
{
  m_mutex.lock();
  m_data = other.m_data;
  if (is_defined())
    increment_ref_counter(m_data);
  m_mutex.unlock();
}

QcPooledString::~QcPooledString()
{
  qQCDebug() << "Delete" << id();
  if (is_defined()) {
    m_mutex.lock();
    uint counter = reference_counter();
    if (counter > 1)
      decrement_ref_counter(m_data);
    else {
      m_id_map.remove(id());
      m_string_map.remove(string());
      qQCDebug() << "Remove string" << string() << m_id_map.keys() << m_string_map.keys();
      delete m_data;
    }
    m_mutex.unlock();
  }
}

QcPooledString &
QcPooledString::operator=(const QcPooledString & other)
{
  if (this != &other) {
    m_mutex.lock();
    m_data = other.m_data;
    if (is_defined())
      increment_ref_counter(m_data);
    m_mutex.unlock();
  }

  return *this;
}

/**************************************************************************************************/

// QC_END_NAMESPACE
