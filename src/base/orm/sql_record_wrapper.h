// -*- mode: c++ -*-
/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#ifndef __SQL_RECORD_WRAPPER_H__
#define __SQL_RECORD_WRAPPER_H__

/**************************************************************************************************/

#include <QBitArray>
#include <QByteArray>
#include <QDate>
#include <QDateTime>
#include <QEasingCurve>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QLine>
#include <QLineF>
#include <QLocale>
#include <QModelIndex>
#include <QPersistentModelIndex>
#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QRectF>
// #include <QRegExp> // Qt6::Core5Compat
#include <QRegularExpression>
#include <QSize>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QUrl>
#include <QUuid>
#include <QVariant>

/**************************************************************************************************/

/* Wrapper that implement to<Type>(int index) method
 *
 * Note: QSqlRecord use implicit sharing
 *
 */
class QoSqlRecordWrapper
{
public:
  /*
  QoSqlRecordWrapper(const QSqlRecord record)
    : m_record(record)
  {}
  */
  QoSqlRecordWrapper(const QSqlRecord & record)
    : m_record(record) // Fixme: simpler ?
  {}

  QoSqlRecordWrapper &
  operator=(const QSqlRecord record)
  {
    m_record = record;

    return *this;
  }

  QoSqlRecordWrapper &
  operator=(const QSqlRecord & record)
  {
    m_record = record;

    return *this;
  }

  QoSqlRecordWrapper &
  operator=(const QoSqlRecordWrapper & other)
  {
    if (this != &other) {
      m_record = other.m_record;
    }

    return *this;
  }

  const QSqlRecord & record() const { return m_record; }

  bool isEmpty() const { return m_record.isEmpty(); }
  bool isNotEmpty() const { return not isEmpty(); }

  QVariant value(int index = 0) const {
    return m_record.value(index);
  }

  QBitArray toBitArray(int index = 0) const {
    return value(index).toBitArray();
  }

  bool toBool(int index = 0) const {
    return value(index).toBool();
  }

  QByteArray toByteArray(int index = 0) const {
    return value(index).toByteArray();
  }

  QChar toChar(int index = 0) const {
    return value(index).toChar();
  }

  QDate toDate(int index = 0) const {
    return value(index).toDate();
  }

  QDateTime toDateTime(int index = 0) const {
    return value(index).toDateTime();
  }

  double toDouble(int index = 0) const {
    return value(index).toDouble();
  }

  QEasingCurve toEasingCurve(int index = 0) const {
    return value(index).toEasingCurve();
  }

  float toFloat(int index = 0) const {
    return value(index).toFloat();
  }

  QHash<QString, QVariant> toHash(int index = 0) const {
    return value(index).toHash();
  }

  int toInt(int index = 0) const {
    return value(index).toInt();
  }

  QJsonArray toJsonArray(int index = 0) const {
    return value(index).toJsonArray();
  }

  QJsonDocument toJsonDocument(int index = 0) const {
    return value(index).toJsonDocument();
  }

  QJsonObject toJsonObject(int index = 0) const {
    return value(index).toJsonObject();
  }

  QJsonValue toJsonValue(int index = 0) const {
    return value(index).toJsonValue();
  }

  QLine toLine(int index = 0) const {
    return value(index).toLine();
  }

  QLineF toLineF(int index = 0) const {
    return value(index).toLineF();
  }

  QList<QVariant> toList(int index = 0) const {
    return value(index).toList();
  }

  QLocale toLocale(int index = 0) const {
    return value(index).toLocale();
  }

  qlonglong toLongLong(int index = 0) const {
    return value(index).toLongLong();
  }

  QMap<QString, QVariant> toMap(int index = 0) const {
    return value(index).toMap();
  }

  QModelIndex toModelIndex(int index = 0) const {
    return value(index).toModelIndex();
  }

  QPersistentModelIndex toPersistentModelIndex(int index = 0) const {
    return value(index).toPersistentModelIndex();
  }

  QPoint toPoint(int index = 0) const {
    return value(index).toPoint();
  }

  QPointF toPointF(int index = 0) const {
    return value(index).toPointF();
  }

  qreal toReal(int index = 0) const {
    return value(index).toReal();
  }

  QRect toRect(int index = 0) const {
    return value(index).toRect();
  }

  QRectF toRectF(int index = 0) const {
    return value(index).toRectF();
  }

  // Fixme: Qt6
  /*
  QRegExp toRegExp(int index = 0) const {
    return value(index).toRegExp();
  }
  */

  QRegularExpression toRegularExpression(int index = 0) const {
    return value(index).toRegularExpression();
  }

  QSize toSize(int index = 0) const {
    return value(index).toSize();
  }

  QSizeF toSizeF(int index = 0) const {
    return value(index).toSizeF();
  }

  QString toString(int index = 0) const {
    return value(index).toString();
  }

  QStringList toStringList(int index = 0) const {
    return value(index).toStringList();
  }

  QTime toTime(int index = 0) const {
    return value(index).toTime();
  }

  uint toUInt(int index = 0) const {
    return value(index).toUInt();
  }

  qulonglong toULongLong(int index = 0) const {
    return value(index).toULongLong();
  }

  QUrl toUrl(int index = 0) const {
    return value(index).toUrl();
  }

  QUuid toUuid(int index = 0) const {
    return value(index).toUuid();
  }

private:
  QSqlRecord m_record;
};

/**************************************************************************************************/

class QoSqlQueryWrapper
{
public:
  QoSqlQueryWrapper(QSqlQuery query)
    // Fixme: Qt6
    // QSqlQuery is not meant to be copied. Use move construction instead.
    // used in src/settings/settings_database.cpp
    : m_query(query)
  {}
  QoSqlQueryWrapper(QSqlQuery & query)
    // Fixme: Qt6
    : m_query(query)
  {}

  QoSqlQueryWrapper &
  operator=(const QSqlQuery query)
  {
    // Fixme: Qt6
    m_query = query;

    return *this;
  }

  QoSqlQueryWrapper &
  operator=(const QSqlQuery & query)
  {
    // Fixme: Qt6
    m_query = query;

    return *this;
  }

  QoSqlQueryWrapper &
  operator=(const QoSqlQueryWrapper & other)
  {
    if (this != &other) {
      // Fixme: Qt6
      m_query = other.m_query;
    }

    return *this;
  }

  QSqlQuery & query() { return m_query; }

  QSqlRecord record() const { return m_query.record(); }

  bool isValid() const { return m_query.isValid(); }

  bool next() { return m_query.next(); }

  QVariant value(int index = 0) const {
    return m_query.value(index);
  }

  QBitArray toBitArray(int index = 0) const {
    return value(index).toBitArray();
  }

  bool toBool(int index = 0) const {
    return value(index).toBool();
  }

  QByteArray toByteArray(int index = 0) const {
    return value(index).toByteArray();
  }

  QChar toChar(int index = 0) const {
    return value(index).toChar();
  }

  QDate toDate(int index = 0) const {
    return value(index).toDate();
  }

  QDateTime toDateTime(int index = 0) const {
    return value(index).toDateTime();
  }

  double toDouble(int index = 0) const {
    return value(index).toDouble();
  }

  QEasingCurve toEasingCurve(int index = 0) const {
    return value(index).toEasingCurve();
  }

  float toFloat(int index = 0) const {
    return value(index).toFloat();
  }

  QHash<QString, QVariant> toHash(int index = 0) const {
    return value(index).toHash();
  }

  int toInt(int index = 0) const {
    return value(index).toInt();
  }

  QJsonArray toJsonArray(int index = 0) const {
    return value(index).toJsonArray();
  }

  QJsonDocument toJsonDocument(int index = 0) const {
    return value(index).toJsonDocument();
  }

  QJsonObject toJsonObject(int index = 0) const {
    return value(index).toJsonObject();
  }

  QJsonValue toJsonValue(int index = 0) const {
    return value(index).toJsonValue();
  }

  QLine toLine(int index = 0) const {
    return value(index).toLine();
  }

  QLineF toLineF(int index = 0) const {
    return value(index).toLineF();
  }

  QList<QVariant> toList(int index = 0) const {
    return value(index).toList();
  }

  QLocale toLocale(int index = 0) const {
    return value(index).toLocale();
  }

  qlonglong toLongLong(int index = 0) const {
    return value(index).toLongLong();
  }

  QMap<QString, QVariant> toMap(int index = 0) const {
    return value(index).toMap();
  }

  QModelIndex toModelIndex(int index = 0) const {
    return value(index).toModelIndex();
  }

  QPersistentModelIndex toPersistentModelIndex(int index = 0) const {
    return value(index).toPersistentModelIndex();
  }

  QPoint toPoint(int index = 0) const {
    return value(index).toPoint();
  }

  QPointF toPointF(int index = 0) const {
    return value(index).toPointF();
  }

  qreal toReal(int index = 0) const {
    return value(index).toReal();
  }

  QRect toRect(int index = 0) const {
    return value(index).toRect();
  }

  QRectF toRectF(int index = 0) const {
    return value(index).toRectF();
  }

  // Fixme: Qt6
  /*
  QRegExp toRegExp(int index = 0) const {
    return value(index).toRegExp();
  }
  */

  QRegularExpression toRegularExpression(int index = 0) const {
    return value(index).toRegularExpression();
  }

  QSize toSize(int index = 0) const {
    return value(index).toSize();
  }

  QSizeF toSizeF(int index = 0) const {
    return value(index).toSizeF();
  }

  QString toString(int index = 0) const {
    return value(index).toString();
  }

  QStringList toStringList(int index = 0) const {
    return value(index).toStringList();
  }

  QTime toTime(int index = 0) const {
    return value(index).toTime();
  }

  uint toUInt(int index = 0) const {
    return value(index).toUInt();
  }

  qulonglong toULongLong(int index = 0) const {
    return value(index).toULongLong();
  }

  QUrl toUrl(int index = 0) const {
    return value(index).toUrl();
  }

  QUuid toUuid(int index = 0) const {
    return value(index).toUuid();
  }

private:
  QSqlQuery m_query;
};

/**************************************************************************************************/

#endif /* __SQL_RECORD_WRAPPER_H__ */
