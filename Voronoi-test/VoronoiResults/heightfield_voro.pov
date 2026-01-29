#version 3.6;

#include "colors.inc"
#include "metals.inc"
#include "textures.inc"

global_settings {
	max_trace_level 32
}

camera {
	location <-602,-552,3160.58>
	look_at <0,0,2752.2>
	sky   <0,0,1>
}

background{rgb 1}

light_source{<-602,-552,3160.58> color rgb <0.77,0.75,0.75>}


#declare r=0.75;
#declare s=2;

union{
#include "heightfield_voro_p.pov"
	scale 1
	rotate <0,0,0>
	texture{T_Silver_3C}
}

union{
#include "heightfield_voro_v.pov"
	scale 1
	rotate <0,0,0>
	pigment{rgb <0.3,0.3,0.9>} finish{phong 0.9 ambient 0.42 reflection 0.1}
}
