#include "voronoi.h"
#include<vector>
using namespace voro;



// This function returns a random double between 0 and 1
double rnd() {return double(rand())/RAND_MAX;}

double maxElevation(HeightField *hf) {

}

void Voronoi::heightfieldVoronoi(HeightField *hf) {
    
    std::cout << "Starting!" << std::endl;
    Box3 domain = hf -> getBox();
    Vector3 min = domain.getMin();
    Vector3 max = domain.getMax();

    int nx = hf -> getSizeX();
    int ny = hf -> getSizeY();
    double sizeX = hf -> getCellSize()[0];
    int nz = (max[2] - min[2])/sizeX; 
    int particles = nx*ny*nz/10000;

    container con(min[0],max[0], min[1],max[1], min[2],max[2], nx, ny, nz, false, false, false, 2);
    HeightFieldWall hf_wall(hf);
    con.add_wall(hf_wall);

    double x,y,z;
    std::cout << "number of particles: " << particles << std::endl;
    for (int i = 0; i < particles; ++i) {
        x = min[0]+rnd()*(max[0]-min[0]);
        y = min[1]+rnd()*(max[1]-min[1]);
        z = min[2]+rnd()*(max[2]-min[2]);
        if(hf_wall.point_inside(x,y,z)) con.put(i,x,y,z);
        
    }

    std::cout << "Drawing particles into heightfield_voro_p.pov" << std::endl;
    // Output the particle positions in gnuplot format
    con.draw_particles_pov("heightfield_voro_p.pov");
 
    std::cout << "Drawing cells into heightfield_voro_v.pov" << std::endl;
    // Output the Voronoi cells in gnuplot format
    con.draw_cells_pov("heightfield_voro_v.pov");

    std::cout << "Drawing particles into heightfield_voro_p.gnu" << std::endl;
    // Output the particle positions in gnuplot format
    con.draw_particles("heightfield_voro_p.gnu");
 
    std::cout << "Drawing cells into heightfield_voro_v.gnu" << std::endl;
    // Output the Voronoi cells in gnuplot format
    con.draw_cells_gnuplot("heightfield_voro_v.gnu");

    std::cout << "Done!" << std::endl;
}

void Voronoi::tethraedronTest() {
    const int particles=64;
    const int n_x=7,n_y=7,n_z=7;
    const double x_min=-2,x_max=2;
    const double y_min=-2,y_max=2;
    const double z_min=-2,z_max=2;

    int i=0;
    double x,y,z;

    // Create a container with the geometry given above, and make it
    // non-periodic in each of the three coordinates. Allocate space for 8
    // particles within each computational block.
    container con(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,
                       false,false,false,8);
    // Add four plane walls to the container to make a tetrahedron
    wall_plane p1(1,1,1,1);con.add_wall(p1);
    wall_plane p2(-1,-1,1,1);con.add_wall(p2);
    wall_plane p3(1,-1,-1,1);con.add_wall(p3);
    wall_plane p4(-1,1,-1,1);con.add_wall(p4);
 
    // Randomly insert particles into the container, checking that they lie
    // inside the tetrahedron
    while(i<particles) {
        x=x_min+rnd()*(x_max-x_min);
        y=y_min+rnd()*(y_max-y_min);
        z=z_min+rnd()*(z_max-z_min);
        if (con.point_inside(x,y,z)) {
            con.put(i,x,y,z);i++;
        }
    }

    // Output the particle positions and the Voronoi cells in Gnuplot and
    // POV-Ray formats
    con.draw_particles("tetrahedron_p.gnu");
    con.draw_cells_gnuplot("tetrahedron_v.gnu");
    con.draw_particles_pov("tetrahedron_p.pov");
    con.draw_cells_pov("tetrahedron_v.pov");
}

void Voronoi::randomPointsTest() {
    int i;
    double x,y,z;
    const int particles=20;
    const int n_x=6,n_y=6,n_z=6;
    const double x_min=-1,x_max=1;
    const double y_min=-1,y_max=1;
    const double z_min=-1,z_max=1;
    const double cvol=(x_max-x_min)*(y_max-y_min)*(x_max-x_min);
 
    // Create a container with the geometry given above, and make it
    // non-periodic in each of the three coordinates. Allocate space for
    // eight particles within each computational block
    container con(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,
                         false,false,false,8);
 
    // Randomly add particles into the container
    for(i=0;i<particles;i++) {
        x=x_min+rnd()*(x_max-x_min);
        y=y_min+rnd()*(y_max-y_min);
        z=z_min+rnd()*(z_max-z_min);
        con.put(i,x,y,z);
    }
 
    // Sum up the volumes, and check that this matches the container volume
    double vvol=con.sum_cell_volumes();
    printf("Container volume : %g\n"
                "Voronoi volume   : %g\n"
                "Difference       : %g\n",cvol,vvol,vvol-cvol);
 
    // Output the particle positions in gnuplot format
    con.draw_particles_pov("random_points_p.pov");
 
    // Output the Voronoi cells in pov format
    con.draw_cells_pov("random_points_v.pov");
}