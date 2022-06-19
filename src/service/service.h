// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __SERVICE_H__
#define __SERVICE_H__

/**************************************************************************************************/

#include <QTimer>

#include "rep_service_source.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class Service : public ServiceSource
{
  Q_OBJECT

public:
  Service(QObject * parent = nullptr);
  ~Service();

public slots:
  void ping() override;
  void start_timer() override;
  void stop_timer() override;
  void stop_service();

private slots:
  void timer_slot();

private:
  QTimer m_timer;
};

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __SERVICE_H__ */
