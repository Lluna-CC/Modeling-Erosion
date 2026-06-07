#ifndef MECHANICALMODEL_H
#define MECHANICALMODEL_H
#include "cellGraph.h"
#include <Eigen/Sparse>

class MechanicalModel {
 public:
    MechanicalModel();
    void initializeModel(CellGraph* graph);

    void computeEquilibra();

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