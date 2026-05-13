#include "voronoi.h"
#include<vector>
using namespace voro;



// This function returns a random double between 0 and 1
double rnd() {return double(rand())/RAND_MAX;}

double maxElevation(HeightField *hf) {

}

void Voronoi::heightfieldVoronoi(const HeightField *hf, CellDecomposition* decomp) {
    
    std::cout << "Starting!" << std::endl;
    Box3 domain = hf -> getBox();
    Vector3 min = domain.getMin();
    Vector3 max = domain.getMax();

    int nx = hf -> getSizeX();
    int ny = hf -> getSizeY();
    double sizeX = hf -> getCellSize()[0];
    double sizeY = hf -> getCellSize()[1];
    int nz = (max[2] - min[2])/sizeX; 
    
    
    container con(min[0],max[0], min[1],max[1], min[2],max[2], nx, ny, nz, false, false, false, 2);
    HeightFieldWall hf_wall(hf);
    con.add_wall(hf_wall);

    double x,y,z;
    
    
    int block = 3;
    int zSamples = 35;
    int particles = 0;
    //int block = ny;
    //int zSamples = 1;
    
    
    for (int i = 0; i < nx/block; ++i) {
        for (int j = 0; j < ny/block; ++j) {
            for (int k = 0; k < zSamples; ++k) {
                x = min[0] + i*block*sizeX + rnd()*(block*sizeX);
                y = min[1] + j*block*sizeY  + rnd()*(block*sizeY);
                //double z_max = hf -> Height(Vector2(x,y));
                z = min[2] + rnd()*(max[2] - min[2]);
                
                int idx = i*ny/block*zSamples + j*zSamples + k;
                con.put(particles,x,y,z);
                ++particles;
            }
        }
    }
   
    
    c_loop_all loopAll(con);
    std::cout << "number of particles: " << particles << " " << con.total_particles() << std::endl;
     
    if(!loopAll.start()) return;
    decomp -> setNumCells(particles);
    do {
        voronoicell_neighbor c;
        //std::cout << "a" << std::endl;
        con.compute_cell(c,loopAll);
        if (loopAll.pid() >= particles) std::cout << loopAll.pid() << std::endl;
        double cellX = loopAll.x();
        double cellY = loopAll.y();
        double cellZ = loopAll.z();
        double z_max = hf -> Height(Vector2(cellX,cellY));

        if (cellZ <= z_max) decomp -> addCell(c,cellX, cellY, cellZ, loopAll.pid(), false);
        //else std::cout << "OUT OF RANGE!" << std::endl;
        
    }while (loopAll.inc()); 
    std::cout << "Decomposition ended" << std::endl;
    /*int i = 0;
    while (i < particles) {
        x = min[0] + rnd()*(max[0] - min[0]);
        y = min[1] + rnd()*(max[1] - min[1]);
        double z_max = hf -> Height(Vector2(x,y));
        z = min[2] + rnd()*(z_max - min[2]);

        if(con.point_inside(x,y,z)) {
            con.put(i,x,y,z);
            ++i;
        }
    }*/
    
}

void Voronoi::triangleSamplingVoronoi(std::vector<float>& v, std::vector<uint>& f, CellDecomposition* decomp, const HeightField* hf) {
    std::cout << "Starting!" << std::endl;
    Box3 domain = hf -> getBox();
    Vector3 min = domain.getMin();
    Vector3 max = domain.getMax();

    int nx = hf -> getSizeX();
    int ny = hf -> getSizeY();
    double sizeX = hf -> getCellSize()[0];
    double sizeY = hf -> getCellSize()[1];
    int nz = (max[2] - min[2])/sizeX; 

    int block = 4;
    double offset = 0.5*Norm(hf->getCellSize());
    int zSamples = 25;

    container con(min[0],max[0], min[1],max[1], min[2],max[2] + block, nx/4, ny/4, nz/4, false, false, false, 5);

    int particles = 0;

    double x,y,z;
    

    //HeightFieldWall hf_wall(hf);
    //con.add_wall(hf_wall);

    
    //Two particles per triangle
    for (int i = 0; i < f.size(); i +=3) {
        //Compute centroid
        Vector3 v1 =  Vector3(v[3*f[i]], v[3*f[i] + 1], v[3*f[i] + 2]);
        Vector3 v2 =  Vector3(v[3*f[i + 1]], v[3*f[i + 1] + 1], v[3*f[i +1] + 2]);
        Vector3 v3 =  Vector3(v[3*f[i + 2]], v[3*f[i + 2] + 1], v[3*f[i + 2] + 2]);
        Vector3 centroid = (v1 + v2 + v3)/3;
        
        Vector3 a = v2 - v1;
        Vector3 b = v3 - v1;

  
        //Vector3 norm = Normalized(cross(a,b));
        Vector3 norm = Normalized(cross(a,b));
        

        //Add point to both sides
        Vector3 first = centroid + offset*norm;
        Vector3 second = centroid - offset*norm;
        
        con.put(particles,(double) first[0], (double) first[1], (double) first[2]);
        con.put(particles + 1,(double) second[0],(double) second[1], (double) second[2]);
        
        particles += 2;
    }

    //Particles under the terrain
    
    for (int i = 0; i < nx/block; ++i) {
        for (int j = 0; j < ny/block; ++j) {
            double x_block = min[0] + i*block*sizeX + 0.5*((block - 1)*sizeX);
            double y_block = min[1] + j*block*sizeY  + 0.5*((block - 1)*sizeY);
            double t = hf -> Height(Vector2(x_block,y_block));
            t = t/max[2];
            
            int actSamples = 1 + zSamples*t;
            for (int k = 0; k < actSamples; ++k) {
                x = min[0] + i*block*sizeX + rnd()*((block - 1)*sizeX);
                y = min[1] + j*block*sizeY  + rnd()*((block - 1)*sizeY);
                double z_max = hf -> Height(Vector2(x,y)) - block/2;
                
                z = min[2] + rnd()*(z_max - min[2]);
                
                int idx = i*ny/block*zSamples + j*zSamples + k;
                con.put(particles,x,y,z);
                ++particles;
            }
        }
    }


    c_loop_all loopAll(con);
    std::cout << "number of particles: " << particles << " " << con.total_particles() << std::endl;
     
    if(!loopAll.start()) return;
    decomp -> setNumCells(particles);
    do {
        voronoicell_neighbor c;
        //std::cout << "a" << std::endl;
        con.compute_cell(c,loopAll);
        if (loopAll.pid() >= particles) std::cout << loopAll.pid() << std::endl;
        double cellX = loopAll.x();
        double cellY = loopAll.y();
        double cellZ = loopAll.z();
        double z_max = hf -> Height(Vector2(cellX,cellY));

        if (cellZ <= z_max) decomp -> addCell(c,cellX, cellY, cellZ, loopAll.pid(), false);
        else decomp -> addCell(c,cellX, cellY, cellZ, loopAll.pid(), true);
        
    }while (loopAll.inc()); 
    std::cout << "Decomposition ended" << std::endl;

}