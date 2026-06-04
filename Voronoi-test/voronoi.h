#ifndef VORONOI_H
#define VORONOI_H

#include <voro++.hh>
#include <iostream>
#include "heightfieldWall.h"
#include "cellGraph.h"

class Voronoi {
public:

    static void heightfieldVoronoi(const HeightField *hf, CellGraph* graph);
    static void triangleSamplingVoronoi(const HeightField *hf, std::vector<float>& v, std::vector<uint>& f, CellGraph* graph);
    static void cellSamplingVoronoi(const HeightField *hf, CellGraph* graph);
    static void toyVoronoi(const HeightField *hf, CellGraph* graph);
    static void voronoiFromCentroids(const std::vector<Vector3>& centroids, const std::vector<bool>& exterior, CellGraph* graph, const HeightField* hf);
private:
    static const double offsetScale; 
    static const double areaRatioLimit;
    static const int areRatioWindow;
};

#endif