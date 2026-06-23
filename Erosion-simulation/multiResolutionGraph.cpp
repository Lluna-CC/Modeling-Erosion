#include "multiResolutionGraph.h"
#include <random>
#include<float.h>
#include<chrono>

void MultiResolutionGraph::multiLevelVoronoiDecompositionFurthestPoint(std::vector<float>& v, std::vector<uint>& f, const HeightField *hf, int scale, 
    Vector3 core_center, Vector3 core_range, int zSamples) {
    
    
    
    levels.resize(nLevels);
    upperLevel.resize(nLevels - 1);
    lowerLevel.resize(nLevels - 1);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    Voronoi::cellSamplingVoronoi(hf,&levels[0], core_center, core_range, zSamples);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Decomposition Done. Elapsed time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

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
    while (levels[0].getCells()[first].state == DISCARDED) first = dist(rng);
    centroids[0] = levels[0].getCells()[first].centroid;

    std::vector<double> minDistances(levels[0].getNumCells(), DBL_MAX);
    std::vector<int> closestCentroid(levels[0].getNumCells());
    double max = -1; 
    int argmax;
    std::vector<bool> discard(newSize, false);
    
    for (int i = 1; i < newSize; ++i) {
        
        for (int j = 0; j < minDistances.size(); ++j) {
            if (levels[0].getCells()[j].state == DISCARDED) continue;
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
        
        if (max == -1) {
            discard[i] = true;     
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
        if (levels[0].getCells()[j].state == SOLID || levels[0].getCells()[j].state == CORE) exterior[closestCentroid[j]] = false;
    }


    Voronoi::voronoiFromCentroids(centroids, exterior, &levels[1], hf, core_center, core_range, zSamples, discard);
    end = std::chrono::steady_clock::now();

    std::cout << "Second level completed! Elapsed time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
    
}


void subSampling(double x, double y, double sizeX, double sizeY, int offset, int& particles, const HeightField* hf, int subdivisions, std::vector<Vector3>& higherCentroids, std::vector<bool>& higherExterior) {
    double sub_x[4] = {x - 0.25*sizeX, x + 0.25*sizeX, x - 0.25*sizeX, x + 0.25*sizeX};
    double sub_y[4] = {y + 0.25*sizeY, y + 0.25*sizeY, y - 0.25*sizeY, y - 0.25*sizeY};
    for (int k = 0; k < 4; ++k) {
        double local_x = sub_x[k] + (Math::rnd() - 0.5)*sizeX*0.25;
        double local_y = sub_y[k] + (Math::rnd() - 0.5)*sizeY*0.25;   
        double local_z = hf -> Height(Vector2(local_x, local_y));

        if (subdivisions > 0) {
            subSampling(sub_x[k], sub_y[k], sizeX*0.5, sizeY*0.5, offset, particles, hf, subdivisions - 1, higherCentroids, higherExterior);
        }

        else {
            Vector3 centroid =  Vector3(local_x,local_y,local_z);
            Vector3 norm = hf -> Normal(Vector2(x,y));
            
            //Add point to both sides
            Vector3 first = centroid + offset*norm;
            Vector3 second = centroid - offset*norm;

            higherCentroids.push_back(first);
            higherCentroids.push_back(second);
            higherExterior.push_back(true);
            higherExterior.push_back(false);

        }
    }
}

void MultiResolutionGraph::multiLevelVoronoiDecompositionGridSampling(std::vector<float>& v, std::vector<uint>& f, const HeightField *hf, int window, 
    Vector3 core_center, Vector3 core_range, int zSamples) {
    const double offsetScale = 0.5; 
    const double areaRatioLimit = 1.5;
    const int areaRatioWindow = 8;

    levels.resize(nLevels);
    upperLevel.resize(nLevels - 1);
    lowerLevel.resize(nLevels - 1);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    Box3 domain = hf -> getBox();
    Vector3 min = domain.getMin();
    Vector3 max = domain.getMax();
    ScalarField2 AreaRatio = hf -> AreaRatio(areaRatioWindow);

    int nx = hf -> getSizeX();
    int ny = hf -> getSizeY();
    double sizeX = hf -> getCellSize()[0];
    double sizeY = hf -> getCellSize()[1];
    int nz = (max[2] - min[2])/sizeX; 

    int block = 1;
    double offset = offsetScale*Norm(hf->getCellSize());

    max[2] = max[2] + 4*offset;
    min[2] = min[2] - 4*offset;

    int particles = 0;

    double x,y,z;

    std::vector<Vector3> lowerCentroids;
    std::vector<bool> lowerExterior;
    std::vector<Vector3> higherCentroids;
    std::vector<bool> higherExterior;

    int lastBlock = 0;
    for (int bi = 0; bi < nx; bi += window) {
        for (int bj = 0; bj < ny; bj += window) {
            int lim_x = bi + window < nx ? bi + window : nx;
            int lim_y = bj + window < ny ? bj + window : ny;
            
            for (int i = bi; i < lim_x; ++i) {
                for (int j = bj; j < lim_y; ++j) {
                    double center_x = min[0] + i*sizeX - 0.5*sizeX;
                    double center_y = min[1] + j*sizeY - 0.5*sizeY; 
                    x = center_x + (Math::rnd() - 0.5)*sizeX*0.5;
                    y = center_y + (Math::rnd() - 0.5)*sizeY*0.5;
                    z = hf -> Height(Vector2(x,y));

                    double localAreaRatio = AreaRatio.at(i,j);
                    if (localAreaRatio > areaRatioLimit) {
                        if (localAreaRatio > areaRatioLimit + 0.5) subSampling(center_x,center_y,sizeX,sizeY, offset, particles, hf, 1, higherCentroids, higherExterior);
                        else subSampling(center_x,center_y,sizeX,sizeY, offset, particles, hf, 0, higherCentroids, higherExterior);
                    }
                    
                    else {
                        Vector3 centroid =  Vector3(x,y,z);
                        Vector3 norm = hf -> Normal(Vector2(x,y));
                        
                        //Add point to both sides
                        Vector3 first = centroid + offset*norm;
                        Vector3 second = centroid - offset*norm;
                        
                        higherCentroids.push_back(first);
                        higherCentroids.push_back(second);
                        higherExterior.push_back(true);
                        higherExterior.push_back(false);
                    }
                }
            }

            double center_bi, center_bj; 
            if (window % 2 == 0) {
                center_bi = bi + window/2 < nx ? min[0] + (bi + window/2)*sizeX - 0.1*sizeX : min[0] + (nx - 1)*sizeX - 0.1*sizeX;
                center_bj = bj + window/2 < ny ? min[1] + (bj + window/2)*sizeY - 0.1*sizeY : min[1] + (ny - 1)*sizeY - 0.1*sizeY;  
            }
            else {
                center_bi = bi + window/2 + 1 < nx ? min[0] + (bi + window/2 + 1)*sizeX - 0.5*sizeX : min[0] + (nx - 1)*sizeX - 0.1*sizeX;
                center_bj = bj + window/2 + 1 < ny ? min[1] + (bj + window/2 + 1)*sizeY - 0.5*sizeY : min[1] + (ny - 1)*sizeY - 0.1*sizeY;  
            }
            double center_z = hf -> Height(Vector2(center_bi,center_bj));
            Vector3 block_center(center_bi, center_bj, center_z);
            
            Vector3 sample_int, sample_ext;
            double minDist_int = 10*sizeX + 10*sizeY, minDist_ext = 10*sizeX + 10*sizeY;
            lowerLevel[0].push_back(std::vector<int>());
            lowerLevel[0].push_back(std::vector<int>());
            for (int k = lastBlock; k < higherCentroids.size(); ++k) {
                if (k % 2 == 0) {
                    if (Norm(block_center - higherCentroids[k]) < minDist_ext) {
                        minDist_ext = Norm(block_center - higherCentroids[k]);
                        sample_ext = higherCentroids[k];
                    }
                    upperLevel[0].push_back(lowerCentroids.size() - 1);
                    lowerLevel[0][lowerCentroids.size()].push_back(k);
                }
                else {
                    if (Norm(block_center - higherCentroids[k]) < minDist_int) {
                        minDist_int = Norm(block_center - higherCentroids[k]);
                        sample_int = higherCentroids[k];
                    }
                    upperLevel[0].push_back(lowerCentroids.size() + 1);
                    lowerLevel[0][lowerCentroids.size() + 1].push_back(k);
                }
                
                
            }
            
            
            lastBlock = higherCentroids.size();
            lowerCentroids.push_back(sample_ext);
            lowerCentroids.push_back(sample_int);
            lowerExterior.push_back(true);
            lowerExterior.push_back(false);
        }
    }
    

    double cellScale = 0.75;
    double sizeZ = (max[2] - min[2])/zSamples;
    
    for (int bi = 0; bi < nx; bi += window) {
        int lim_x = bi + window < nx ? bi + window : nx;
        for (int bj =  0; bj < ny; bj += window) {
            int lim_y = bj + window < ny ? bj + window : ny;
            for (int bk = 0; bk < zSamples; bk += window) {
                int lim_z = bk + window < zSamples ? bk + window : zSamples;
                for (int i = bi; i < lim_x; ++i) {
                    double x_block = min[0] + i*sizeX - 0.5*sizeX;    
                
                    for (int j = bj; j < lim_y; ++j) {
                        double y_block = min[1] + j*sizeY - 0.5*sizeY;    
                        for (int k = bk; k < lim_z; ++k) {
                            double z_block = min[2] + k*sizeZ - 0.5*sizeZ;
                            x = x_block + (Math::rnd() - 0.5)*(sizeX)*cellScale;
                            y = y_block + (Math::rnd() - 0.5)*(sizeY)*cellScale;
                            z = z_block + (Math::rnd() - 0.5)*(sizeZ)*cellScale;
                            
                            double z_max = hf -> Height(Vector2(x,y));
                            if (z > z_max - 1.5*offset) break;

                            higherCentroids.push_back(Vector3(x,y,z));
                            higherExterior.push_back(false);
                        }
        
                    }
                }

                double center_bi, center_bj, center_bk; 
                if (window % 2 == 0) {
                    center_bi = bi + window/2 < nx ? min[0] + (bi + window/2)*sizeX -0.1*sizeX : min[0] + (nx - 1)*sizeX - 0.1*sizeX;
                    center_bj = bj + window/2 < ny ? min[1] + (bj + window/2)*sizeY -0.1*sizeY : min[1] + (ny - 1)*sizeY - 0.1*sizeY;  
                    center_bk = bk + window/2 < zSamples ? min[2] + (bk + window/2)*sizeZ -0.1*sizeZ : min[2] + (zSamples - 1)*sizeZ - 0.1*sizeZ;
                }
                else {
                    center_bi = bi + window/2 + 1 < nx ? min[0] + (bi + window/2 + 1)*sizeX - 0.5*sizeX : min[0] + (nx - 1)*sizeX - 0.1*sizeX;
                    center_bj = bj + window/2 + 1 < ny ? min[1] + (bj + window/2 + 1)*sizeY - 0.5*sizeY : min[1] + (ny - 1)*sizeY - 0.1*sizeY;
                    center_bk = bk + window/2 + 1 < zSamples ? min[2] + (bk + window/2 + 1)*sizeZ : min[2] + (zSamples - 1)*sizeZ - 0.1*sizeZ;
                }
                double center_z = hf -> Height(Vector2(center_bi,center_bj));
                Vector3 block_center(center_bi, center_bj, center_z);
                
                Vector3 sample;
                double minDist = 10*sizeX + 10*sizeY;
                lowerLevel[0].push_back(std::vector<int>());
                for (int k = lastBlock; k < higherCentroids.size(); ++k) {
        
                    if (Norm(block_center - higherCentroids[k]) < minDist) {
                        minDist = Norm(block_center - higherCentroids[k]);
                        sample = higherCentroids[k];
                    }
                    
                    upperLevel[0].push_back(lowerCentroids.size());
                    lowerLevel[0][lowerCentroids.size()].push_back(k);
                }
                
                
                lastBlock = higherCentroids.size();
                lowerCentroids.push_back(sample);
                lowerExterior.push_back(false);
                
            }
            
        }
    }
    

    Voronoi::voronoiFromCentroids(higherCentroids, higherExterior, &levels[0], hf, core_center, core_range, zSamples);
    Voronoi::voronoiFromCentroids(lowerCentroids, lowerExterior, &levels[1], hf, core_center, core_range, zSamples);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Second level completed! Elapsed time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
    
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
        if (cells[i].state == AIR || cells[i].state == DISCARDED) continue;
        for (int k = 0; k < cells[i].neighbors.size(); ++k) {
            if (cells[i].neighbors[k] < 0 || cells[cells[i].neighbors[k]].state == AIR) {
                
                //graph -> updateLowerLevelCells(1, i);
                cells[i].isExterior = true;     
                break;
            }
        }
    }
}