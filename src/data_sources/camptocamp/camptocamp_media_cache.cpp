/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "camptocamp_media_cache.h"
#include "alpine_toolkit.h"

#include <QFile>
#include <QtDebug>

/**************************************************************************************************/

C2cMediaCache::C2cMediaCache(const QString & path)
  : m_path(path)
{
  if (! m_path.exists()) {
    if (!m_path.mkpath(m_path.absolutePath())) {
      qWarning() << "Cannot create media cache directory" << m_path;
    }
  }
}

C2cMediaCache::~C2cMediaCache()
{}

QString
C2cMediaCache::media_path(const QString & media) const
{
  return m_path.absoluteFilePath(media);
}

void
C2cMediaCache::save_media(const QString & media, const QByteArray & data) const
{
  QFile media_file(media_path(media));
  if (!media_file.open(QIODevice::WriteOnly))
    qWarning() << "couldn't write to file" << media;
  media_file.write(data);
  qATInfo() << "Saved media" << media_file.fileName();
}

bool
C2cMediaCache::has_media(const QString & media) const
{
  return QFile(media_path(media)).exists();
}

QByteArray
C2cMediaCache::get_media(const QString & media) const
{
  QFile media_file(media_path(media));
  if (media_file.open(QIODevice::ReadOnly))
    return media_file.readAll();
  else {
    qWarning() << "couldn't read to file" << media;
    return QByteArray(); // Fixme:
  }
}
