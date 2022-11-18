// -*- mode: c++ -*-

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

#ifndef __QC_NETWORK_REPLY_H__
#define __QC_NETWORK_REPLY_H__

/**************************************************************************************************/

#include "qtcarto_global.h"

#include <QNetworkReply>
#include <QObject>
#include <QPointer>
#include <QString>

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

// was QcNetworkReply

class QC_EXPORT QcNetworkFuture : public QObject
{
  Q_OBJECT

 public:
  enum Error { // Fixme: check
    NoError,
    CommunicationError,
    ParseError,
    UnknownError
  };

 public:
  QcNetworkFuture();
  QcNetworkFuture(Error error, const QString & error_string);
  virtual ~QcNetworkFuture();

  /*! Return true if the operation completed successfully or
    encountered an error which cause the operation to come to a halt.
  */
  bool is_finished() const { return m_is_finished; }

  /*! Returns the error state of this reply.

    If the result is QcNetworkFuture::NoError then no error has occurred.
  */
  Error error() const { return m_error; }
  /*! Returns the textual representation of the error state of this reply.

    If no error has occurred this will return an empty string.  It is
    possible that an error occurred which has no associated textual
    representation, in which case this will also return an empty
    string.

    To determine whether an error has occurred, check to see if
    QcNetworkFuture::error() is equal to QcNetworkFuture::NoError.
  */
  QString error_string() const { return m_error_string; }

  //! Returns whether the reply is coming from a cache.
  bool is_cached() const { return m_is_cached; }

  virtual void abort();

 signals:
  void finished();
  void error(Error error, const QString & error_string = QString());

 protected:
  void set_error(Error error, const QString & error_string);
  void set_finished(bool finished);

  //! Sets whether the reply is coming from a cache to \a cached.
  void set_cached(bool cached) { m_is_cached = cached; }

 private:
  Q_DISABLE_COPY(QcNetworkFuture);

 private:
  Error m_error;
  QString m_error_string;
  bool m_is_finished;
  bool m_is_cached; // Fixme: purpose ?
};

/**************************************************************************************************/

class QcNetworkReply : public QcNetworkFuture
{
  Q_OBJECT

public:
  explicit QcNetworkReply(QNetworkReply * reply);
  ~QcNetworkReply();

  void abort() override;

  virtual void process_payload() = 0;

  QNetworkReply * network_reply() const { return m_reply; }

private slots:
  void network_reply_finished();
  void network_reply_error(QNetworkReply::NetworkError error);

private:
  void cleanup();

private:
  QPointer<QNetworkReply> m_reply;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_NETWORK_REPLY_H__ */
