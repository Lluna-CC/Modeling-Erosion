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
    double normalStressModifier(double normalStress, double D);
    double shearStressModifier(double shearStress, double normalStress, double D);    

    double normalModifier(vorolink& l);
    double shearModifier(vorolink& l);

    void setAvgLen(double L); 

 private:
    Eigen::SparseMatrix<double> K;
    Eigen::VectorXd F;
    Eigen::VectorXd u;
    
    Vector3 g = Vector3(0.0,0.0,-9.81);
    double rockDensity = 2650;
   double E = 70e9;
   double v = 0.255;
   double kn = 1e9;
   double ks = 1e8;
   double T_max = 39e6;
   double UCS = 2.2e9;
   double c = 20e6;
   double tanPhi = 0.267949;

   double alph_s = 5.0;
   double q = 2.0;
   double s = 2.0;
   double alph_c = 6.0;
   double alph_tt = 2.0; 
   double p = 2.0;
};

#endif