#include "heightfieldWall.h"
using namespace voro;

bool HeightFieldWall::point_inside(double x, double y, double z) {
    double height = hf -> Height(Vector2(x,y), false);
    return z < height;
}

template<class vc_class> inline bool HeightFieldWall::cut_cell_base(vc_class &c, double x, double y, double z) {
    if (!point_inside(x,y,z)) return false;
    Vector3 norm = hf -> Normal(Vector2(x,y), false); 
    double height = hf -> Height(Vector2(x,y), false);
    double cos_a = dot(norm, Vector3(0,0,1));
    double dist = (height - z)*cos_a;

    return c.nplane(norm[0], norm[1], norm[2], dist*dist,w_id);
}
