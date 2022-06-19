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

#ifndef __CAMPTOCAMP_MEDIA_CACHE_H__
#define __CAMPTOCAMP_MEDIA_CACHE_H__

/**************************************************************************************************/

#include <QDir>
#include <QString>

/**************************************************************************************************/

class C2cMediaCache
{
public:
  C2cMediaCache(const QString & path);
  ~C2cMediaCache();

  void save_media(const QString & media, const QByteArray & data) const;
  bool has_media(const QString & media) const;
  QByteArray get_media(const QString & media) const; // Fixme: * for error ?

private:
  QString media_path(const QString & media) const;

private:
  QDir m_path;
};

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_MEDIA_CACHE_H__ */
