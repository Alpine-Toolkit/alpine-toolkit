/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
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
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include <iostream>

#include <QtTest/QtTest>

/**************************************************************************************************/

#include "wmts/tile_matrix_set.h"

/***************************************************************************************************/

class TestQcTileMatrixSet: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestQcTileMatrixSet::constructor()
{
  QcMercatorTileMatrixSet tile_matrix_set(20, 256);

  for (size_t i = 0; i < tile_matrix_set.number_of_levels(); i++) { // -Wsign-compare
    std::cout << "Level " << tile_matrix_set[i].level() << std::endl;
  }

  for (const QcTileMatrix & tile_matrix : tile_matrix_set.levels()) {
    std::cout << "Level " << tile_matrix.level() << std::endl;
  }
}

/***************************************************************************************************/

QTEST_MAIN(TestQcTileMatrixSet)
#include "test_tile_matrix_set.moc"
