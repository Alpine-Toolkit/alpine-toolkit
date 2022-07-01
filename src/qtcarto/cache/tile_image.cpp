/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "tile_image.h"
#include "qtcarto.h"

#include <QDir>
#include <QFile>

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QString
tile_spec_to_filename(const QcTileSpec & tile_spec, const QString & format, const QString & directory)
{
  QString filename = tile_spec.plugin(); // Fixme: litteral, arg
  filename += QStringLiteral("-");
  filename += QString::number(tile_spec.map_id());
  filename += QStringLiteral("-");
  filename += QString::number(tile_spec.level());
  filename += QStringLiteral("-");
  filename += QString::number(tile_spec.x());
  filename += QStringLiteral("-");
  filename += QString::number(tile_spec.y());
  filename += QStringLiteral(".");
  filename += format;

  return QDir(directory).filePath(filename);
}

QcTileSpec
filename_to_tile_spec(const QString & filename)
{
  QcTileSpec tile_spec;

  QStringList parts = filename.split('.');
  if (parts.length() != 2)
    return tile_spec;
  QString name = parts.at(0);

  QStringList fields = name.split('-');
  int length = fields.length();
  if (length != 5)
    return tile_spec;

  QList<int> numbers;
  bool ok = false;
  for (int i = 1; i < length; ++i) {
    ok = false;
    int value = fields.at(i).toInt(&ok);
    if (!ok)
      return tile_spec;
    numbers.append(value);
  }

  return QcTileSpec(fields.at(0),
		    numbers.at(0),
		    numbers.at(1),
		    numbers.at(2),
		    numbers.at(3));
}

/**************************************************************************************************/

void
write_tile_image(const QString & filename, const QByteArray & bytes)
{
  QFile file(filename);
  file.open(QIODevice::WriteOnly);
  file.write(bytes);
  file.close();
}

QByteArray
read_tile_image(const QString & filename)
{
  QFile file(filename);
  file.open(QIODevice::ReadOnly);
  // Fixme: efficient ?
  QByteArray data = file.readAll();
  file.close();
  return data;
}

/**************************************************************************************************/

// QC_END_NAMESPACE
