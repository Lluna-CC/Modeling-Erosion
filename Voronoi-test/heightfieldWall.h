#include "voro++.hh"
#include "heightfield.h"
#include "core.h"
using namespace voro;

class HeightFieldWall: public wall {
public:

    HeightFieldWall(HeightField* height, int iw_id = -99) {
        hf = height;
        w_id = iw_id;
    }

    bool point_inside(double x, double y, double z);

    template<class vc_class> inline bool cut_cell_base(vc_class &c, double x, double y, double z);
    bool cut_cell(voronoicell &c,double x, double y,double z) {return cut_cell_base(c,x,y,z);}
    bool cut_cell(voronoicell_neighbor &c,double x,double y,double z) {return cut_cell_base(c,x,y,z);}
private:

    HeightField *hf;
    int w_id;
};