/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
** Copyright (C) 2015 The Qt Company Ltd.
**
***************************************************************************************************/

/**************************************************************************************************/

#include "network_reply.h"
#include "qtcarto.h"

#include <QtGlobal>
#include <QDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/*!
    \class QcNetworkFuture

    \brief The QcNetworkFuture class manages a ...

    Instances of QcNetworkFuture manage the state and results of these
    operations.

    The isFinished(), error() and errorString() methods provide information
    on whether the operation has completed and if it completed successfully.

    The finished() and error(QcNetworkFuture::Error,QString)
    signals can be used to monitor the progress of the operation.

    It is possible that a newly created QcNetworkFuture may be in a finished
    state, most commonly because an error has occurred. Since such an instance
    will never emit the finished() or
    error(QcNetworkFuture::Error,QString) signals, it is
    important to check the result of isFinished() before making the connections
    to the signals.
*/

/*!
    \enum QcNetworkFuture::Error

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
QcNetworkFuture::QcNetworkFuture()
  : QObject(),
    m_error(QcNetworkFuture::NoError),
    m_is_finished(false),
    m_is_cached(false)
{}

/*!
  Constructs a tiled map reply object with a given \a error and \a errorString and the specified \a parent.
*/
QcNetworkFuture::QcNetworkFuture(Error error, const QString & error_string)
  : QObject(),
    m_error(error),
    m_error_string(error_string),
    m_is_finished(true),
    m_is_cached(false)
{}

/*!
  Destroys this tiled map reply object.
*/
QcNetworkFuture::~QcNetworkFuture()
{}

/*!
  Sets whether or not this reply has finished to \a finished.

  If \a finished is true, this will cause the finished() signal to be
  emitted.

  If the operation completed successfully,
  QcNetworkFuture::setMapImageData() should be called before this
  function. If an error occurred, QcNetworkFuture::setError() should be used
  instead.
*/
void
QcNetworkFuture::set_finished(bool finished)
{
  m_is_finished = finished;
  if (m_is_finished)
    emit this->finished();
}

/*!
  Sets the error state of this reply to \a error and the textual
  representation of the error to \a errorString.

  This will also cause error() and finished() signals to be emitted, in that
  order.
*/
void
QcNetworkFuture::set_error(QcNetworkFuture::Error error, const QString & error_string)
{
  m_error = error;
  m_error_string = error_string;
  emit this->error(error, error_string);
  set_finished(true);
}

/*!
  Cancels the operation immediately.

  This will do nothing if the reply is finished.
*/
void
QcNetworkFuture::abort()
{
  if (!is_finished())
    set_finished(true);
}

/**************************************************************************************************/

QcNetworkReply::QcNetworkReply(QNetworkReply * reply)
  : QcNetworkFuture(),
    m_reply(reply)
{
  connect(m_reply, SIGNAL(finished()),
          this, SLOT(network_reply_finished()));

  connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
          this, SLOT(network_reply_error(QNetworkReply::NetworkError)));

  // connect(m_reply, &QNetworkReply::finished,
  //         this, &QcNetworkReply::network_reply_finished);

  // qOverload<QNetworkReply::NetworkError>(&QNetworkReply::error)
  // connect(m_reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
  //         this, &QcNetworkReply::network_reply_error);
}

QcNetworkReply::~QcNetworkReply()
{
  if (m_reply) {
    m_reply->deleteLater();
    m_reply = nullptr;
  }
}

void
QcNetworkReply::abort()
{
  if (m_reply)
    m_reply->abort();
}

void
QcNetworkReply::cleanup()
{
  set_finished(true);
  m_reply->deleteLater();
  m_reply = nullptr;
}

// Handle a successful request : store image data
void
QcNetworkReply::network_reply_finished()
{
  if (!m_reply)
    return;

  if (m_reply->error() != QNetworkReply::NoError) // Fixme: when ?
    return;

  process_payload();

  cleanup();
}

// Handle an unsuccessful request : set error message
void
QcNetworkReply::network_reply_error(QNetworkReply::NetworkError error)
{
  if (!m_reply)
    return;

  if (error != QNetworkReply::OperationCanceledError)
    set_error(QcNetworkReply::CommunicationError, m_reply->errorString());

  cleanup();
}

/**************************************************************************************************/

// #include "network_reply.moc"

// QC_END_NAMESPACE
