#include "voronoi.h"
#include<vector>
using namespace voro;



// This function returns a random double between 0 and 1
double rnd() {return double(rand())/RAND_MAX;}

double maxElevation(HeightField *hf) {

}

void Voronoi::heightfieldVoronoi(const HeightField *hf, CellGraph* graph) {
    
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
                
                //int idx = i*ny/block*zSamples + j*zSamples + k;
                con.put(particles,x,y,z);
                ++particles;
            }
        }
    }
   
    
    c_loop_all loopAll(con);
    std::cout << "number of particles: " << particles << " " << con.total_particles() << std::endl;
     
    if(!loopAll.start()) return;
    graph -> setNumCells(particles);
    do {
        voronoicell_neighbor c;
        //std::cout << "a" << std::endl;
        con.compute_cell(c,loopAll);
        if (loopAll.pid() >= particles) std::cout << loopAll.pid() << std::endl;
        double cellX = loopAll.x();
        double cellY = loopAll.y();
        double cellZ = loopAll.z();
        double z_max = hf -> Height(Vector2(cellX,cellY));

        if (cellZ <= z_max) graph -> addCell(c,cellX, cellY, cellZ, loopAll.pid(), false);
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

void Voronoi::triangleSamplingVoronoi(const HeightField* hf, std::vector<float>& v, std::vector<uint>& f, CellGraph* graph) {
    std::cout << "Starting!" << std::endl;
    Box3 domain = hf -> getBox();
    Vector3 min = domain.getMin();
    Vector3 max = domain.getMax();

    int nx = hf -> getSizeX();
    int ny = hf -> getSizeY();
    double sizeX = hf -> getCellSize()[0];
    double sizeY = hf -> getCellSize()[1];
    int nz = (max[2] - min[2])/sizeX; 

    int block = 1;
    double offset = 0.75*Norm(hf->getCellSize());
    int zSamples = 16;

    container con(min[0],max[0], min[1],max[1], min[2] - 4*offset,max[2] + 4*offset, nx, ny, nz, false, false, false, 2);

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
        Vector3 jitter = Vector3(rnd(),rnd(),rnd());
        jitter = Normalized(jitter - dot(jitter,norm)*norm);

        //Add point to both sides
        Vector3 first = centroid + offset*norm + offset*jitter*0.2*rnd();
        Vector3 second = centroid - offset*norm + offset*jitter*0.2*rnd();
        
        con.put(particles,(double) first[0], (double) first[1], (double) first[2]);
        con.put(particles + 1,(double) second[0],(double) second[1], (double) second[2]);
        
        particles += 2;
    }

    std::cout << "Triangles: " << particles << std::endl;
    //Particles under the terrain
    
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            double x_block = min[0] + i*sizeX - 0.5*sizeX;
            double y_block = min[1] + j*sizeY - 0.5*sizeY;
            double t = hf -> Height(Vector2(x_block,y_block));
            t = 1.0 - (max[2] - t)/(max[2] - min[2]);
            
            int actSamples = ceil(1.0 + zSamples*t);
            
            for (int k = 0; k < actSamples; ++k) {
                x = x_block + rnd()*(sizeX) - 0.5*sizeX;
                y = y_block + rnd()*(sizeY) - 0.5*sizeY;
                double z_max = hf -> Height(Vector2(x,y)) - block/2;
                
                z = min[2] - 4*offset + rnd()*(z_max - min[2] + 2*offset);
                
                con.put(particles,x,y,z);
                ++particles;
            }
        }
    }


    c_loop_all loopAll(con);
    std::cout << "number of particles: " << particles << " " << con.total_particles() << std::endl;
     
    if(!loopAll.start()) return;
    graph -> setNumCells(particles);
    do {
        voronoicell_neighbor c;
        //std::cout << "a" << std::endl;
        con.compute_cell(c,loopAll);
        double cellX = loopAll.x();
        double cellY = loopAll.y();
        double cellZ = loopAll.z();
        double z_max = hf -> Height(Vector2(cellX,cellY));

        if (cellZ <= z_max) graph -> addCell(c,cellX, cellY, cellZ, loopAll.pid(), false);
        else graph -> addCell(c,cellX, cellY, cellZ, loopAll.pid(), true);
        
    }while (loopAll.inc()); 
    std::cout << "Decomposition ended" << std::endl;

}

void Voronoi::cellSamplingVoronoi(const HeightField* hf,CellGraph* graph) {
    std::cout << "Starting!" << std::endl;
    Box3 domain = hf -> getBox();
    Vector3 min = domain.getMin();
    Vector3 max = domain.getMax();
    ScalarField2 roughness = hf -> SurfaceRoughnessSAT(32, false);

    int nx = hf -> getSizeX();
    int ny = hf -> getSizeY();
    double sizeX = hf -> getCellSize()[0];
    double sizeY = hf -> getCellSize()[1];
    int nz = (max[2] - min[2])/sizeX; 

    int block = 1;
    double offset = 0.75*Norm(hf->getCellSize());
    int zSamples = 16;

    container con(min[0],max[0], min[1],max[1], min[2] - 4*offset,max[2] + 4*offset, nx, ny, nz, false, false, false, 2);

    int particles = 0;

    double x,y,z;
    

    //HeightFieldWall hf_wall(hf);
    //con.add_wall(hf_wall);

    
    //Two particles per cell
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            x = min[0] + i*sizeX - 0.5*sizeX;
            y = min[1] + j*sizeY - 0.5*sizeY;
            z = hf -> Height(Vector2(x,y));

            Vector3 centroid =  Vector3(x,y,z);
            Vector3 norm = hf -> Normal(Vector2(x,y));
            Vector3 jitter = Vector3(rnd(),rnd(),rnd());
            jitter = Normalized(jitter - dot(jitter,norm)*norm);

            //Add point to both sides
            Vector3 first = centroid + offset*norm + offset*jitter*0.2*rnd();
            Vector3 second = centroid - offset*norm + offset*jitter*0.2*rnd();
            
            con.put(particles,(double) first[0], (double) first[1], (double) first[2]);
            con.put(particles + 1,(double) second[0],(double) second[1], (double) second[2]);
            
            particles += 2;
        }
    }

    std::cout << "Triangles: " << particles << std::endl;
    //Particles under the terrain
    
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            double x_block = min[0] + i*sizeX - 0.5*sizeX;
            double y_block = min[1] + j*sizeY - 0.5*sizeY;
            double t = hf -> Height(Vector2(x_block,y_block));
            t = 1.0 - (max[2] - t)/(max[2] - min[2]);
            
            int actSamples = ceil(1.0 + zSamples*t);
            
            for (int k = 0; k < actSamples; ++k) {
                x = x_block + rnd()*(sizeX) - 0.5*sizeX;
                y = y_block + rnd()*(sizeY) - 0.5*sizeY;
                double z_max = hf -> Height(Vector2(x,y)) - block/2;
                
                z = min[2] - 4*offset + rnd()*(z_max - min[2] + 3*offset);
                
                con.put(particles,x,y,z);
                ++particles;
            }
        }
    }


    c_loop_all loopAll(con);
    std::cout << "number of particles: " << particles << " " << con.total_particles() << std::endl;
     
    if(!loopAll.start()) return;
    graph -> setNumCells(particles);
    do {
        voronoicell_neighbor c;
        //std::cout << "a" << std::endl;
        con.compute_cell(c,loopAll);
        double cellX = loopAll.x();
        double cellY = loopAll.y();
        double cellZ = loopAll.z();
        double z_max = hf -> Height(Vector2(cellX,cellY));

        if (cellZ <= z_max) graph -> addCell(c,cellX, cellY, cellZ, loopAll.pid(), false);
        else graph -> addCell(c,cellX, cellY, cellZ, loopAll.pid(), true);
        
    }while (loopAll.inc()); 
    std::cout << "Decomposition ended" << std::endl;

}


void Voronoi::toyVoronoi(const HeightField *hf, CellGraph *graph) {
      
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

    container con(min[0],max[0], min[1],max[1], min[2] - 4*offset,max[2] + 2*offset, nx, ny, nz, false, false, false, 2);

    int particles = 0;

    double x,y,z;

    for (int i = 0; i < nx; ++i) {
        x = min[0] + i*sizeX;
        y = 0;
        double max_z = hf -> Height(Vector2(x,y));
        for (int k = 0; k < zSamples; ++k) {
            
            z = min[2] - 4*offset + rnd()*(max[2] - min[2] + 6*offset);
                
               
            con.put(particles,x,y,z);
            ++particles;
        }

    }

    c_loop_all loopAll(con);
    std::cout << "number of particles: " << particles << " " << con.total_particles() << std::endl;
     
    if(!loopAll.start()) return;
    graph -> setNumCells(particles);
    do {
        voronoicell_neighbor c;
        //std::cout << "a" << std::endl;
        con.compute_cell(c,loopAll);
        double cellX = loopAll.x();
        double cellY = loopAll.y();
        double cellZ = loopAll.z();
        double z_max = hf -> Height(Vector2(cellX,cellY));

        if (cellZ <= z_max) graph -> addCell(c,cellX, cellY, cellZ, loopAll.pid(), false);
        else graph -> addCell(c,cellX, cellY, cellZ, loopAll.pid(), true);
        
    }while (loopAll.inc()); 
    std::cout << "Decomposition ended" << std::endl;
}

void Voronoi::voronoiFromCentroids(const std::vector<Vector3> centroids, CellGraph* graph, const HeightField* hf) {
     Box3 domain = hf -> getBox();
    Vector3 min = domain.getMin();
    Vector3 max = domain.getMax();

    int nx = hf -> getSizeX();
    int ny = hf -> getSizeY();
    double sizeX = hf -> getCellSize()[0];
    double sizeY = hf -> getCellSize()[1];
    int nz = (max[2] - min[2])/sizeX; 
    
    container con(min[0],max[0], min[1],max[1], min[2],max[2], nx, ny, nz, false, false, false, 2);
    int particles = centroids.size();

    for (int i = 0; i < particles; ++i) {
        con.put(i, centroids[i][0],centroids[i][1],centroids[i][2]);
    }

    c_loop_all loopAll(con);

    
    if(!loopAll.start()) return;
    graph -> setNumCells(particles);
    do {
        voronoicell_neighbor c;
        //std::cout << "a" << std::endl;
        con.compute_cell(c,loopAll);
        double cellX = loopAll.x();
        double cellY = loopAll.y();
        double cellZ = loopAll.z();
        double z_max = hf -> Height(Vector2(cellX,cellY));

        if (cellZ <= z_max) graph -> addCell(c,cellX, cellY, cellZ, loopAll.pid(), false);
        else graph -> addCell(c,cellX, cellY, cellZ, loopAll.pid(), true);
        
    }while (loopAll.inc()); 
}