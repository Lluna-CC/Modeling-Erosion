#ifndef MULTIRESOLUTIONGRAPH_HH
#define MULTIRESOLUTIONGRAPH_HH
#include <vector>
#include "cellGraph.h"
#include "core.h"
#include "voronoi.h"



class MultiResolutionGraph {
  public:
    //CellGraph& getLevel(int k) {return levels[k];};
    int getNumCells(int l) {return levels[l].getNumCells();}

    std::vector<vorocell>& getCells(int l) {return levels[l].getCells();}
    std::map<std::pair<int,int>, vorolink>& getLinks(int l) {return levels[l].getLinks();}
    std::set<std::pair<int,int>>& getExteriorLinks(int l) {return levels[l].getExteriorLinks();}

    void computeBounds();
    Vector3 getMin() {return levels[0].getMin();}
    Vector3 getMax() {return levels[0].getMax();}
    
    void multiLevelVoronoiDecomposition(std::vector<float>& v, std::vector<uint>& f, const HeightField *hf); 
    void toyVoronoi(const HeightField *hf) {levels.resize(1); Voronoi::toyVoronoi(hf, &levels[0]);};

    void clear();
    void updateExternalLinks();

    int getLevels() {return nLevels;}
    void removeLowerLevel(int l, int cell);

  private:
    int nLevels = 2;
  
    std::vector<CellGraph> levels;
    std::vector<std::vector<int>> upperLevel; //For each level and for each cell of that level, the centroid on the upper level
    std::vector<std::vector<std::vector<int>>> lowerLevel; //For each level and cell a vector of "children"
    
    int scale = 10;
 };

#endif