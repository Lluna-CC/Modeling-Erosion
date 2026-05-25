#ifndef MULTIRESOLUTIONGRAPH_HH
#define MULTIRESOLUTIONGRAPH_HH
#include <vector>
#include "cellGraph.h"
#include "core.h"
#include "voronoi.h"



class MultiResolutionGraph {
  public:
    //CellGraph& getLevel(int k) {return levels[k];};
    int getNumCells(int k) {return levels[k].getNumCells();}

    std::vector<vorocell>& getCells(int k) {return levels[k].getCells();}
    std::map<std::pair<int,int>, vorolink>& getLinks(int k) {return levels[k].getLinks();}
    std::set<std::pair<int,int>>& getExteriorLinks(int k) {return levels[k].getExteriorLinks();}

    void computeBounds();
    Vector3 getMin() {return levels[0].getMin();}
    Vector3 getMax() {return levels[0].getMax();}
    
    void multiLevelVoronoiDecomposition(std::vector<float>& v, std::vector<uint>& f, const HeightField *hf); 
    void toyVoronoi(const HeightField *hf) {levels.resize(1); Voronoi::toyVoronoi(hf, &levels[0]);};

    void clear();
    void updateExternalLinks();

  private:
    std::vector<CellGraph> levels;

};

#endif