/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) None Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
****************************************************************************/

#include "qmlsensorrange.h"
#include "alpine_toolkit.h"

QTQmlSensorRange::QTQmlSensorRange(QObject *parent)
    : QObject(parent),
      min(0),
      max(0)
{
}

QTQmlSensorRange::~QTQmlSensorRange()
{
}

int QTQmlSensorRange::minimum() const
{
    return min;
}

int QTQmlSensorRange::maximum() const
{
    return max;
}

QTQmlSensorOutputRange::QTQmlSensorOutputRange(QObject *parent)
    : QObject(parent),
      min(0),
      max(0),
      acc(0)
{
}

QTQmlSensorOutputRange::~QTQmlSensorOutputRange()
{
}

qreal QTQmlSensorOutputRange::minimum() const
{
    return min;
}

qreal QTQmlSensorOutputRange::maximum() const
{
    return max;
}

qreal QTQmlSensorOutputRange::accuracy() const
{
    return acc;
}
