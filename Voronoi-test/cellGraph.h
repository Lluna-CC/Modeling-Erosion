#ifndef CELLGRAPH
#define CELLGRAPH

#include <vector>
#include <map>
#include <set>
#include "core.h"
#include <voro++.hh>

enum cellState {
  SOLID,
  AIR,
  CORE
};

enum linkState {
  INTERIOR,
  EXTERIOR,
  BROKEN,
  MARKED
};

struct voroFace {
  //int planeID;
  //std::vector<unsigned int> faceNeighbors;
  std::vector<unsigned int> vertices;
  double area;
  Vector3 normal;
  Vector3 face_centroid;
};


struct vorocell {
  Vector3 centroid;
  std::vector<float> vertices;
  std::map<int,voroFace> faceData;
  std::vector<int> neighbors;
  int nTriangles;
  cellState state = SOLID;
  bool isExterior = false;
  double volume = -1;
};

struct vorolink  {
  std::vector<std::pair<int,int>> neighbors;
  linkState state = INTERIOR;
  double life = 1.0;
  double normalStress = 0.0;
  double shearStress = 0.0;
};

class CellGraph {
 public:
  
  int getNumCells() {return cells.size();}

  std::vector<vorocell>& getCells() {return cells;}
  std::map<std::pair<int,int>, vorolink>& getLinks() {return links;}
  std::set<std::pair<int,int>>& getExteriorLinks() {return exteriorLinks;}
  

  void addCell(voro::voronoicell_neighbor& c, double x, double y, double z, int pid, bool outside, bool isCore = false);
  void setNumCells(int n);
  
  void computeBounds();
  Vector3 getMin() {return min;}
  Vector3 getMax() {return max;}

  
  bool breakLink(std::pair<int,int> link);
  void removeComponent(int cell);
  int componentSize(int cell, int otherCell, bool& containsCore, bool& reachable, bool& exterior);
  void updateExternalLinks(); 

  void clear();
  
 private:

  Vector3 min;
  Vector3 max;

  std::vector<vorocell> cells;
  std::map<std::pair<int,int>, vorolink> links;
  std::set<std::pair<int,int>> exteriorLinks;
  void addLinks(voro::voronoicell_neighbor& c, std::map<int,voroFace>& faces, int pid);


    
};

#endif