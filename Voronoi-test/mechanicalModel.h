#ifndef MECHANICALMODEL_H
#define MECHANICALMODEL_H
#include "cellGraph.h"
#include <Eigen/Sparse>
#include <Eigen/Core>

class MechanicalModel {
 public:
   MechanicalModel() {}
   void initializeModel(std::vector<vorocell>& cells);

   void computeEquilibra();
   void updateLinkStresses(std::map<std::pair<int,int>, vorolink>& links); 

 private:
    Eigen::SparseMatrix<double> K;
    Eigen::VectorXd F;
    Eigen::VectorXd u;
    
    Vector3 g = Vector3(0.0,0.0,-9.81);
    double rockDensity = 2500.0;
    double kn = 1e9;
    double ks = 1e8;
};

#endif