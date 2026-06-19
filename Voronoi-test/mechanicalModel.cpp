#include "mechanicalModel.h"
#include <iostream> 

void MechanicalModel::initializeModel(std::vector<vorocell>& cells, std::map<std::pair<int,int>, vorolink>& links, std::vector<int>& solidCells) {
    std::vector<Eigen::Triplet<double>> K_coeff;
    
    int N = solidCells[solidCells.size() - 1];
    F = Eigen::VectorXd::Zero(6*N);
    std::cout << "N: " << N << std::endl;
    
    for (int i = 0; i < cells.size(); ++i) {
        if (solidCells[i] == -1) continue;
        int cell = solidCells[i];
        if (cells[i].state == SOLID) {

            double mass = cells[i].volume * rockDensity;
            
            F(6*cell) = g[0]*mass; F(6*cell + 1) = g[1]*mass; F(6*cell + 2) = g[2]*mass;
            
            for (int j = 0; j < cells[i].neighbors.size(); ++j) {
                
                
                int neigh = cells[i].neighbors[j];
                if (i > neigh || cells[neigh].state != SOLID || links[std::make_pair(i, neigh)].state == BROKEN) continue;
                int cell_j = solidCells[neigh];
                

                voroFace& interface = cells[i].faceData[neigh]; 
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
                        K_coeff.push_back(Eigen::Triplet<double>(6*cell + k, 6*cell + l, K_act(k,l)));
            
                for (int k = 0; k < 6; ++k) 
                    for (int l = 0; l < 6; ++l)
                        K_coeff.push_back(Eigen::Triplet<double>(6*cell_j + k, 6*cell_j + l, K_act(k + 6,l + 6)));
            
                for (int k = 0; k < 6; ++k) 
                    for (int l = 0; l < 6; ++l)
                        K_coeff.push_back(Eigen::Triplet<double>(6*cell + k, 6*cell_j + l, K_act(k, l + 6)));
            
                for (int k = 0; k < 6; ++k) 
                    for (int l = 0; l < 6; ++l)
                        K_coeff.push_back(Eigen::Triplet<double>(6*cell_j + k, 6*cell + l, K_act(k + 6, l)));
            
            }
        }

        else {
            for (int j = 0; j < 6; ++j) K_coeff.push_back(Eigen::Triplet<double>(6*cell + j, 6*cell + j, 1));
        }


    }

    K.resize(6*N,6*N);
    K.setFromTriplets(K_coeff.begin(), K_coeff.end());
    
    
}

void MechanicalModel::computeEquilibra() {
    std::cout << "Finding Equilibria" << std::endl;
    Eigen::LeastSquaresConjugateGradient<Eigen::SparseMatrix<double>> solver(K);
    u = solver.solve(F);
    std::cout << "Equilibria Found" << std::endl;
}

void MechanicalModel::updateLinkStresses(std::map<std::pair<int,int>, vorolink>& links, std::vector<vorocell>& cells, std::vector<int>& solidCells, std::vector<std::pair<int,int>>& brokenLinks) {
    brokenLinks.clear();
    std::cout << "Updating Link Stresses" << std::endl;
    for (auto it = links.begin(); it != links.end(); ++it) {
        if (it -> second.state == EXTERIOR || it -> second.state == BROKEN) continue;
        int i = it -> first.first;
        int j = it -> first.second;
        if (i < 0 || j < 0) continue;
        int solid_i = solidCells[i];
        int solid_j = solidCells[j];
        if (solid_i == -1 || solid_j == -1) continue;

        Vector3 s_i = Vector3(u(6*solid_i), u(6*solid_i + 1), u(6*solid_i + 2));
        Vector3 theta_i = Vector3(u(6*solid_i + 3), u(6*solid_i + 4), u(6*solid_i + 5));
        Vector3 s_j = Vector3(u(6*solid_j), u(6*solid_j + 1), u(6*solid_j + 2));
        Vector3 theta_j = Vector3(u(6*solid_j + 3), u(6*solid_j + 4), u(6*solid_j + 5));
        Vector3 r_i = (cells[i].faceData[j].face_centroid - cells[i].centroid);
        Vector3 r_j = (cells[j].faceData[i].face_centroid - cells[j].centroid);

        Vector3 d_i = s_i + cross(theta_i, r_i);
        Vector3 d_j = s_j + cross(theta_j, r_j);
        Vector3 d_ij = d_j - d_i;

        double area = cells[i].faceData[j].area;
        Vector3 n = cells[i].faceData[j].normal;
        Vector3 F_ij = kn * area * (dot(d_ij, n) * n) + ks * area* (d_ij - dot(d_ij, n) * n); 
        it -> second.normalStress = -dot(F_ij, n)/area;
        it -> second.shearStress = Norm(F_ij - dot(F_ij, n)*n)/area;

        double D = 1 - it -> second.life;
        if (it -> second.normalStress > getTmax(D)) {
            std::cout << "Crack Propagation. Normal stress: " << it -> second.normalStress << std::endl;
            brokenLinks.push_back(it -> first);
        }
        else if (it -> second.shearStress > (getShearC(D) - it -> second.normalStress * tanPhi)) {
            std::cout << "Crack Propagation. Shear stress: " << it -> second.shearStress << std::endl;
            brokenLinks.push_back(it -> first);
        }
        else if (it -> second.normalStress < -getUCS(D)) {
            std::cout << "Crack Propagation.  Normal stress: " << it -> second.normalStress << std::endl;
            brokenLinks.push_back(it -> first);
        }
    }
}

void MechanicalModel::removeLink(std::pair<int,int> l, std::vector<vorocell>& cells, std::vector<int>& solidCells) {
    int i = solidCells[l.first];
    int j = solidCells[l.second];

    voroFace& interface = cells[l.first].faceData[l.second]; 
    double area = interface.area;
    Vector3 normal = interface.normal;

    Eigen::Vector3d n(normal[0],normal[1],normal[2]);
    Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
    Eigen::Matrix3d Kt = area * (kn * (n * n.transpose()) + ks*(I - n*n.transpose()));

    
    Eigen::Matrix3d R_i, R_j;

    Vector3 arm_i = interface.face_centroid - cells[l.first].centroid;
    R_i << 0, -arm_i[2], arm_i[1], arm_i[2], 0, -arm_i[0], -arm_i[1], arm_i[0], 0;
    
    Vector3 arm_j = interface.face_centroid - cells[l.second].centroid;  
    R_j << 0, -arm_j[2], arm_j[1], arm_j[2], 0, -arm_j[0], -arm_j[1], arm_j[0], 0;
    
    Eigen::Matrix<double, 3, 6> B_i, B_j; 
    
    B_i.block(0,0,3,3) = Eigen::Matrix3d::Identity();
    B_i.block(0,3,3,3) = R_i;

    B_j.block(0,0,3,3) = Eigen::Matrix3d::Identity();
    B_j.block(0,3,3,3) = R_j;
    
    Eigen::Matrix<double, 6, 6> K_ii = B_i.transpose() * Kt * B_i;
    Eigen::Matrix<double, 6, 6> K_jj = B_j.transpose() * Kt * B_j;
    for (int k = 0; k < 6; ++k) {
        for (int l = 0; l < 6; ++l) {
            K.coeffRef(6*i + k,6*j + l) = 0;
            K.coeffRef(6*j + k,6*i + l) = 0;
            K.coeffRef(6*i + k, 6*i + l) -= K_ii(k, l);
            K.coeffRef(6*j + k, 6*j + l) -= K_jj(k, l);
        }
    }
    K.makeCompressed();
}

double MechanicalModel::getTmax(double damage) {
    return T_max*(1 - damage);
}

double MechanicalModel::getShearC(double damage) {
    return c*(1 - damage);
}

double MechanicalModel::getUCS(double damage) {
    return UCS*(1 - damage);
}

double MechanicalModel::normalModifier(vorolink& l) {
    

    if (l.normalStress > 0) {
        
        double T = getTmax(1 - l.life); 
        return exp(alph_tt * pow(l.normalStress/T,p));
    }

    else {
        double u = abs(l.normalStress)/getUCS(1 - l.life);
       
        double Ic = 1 + s*u - alph_c*u*u;  
        return 1.0/Ic;
    }
    
}

double MechanicalModel::shearModifier(vorolink& l) {
    double c = getShearC(1 - l.life);
    double t_limit = c - l.normalStress * tanPhi;
    
    return alph_s * pow(l.shearStress/t_limit, q);
}

void MechanicalModel::setAvgLen(double L) {
    kn = E/L;
    ks = E/(2*(1+v)*L);
}