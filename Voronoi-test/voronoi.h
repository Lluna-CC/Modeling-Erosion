#ifndef VORONOI_H
#define VORONOI_H

#include <voro++.hh>
#include <iostream>
#include "heightfieldWall.h"
#include "celldecomposition.h"

class Voronoi {
public:

    static void heightfieldVoronoi(HeightField *hf, CellDecomposition *cellDecomp);
    static void tethraedronTest();
    static void randomPointsTest();
};

#endif