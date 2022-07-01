/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
