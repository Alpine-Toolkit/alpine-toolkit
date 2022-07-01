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

#ifndef QTQMLSENSOR_H
#define QTQMLSENSOR_H

#include <QQmlParserStatus>
#include <QQmlListProperty>
#include "qmlsensorrange.h"

// QT_BEGIN_NAMESPACE

class QSensor;
class QSensorReading;

class QTQmlSensorReading;

class QTQmlSensor : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_ENUMS(AxesOrientationMode)
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QString identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    Q_PROPERTY(bool connectedToBackend READ isConnectedToBackend NOTIFY connectedToBackendChanged)
    Q_PROPERTY(QQmlListProperty<QTQmlSensorRange> availableDataRates READ availableDataRates NOTIFY availableDataRatesChanged)
    Q_PROPERTY(int dataRate READ dataRate WRITE setDataRate NOTIFY dataRateChanged)
    Q_PROPERTY(QTQmlSensorReading* reading READ reading NOTIFY readingChanged)
    Q_PROPERTY(bool busy READ isBusy)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(QQmlListProperty<QTQmlSensorOutputRange> outputRanges READ outputRanges NOTIFY outputRangesChanged)
    Q_PROPERTY(int outputRange READ outputRange WRITE setOutputRange NOTIFY outputRangeChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    Q_PROPERTY(int error READ error NOTIFY errorChanged)
    Q_PROPERTY(bool alwaysOn READ isAlwaysOn WRITE setAlwaysOn NOTIFY alwaysOnChanged)
    Q_PROPERTY(bool skipDuplicates READ skipDuplicates WRITE setSkipDuplicates NOTIFY skipDuplicatesChanged REVISION 1)
    Q_PROPERTY(AxesOrientationMode axesOrientationMode READ axesOrientationMode WRITE setAxesOrientationMode NOTIFY axesOrientationModeChanged REVISION 1)
    Q_PROPERTY(int currentOrientation READ currentOrientation NOTIFY currentOrientationChanged REVISION 1)
    Q_PROPERTY(int userOrientation READ userOrientation WRITE setUserOrientation NOTIFY userOrientationChanged REVISION 1)
    Q_PROPERTY(int maxBufferSize READ maxBufferSize NOTIFY maxBufferSizeChanged REVISION 1)
    Q_PROPERTY(int efficientBufferSize READ efficientBufferSize NOTIFY efficientBufferSizeChanged REVISION 1)
    Q_PROPERTY(int bufferSize READ bufferSize WRITE setBufferSize NOTIFY bufferSizeChanged REVISION 1)

public:
    // Keep in sync with QSensor::AxesOrientationMode
    enum AxesOrientationMode {
        FixedOrientation,
        AutomaticOrientation,
        UserOrientation
    };

    explicit QTQmlSensor(QObject *parent = 0);
    ~QTQmlSensor();

    QString identifier() const;
    void setIdentifier(const QString &identifier);

    QString type() const;

    bool isConnectedToBackend() const;

    bool isBusy() const;

    void setActive(bool active);
    bool isActive() const;

    bool isAlwaysOn() const;
    void setAlwaysOn(bool alwaysOn);

    bool skipDuplicates() const;
    void setSkipDuplicates(bool skipDuplicates);

    QQmlListProperty<QTQmlSensorRange> availableDataRates() const;
    int dataRate() const;
    void setDataRate(int rate);

    QQmlListProperty<QTQmlSensorOutputRange> outputRanges() const;
    int outputRange() const;
    void setOutputRange(int index);

    QString description() const;
    int error() const;

    QTQmlSensorReading *reading() const;

    AxesOrientationMode axesOrientationMode() const;
    void setAxesOrientationMode(AxesOrientationMode axesOrientationMode);

    int currentOrientation() const;

    int userOrientation() const;
    void setUserOrientation(int userOrientation);

    int maxBufferSize() const;

    int efficientBufferSize() const;

    int bufferSize() const;
    void setBufferSize(int bufferSize);

public Q_SLOTS:
    bool start();
    void stop();

Q_SIGNALS:
    void identifierChanged();
    void typeChanged();
    void connectedToBackendChanged();
    void availableDataRatesChanged();
    void dataRateChanged();
    void readingChanged();
    void activeChanged();
    void outputRangesChanged();
    void outputRangeChanged();
    void descriptionChanged();
    void errorChanged();
    void alwaysOnChanged();
    Q_REVISION(1) void skipDuplicatesChanged(bool skipDuplicates);
    Q_REVISION(1) void axesOrientationModeChanged(AxesOrientationMode axesOrientationMode);
    Q_REVISION(1) void currentOrientationChanged(int currentOrientation);
    Q_REVISION(1) void userOrientationChanged(int userOrientation);
    Q_REVISION(1) void maxBufferSizeChanged(int maxBufferSize);
    Q_REVISION(1) void efficientBufferSizeChanged(int efficientBufferSize);
    Q_REVISION(1) void bufferSizeChanged(int bufferSize);

protected:
    virtual QSensor *sensor() const = 0;
    virtual QTQmlSensorReading *createReading() const = 0;

private Q_SLOTS:
    void updateReading();

protected Q_SLOTS:
    void componentComplete();

private:
    void classBegin();
    virtual void _update();
    bool m_parsed;
    bool m_active;
    QString m_identifier;
    QTQmlSensorReading *m_reading;
};

class QTQmlSensorReading : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint64 timestamp READ timestamp NOTIFY timestampChanged)
public:
    explicit QTQmlSensorReading(QSensor *sensor);
    ~QTQmlSensorReading();

    quint64 timestamp() const;
    void update();

Q_SIGNALS:
    void timestampChanged();

private:
    virtual QSensorReading *reading() const = 0;
    virtual void readingUpdate() = 0;
    quint64 m_timestamp;
};

// QT_END_NAMESPACE

#endif
