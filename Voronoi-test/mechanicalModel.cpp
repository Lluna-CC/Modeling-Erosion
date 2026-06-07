#include "mechanicalModel.h"


void MechanicalModel::initializeModel(CellGraph* graph) {
    std::vector<Eigen::Triplet<double>> K_coeff;
    std::vector<vorocell>& cells = graph -> getCells();
    
    int N = cells.size();
    F = Eigen::VectorXd::Zero(N);

    
    for (int i = 0; i < cells.size(); ++i) {
        //Skip Core and Air cells
        if (cells[i].state == SOLID) {
            double mass = cells[i].volume * rockDensity;
            F(6*i) = g[0]; F(6*i + 1) = g[1]; F(6*i + 2) = g[2];
        
            for (int j = 0; i < cells[i].neighbors.size(); ++j) {
                int neigh = cells[i].neighbors[j];
                if (i > neigh || cells[neigh].state != SOLID) continue;

                double area = cells[i].faceData[j].area;
                Vector3 normal = cells[i].faceData[j].normal;
                
                Eigen::Vector3d n(normal[0],normal[1],normal[2]);
                Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
                Eigen::Matrix3d kt = area * (kn * (n * n.transpose()) + ks*(I - n*n.transpose()));
            }
        }

        else {
            for (int j = 0; j < 6; ++j) K_coeff.push_back(Eigen::Triplet<double>(6*i + j, 6*i + j, 1));
        }


    }
}