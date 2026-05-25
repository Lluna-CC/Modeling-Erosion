#ifndef VORONOI_H
#define VORONOI_H

#include <voro++.hh>
#include <iostream>
#include "heightfieldWall.h"
#include "cellGraph.h"

class Voronoi {
public:

    static void heightfieldVoronoi(const HeightField *hf, CellGraph* graph);
    static void triangleSamplingVoronoi(std::vector<float>& v, std::vector<uint>& f, CellGraph* graph, const HeightField *hf);
    static void toyVoronoi(const HeightField *hf, CellGraph* graph);
    static void voronoiFromCentroids(const std::vector<Vector3> centroids, CellGraph* graph, const HeightField* hf);
};

#endif