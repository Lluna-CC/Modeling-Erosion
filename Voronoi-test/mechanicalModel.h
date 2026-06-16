#ifndef MECHANICALMODEL_H
#define MECHANICALMODEL_H
#include "cellGraph.h"
#include <Eigen/Sparse>
#include <Eigen/Core>

class MechanicalModel {
 public:
  MechanicalModel() {}
  void initializeModel(std::vector<vorocell>& cells, std::map<std::pair<int,int>, vorolink>& links, std::vector<int>& solidCells);

  void computeEquilibra();
  void updateLinkStresses(std::map<std::pair<int,int>, vorolink>& links, std::vector<vorocell>& cells, std::vector<int>& solidCells, std::vector<std::pair<int,int>>& brokenLinks); 
  void removeLink(std::pair<int,int> l, std::vector<vorocell>& cells, std::vector<int>& solidCells);
 
  double getTmax(double damage);
  double getShearC(double damage);
  double getUCS(double damage); 
  double getTanPhi() {return tanPhi;}

 private:
    Eigen::SparseMatrix<double> K;
    Eigen::VectorXd F;
    Eigen::VectorXd u;
    
    Vector3 g = Vector3(0.0,0.0,-9.81);
    double rockDensity = 2500.0;
    double kn = 1e9;
    double ks = 1e8;
    double T_max = 1e26;
    double UCS = 1e25;
    double c = 1e26;
    double tanPhi = 0.1773502;
};

#endif