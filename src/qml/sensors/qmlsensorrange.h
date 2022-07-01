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

#ifndef QTQMLSENSORRANGE_H
#define QTQMLSENSORRANGE_H

#include <QObject>

// QT_BEGIN_NAMESPACE

class QTQmlSensorRange : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int minimum READ minimum)
    Q_PROPERTY(int maximum READ maximum)
public:
    explicit QTQmlSensorRange(QObject *parent = 0);
    ~QTQmlSensorRange();

    int minimum() const;
    void setMinumum(int mini) { min = mini; }

    int maximum() const;
    void setMaximum(int maxi) { max = maxi; }

private:

    int min;
    int max;
};

class QTQmlSensorOutputRange : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal minimum READ minimum)
    Q_PROPERTY(qreal maximum READ maximum)
    Q_PROPERTY(qreal accuracy READ accuracy)
public:
    explicit QTQmlSensorOutputRange(QObject *parent = 0);
    ~QTQmlSensorOutputRange();

    qreal minimum() const;
    void setMinimum(int mini) { min = mini; }

    qreal maximum() const;
    void setMaximum(int maxi) { max = maxi; }

    qreal accuracy() const;
    void setAccuracy(int accu) { acc = accu; }

private:
    qreal min;
    qreal max;
    qreal acc;
};

// QT_END_NAMESPACE

#endif
