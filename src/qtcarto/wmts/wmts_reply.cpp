/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "wmts_reply.h"
#include "qtcarto.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/*!
    \class QcWmtsReply
    \inmodule QtLocation
    \ingroup QtLocation-impl
    \since 5.6
    \internal

    \brief The QcWmtsReply class manages a tile fetch operation started
    by an instance of QGeoTiledManagerEngine.

    Instances of QcWmtsReply manage the state and results of these
    operations.

    The isFinished(), error() and errorString() methods provide information
    on whether the operation has completed and if it completed successfully.

    The finished() and error(QcWmtsReply::Error,QString)
    signals can be used to monitor the progress of the operation.

    It is possible that a newly created QcWmtsReply may be in a finished
    state, most commonly because an error has occurred. Since such an instance
    will never emit the finished() or
    error(QcWmtsReply::Error,QString) signals, it is
    important to check the result of isFinished() before making the connections
    to the signals.

    If the operation completes successfully the results are accessed by
    mapImageData() and mapImageFormat().
*/

/*!
    \enum QcWmtsReply::Error

    Describes an error which prevented the completion of the operation.

    \value NoError
        No error has occurred.
    \value CommunicationError
        An error occurred while communicating with the service provider.
    \value ParseError
        The response from the service provider was in an unrecognizable format
        supported by the service provider.
    \value UnknownError
        An error occurred which does not fit into any of the other categories.
*/

/*!
    Constructs a tiled map reply object based on \a request,  with parent \a parent.
*/
QcWmtsReply::QcWmtsReply(QNetworkReply * reply, const QcTileSpec & tile_spec)
  : QcNetworkReply(reply),
    m_tile_spec(tile_spec)
{}

/*!
  Destroys this tiled map reply object.
*/
QcWmtsReply::~QcWmtsReply()
{}

/**************************************************************************************************/

// #include "wmts_reply.moc"

// QC_END_NAMESPACE
