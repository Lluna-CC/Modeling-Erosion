#include "heightfieldWall.h"
#include <queue>
#define M_PI 3.14159265358979323846  /* pi */
using namespace voro;


template<class vc_class> bool HeightFieldWall::cutNClosestPlanes(Vector3 p, int n, vc_class& c, int nDistances, int nAngles) {
    double height = hf -> Height(Vector2(p[0],p[1]), true);
    Vector3 bMin = hf -> getBox().getMin();
    Vector3 bMax = hf -> getBox().getMax();

    double deltaAlpha = 2*M_PI/nAngles;
    double deltaR = height/nDistances;

    std::priority_queue<std::pair<double,std::pair<double,double>>> nearest;
    
    nearest.push(std::make_pair(height,std::make_pair(p[0],p[1])));
    for (double r = deltaR; r <= height; r += deltaR) {
        for (double alpha = 0; alpha < 2*M_PI; alpha += deltaAlpha) {
            Vector3 sample;
            sample[0] = r * std::cos(alpha);
            if (sample[0] > bMax[0] || sample[0] < bMin[0]) continue;
            sample[1] = r * std::sin(alpha);
            if (sample[1] > bMax[1] || sample[1] < bMin[1]) continue;
            sample[2] = hf -> Height(Vector2(sample[0],sample[1]), true);

            double dist = Norm(sample - p);
            if (nearest.size() < n) nearest.push(std::make_pair(dist, std::make_pair(sample[0],sample[1])));
            else  {
                if (dist < nearest.top().first) {
                    nearest.pop();
                    nearest.push(std::make_pair(dist,std::make_pair(sample[0],sample[1])));
                }
            }
            
        }
    }

    bool ret = true;
    while (nearest.size() > 0) {
        double x = nearest.top().second.first;
        double y = nearest.top().second.second;
        double z = hf -> Height(Vector2(x,y), true);

        Vector3 norm = hf -> Normal(Vector2(x,y), true);
        Vector3 sample = Vector3(x,y,z);

        double dist = dot(norm, sample - p);
        ret = ret && c.nplane(norm[0], norm[1], norm[2], dist*dist,w_id - nearest.size());
        nearest.pop();
    
    }
    return ret;

}

bool HeightFieldWall::point_inside(double x, double y, double z) {
    double height = hf -> Height(Vector2(x,y), false);
    return z <= height;
}

template<class vc_class> inline bool HeightFieldWall::cut_cell_base(vc_class &c, double x, double y, double z) {
    
    if (!point_inside(x,y,z)) return false;
    Vector3 norm = hf -> Normal(Vector2(x,y), true); 
    double height = hf -> Height(Vector2(x,y), true);
    double cos_a = dot(norm, Vector3(0,0,1));
    double dist = (height - z)*cos_a;
    if (z < 0.95*height) return false;

    Vector3 p = Vector3(x,y,z);

    return c.nplane(norm[0], norm[1], norm[2], dist*dist,w_id);
    //return cutNClosestPlanes(p, 50, c, 20, 30);
}
