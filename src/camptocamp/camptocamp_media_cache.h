// -*- mode: c++ -*-

/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the QtCarto library.
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

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
