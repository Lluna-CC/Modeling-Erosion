#ifndef VORONOI_H
#define VORONOI_H

#include <voro++.hh>
#include <iostream>
#include "heightfieldWall.h"
#include "celldecomposition.h"

class Voronoi {
public:

    static void heightfieldVoronoi(const HeightField *hf, CellDecomposition *cellDecomp);
    static void triangleSamplingVoronoi(std::vector<float>& v, std::vector<uint>& f, CellDecomposition* decomp, const HeightField *hf);
    static void toyVoronoi(const HeightField *hf, CellDecomposition *decomp);
};

#endif