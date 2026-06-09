#include "mechanicalModel.h"
#include <iostream> 

void MechanicalModel::initializeModel(std::vector<vorocell>& cells) {
    std::vector<Eigen::Triplet<double>> K_coeff;
    
    int N = cells.size();
    F = Eigen::VectorXd::Zero(6*N);

    
    for (int i = 0; i < cells.size(); ++i) {
        //Skip Core and Air cells
        if (cells[i].state == SOLID) {
            double mass = cells[i].volume * rockDensity;
            F(6*i) = g[0]; F(6*i + 1) = g[1]; F(6*i + 2) = g[2];
        
            for (int j = 0; j < cells[i].neighbors.size(); ++j) {
                
                int neigh = cells[i].neighbors[j];
                if (i > neigh || cells[neigh].state != SOLID) continue;

                voroFace& interface = cells[i].faceData[j]; 
                double area = interface.area;
                Vector3 normal = interface.normal;
                
                Eigen::Vector3d n(normal[0],normal[1],normal[2]);
                Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
                Eigen::Matrix3d Kt = area * (kn * (n * n.transpose()) + ks*(I - n*n.transpose()));
                
                
                Eigen::Matrix3d R_i, R_j;

                Vector3 arm_i = interface.face_centroid - cells[i].centroid;
                R_i << 0, -arm_i[2], arm_i[1], arm_i[2], 0, -arm_i[0], -arm_i[1], arm_i[0], 0;
                
                Vector3 arm_j = interface.face_centroid - cells[neigh].centroid;  
                R_j << 0, -arm_j[2], arm_j[1], arm_j[2], 0, -arm_j[0], -arm_j[1], arm_j[0], 0;
                
                
                Eigen::Matrix<double, 3, 6> B_i, B_j; 
                
                B_i.block(0,0,3,3) = Eigen::Matrix3d::Identity();
                B_i.block(0,3,3,3) = R_i;
                
                B_j.block(0,0,3,3) = Eigen::Matrix3d::Identity();
                B_j.block(0,3,3,3) = R_j;

                
                Eigen::Matrix<double, 12, 12> K_act;
                K_act.block(0,0,6,6) = B_i.transpose() * Kt * B_i;
                K_act.block(6,6,6,6) = B_j.transpose() * Kt * B_j;
                K_act.block(0,6,6,6) = -B_i.transpose() * Kt * B_j;
                K_act.block(6,0,6,6) = -B_j.transpose() * Kt * B_i; 

                for (int k = 0; k < 6; ++k) 
                    for (int l = 0; l < 6; ++l)
                        K_coeff.push_back(Eigen::Triplet<double>(6*i + k, 6*i + l, K_act(k,l)));
            
                for (int k = 0; k < 6; ++k) 
                    for (int l = 0; l < 6; ++l)
                        K_coeff.push_back(Eigen::Triplet<double>(6*neigh + k, 6*neigh + l, K_act(k + 6,l + 6)));
            
                for (int k = 0; k < 6; ++k) 
                    for (int l = 0; l < 6; ++l)
                        K_coeff.push_back(Eigen::Triplet<double>(6*i + k, 6*neigh + l, K_act(k, l + 6)));
            
                for (int k = 0; k < 6; ++k) 
                    for (int l = 0; l < 6; ++l)
                        K_coeff.push_back(Eigen::Triplet<double>(6*neigh + k, 6*i + l, K_act(k + 6, l)));
            
            }
        }

        else {
            for (int j = 0; j < 6; ++j) K_coeff.push_back(Eigen::Triplet<double>(6*i + j, 6*i + j, 1));
        }


    }

    K.resize(6*N,6*N);
    K.setFromTriplets(K_coeff.begin(), K_coeff.end());
}

void MechanicalModel::computeEquilibra() {
    std::cout << "Finding Equilibria" << std::endl;
    Eigen::ConjugateGradient<Eigen::SparseMatrix<double>> solver(K);
    u = solver.solve(F);
}

void MechanicalModel::updateLinkStresses(std::map<std::pair<int,int>, vorolink>& links) {
    for (auto it = links.begin(); it != links.end(); ++it) {
        int i = it -> first.first;
        int j = it -> first.second;
    }
}

