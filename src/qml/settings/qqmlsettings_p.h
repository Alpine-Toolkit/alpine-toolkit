/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) None Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
****************************************************************************/

#ifndef QQMLSETTINGS_P_H
#define QQMLSETTINGS_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtQml/qqml.h>
#include <QtCore/qobject.h>
#include <QtCore/qscopedpointer.h>
#include <QtQml/qqmlparserstatus.h>

QT_BEGIN_NAMESPACE

class QQmlSettingsPrivate;

class QQmlSettings : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QString category READ category WRITE setCategory FINAL)

public:
    explicit QQmlSettings(QObject *parent = 0);
    ~QQmlSettings();

    QString category() const;
    void setCategory(const QString &category);

protected:
    void timerEvent(QTimerEvent *event) override;

    void classBegin() override;
    void componentComplete() override;

private:
    Q_DISABLE_COPY(QQmlSettings)
    Q_DECLARE_PRIVATE(QQmlSettings)
    QScopedPointer<QQmlSettingsPrivate> d_ptr;
    Q_PRIVATE_SLOT(d_func(), void _q_propertyChanged())
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQmlSettings)

#endif // QQMLSETTINGS_P_H
