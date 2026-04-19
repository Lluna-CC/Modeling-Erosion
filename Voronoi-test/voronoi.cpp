#include "voronoi.h"
#include<vector>
using namespace voro;



// This function returns a random double between 0 and 1
double rnd() {return double(rand())/RAND_MAX;}

double maxElevation(HeightField *hf) {

}

void Voronoi::heightfieldVoronoi(HeightField *hf, CellDecomposition* decomp) {
    
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

        if (cellZ <= z_max) decomp -> addCell(c,cellX, cellY, cellZ, loopAll.pid());
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
