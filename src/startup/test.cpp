/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
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
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QtDebug>

/**************************************************************************************************/

#include "startup.h"

/**************************************************************************************************/

void
run_before_event_loop(const QDir & application_user_directory)
{
  QFile output_file(application_user_directory.filePath("out.txt"));
  if (!output_file.open(QIODevice::WriteOnly | QIODevice::Text))
    qWarning() << "couldn't write to file";
  QTextStream out(&output_file);
  out << "The magic number is: " << 49 << "\n";

  QFile input_file("assets:/file1.txt");
  if (!input_file.open(QIODevice::ReadOnly | QIODevice::Text))
    qWarning() << "couldn't read to file";
  while (!input_file.atEnd()) {
    QByteArray line = input_file.readLine();
    qInfo() << line;
  }
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
