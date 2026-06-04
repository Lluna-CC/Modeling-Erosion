#include "multiResolutionGraph.h"
#include <random>
#include<float.h>

void MultiResolutionGraph::multiLevelVoronoiDecomposition(std::vector<float>& v, std::vector<uint>& f, const HeightField *hf, int scale) {
    
    
    levels.resize(nLevels);
    upperLevel.resize(nLevels - 1);
    lowerLevel.resize(nLevels - 1);

    
    Voronoi::cellSamplingVoronoi(hf,&levels[0]);

    int newSize = levels[0].getNumCells()/scale;

    if (newSize == 0) return;
    upperLevel[0].resize(levels[0].getNumCells());
    lowerLevel[0].resize(newSize);

    std::vector<Vector3> centroids(newSize);
    std::vector<bool> exterior(newSize, true);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, newSize - 1);

    int first = dist(rng);
    centroids[0] = levels[0].getCells()[first].centroid;

    std::vector<double> minDistances(levels[0].getNumCells(), DBL_MAX);
    std::vector<int> closestCentroid(levels[0].getNumCells());
    double max = -1; 
    int argmax;
    
    for (int i = 1; i < newSize; ++i) {
        
        for (int j = 0; j < minDistances.size(); ++j) {
            Vector3 centr = levels[0].getCells()[j].centroid;
            double dist = Norm(centr - centroids[i - 1]);
            if (dist < minDistances[j]) {
                minDistances[j] = dist;
                closestCentroid[j] = i - 1;
            }
            if (minDistances[j] > max) {
                max = minDistances[j];
                argmax = j;
            }
        }
        
        centroids[i] =  levels[0].getCells()[argmax].centroid;
        max = -1;
    }

    for (int j = 0; j < minDistances.size(); ++j) {
        Vector3 centr = levels[0].getCells()[j].centroid;
        double dist = Norm(centr - centroids[newSize - 1]);
        if (dist < minDistances[j]) {
            minDistances[j] = dist;
            closestCentroid[j] = newSize - 1;
        }
        
        upperLevel[0][j] = closestCentroid[j];
        lowerLevel[0][closestCentroid[j]].push_back(j);
        if (levels[0].getCells()[j].state == SOLID) exterior[closestCentroid[j]] = false;
    }


    Voronoi::voronoiFromCentroids(centroids, exterior, &levels[1], hf);
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
    for (int l = 0; l < levels.size(); ++l) levels[l].updateExternalLinks();
}


void MultiResolutionGraph::removeLowerLevel(int l, int cell) {
    if (l < 1) return;
    std::vector<vorocell>& lowerCells = levels[l - 1].getCells();
    for (int i = 0; i < lowerLevel[l - 1][cell].size(); ++i) {
        int actCell = lowerLevel[l - 1][cell][i];
        lowerCells[actCell].state = AIR;
    }
}

void MultiResolutionGraph::updateLowerLevelCells(int l, int cell) {
    if (l < 1 || l > lowerLevel.size() + 1) return;
    std::vector<vorocell>& lowerCells = levels[l - 1].getCells();
    for (int i = 0; i < lowerLevel[l - 1][cell].size(); ++i) {
        int actCell = lowerLevel[l - 1][cell][i];
        if (lowerCells[actCell].state == AIR) continue;
        for (int k = 0; k < lowerCells[actCell].neighbors.size(); ++k) {
            if (lowerCells[actCell].neighbors[k] < 0 || lowerCells[lowerCells[actCell].neighbors[k]].state == AIR) {
                lowerCells[actCell].isExterior = true;     
                break;
            }
        }
    
    }
}

void MultiResolutionGraph::updateExternalCells(int l) {
    if (l < 0 || l > levels.size()) return;
    std::vector<vorocell>& cells = levels[l].getCells();
    for (int i = 0; i < cells.size(); ++i) {
        if (cells[i].state == AIR) continue;
        for (int k = 0; k < cells[i].neighbors.size(); ++k) {
            if (cells[i].neighbors[k] < 0 || cells[cells[i].neighbors[k]].state == AIR) {
                if (!cells[i].isExterior) {
                    
                }
                //graph -> updateLowerLevelCells(1, i);
                cells[i].isExterior = true;     
                break;
            }
        }
    }
}