#include "multiResolutionGraph.h"
#include <random>

void MultiResolutionGraph::multiLevelVoronoiDecomposition(std::vector<float>& v, std::vector<uint>& f, const HeightField *hf) {
    levels.resize(2);
    Voronoi::triangleSamplingVoronoi(v,f,&levels[0],hf);

    int newSize = levels[0].getNumCells()/10;
    if (newSize == 0) return;

    std::vector<Vector3> centroids(newSize);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, newSize - 1);

    int first = dist(rng);
    centroids[0] = levels[0].getCells()[first].centroid;

    std::vector<double> minDistances(levels[0].getNumCells());
    double max = -1; 
    int argmax;
    
    for (int i = 1; i < newSize; ++i) {
        
        for (int j = 0; j < minDistances.size(); ++j) {
            Vector3 centr = levels[0].getCells()[j].centroid;
            double dist = Norm(centr - centroids[i - 1]);
            if (dist < minDistances[j]) minDistances[j] = dist;
            if (minDistances[j] > max) {
                max = minDistances[j];
                argmax = j;
            }
        }
        
        centroids[i] =  levels[0].getCells()[argmax].centroid;
        max = -1;
    }

    Voronoi::voronoiFromCentroids(centroids, &levels[1], hf);
    std::cout << "second level completed" << std::endl;

}

void MultiResolutionGraph::computeBounds() {
    if (levels.size() == 0) return;
    levels[0].computeBounds();
}

void MultiResolutionGraph::clear() {
    for (int k = 0; k < levels.size(); ++k) levels[k].clear();
}

void MultiResolutionGraph::updateExternalLinks() {
    if (levels.size() == 0) return;
    else levels[0].updateExternalLinks();
}