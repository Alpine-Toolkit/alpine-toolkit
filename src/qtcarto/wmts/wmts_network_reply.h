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

#ifndef __QC_WMTS_NETWORK_REPLY_H__
#define __QC_WMTS_NETWORK_REPLY_H__

/**************************************************************************************************/

#include "wmts/wmts_reply.h"

#include <QNetworkReply>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

// Fixme: clarify API
//        why ??? QcWmtsNetworkReply > QcWmtsReply  >> QcNetworkReply > QcNetworkFuture
//        Merge QcWmtsNetworkReply in QcWmtsReply
// It just implements process_payload

/// The QcWmtsNetworkReply class manages a tile fetch operation started by the tile fetcher.
class QcWmtsNetworkReply : public QcWmtsReply
{
  Q_OBJECT

public:
  explicit QcWmtsNetworkReply(QNetworkReply * reply, const QcTileSpec & spec, const QString & format);
  ~QcWmtsNetworkReply();

  void process_payload();

private:
  QString m_format;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_WMTS_NETWORK_REPLY_H__ */
