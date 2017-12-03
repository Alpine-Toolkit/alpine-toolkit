/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $ALPINE_TOOLKIT_END_LICENSE$
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
