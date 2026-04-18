#version 410 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 vWorldPos[];
out vec3 gNormal;
out vec3 gWorldPos;

void main( void )
{
	vec3 a = vec3(gl_in[1].gl_Position) - vec3(gl_in[0].gl_Position);
   	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[0].gl_Position);
   	gNormal = normalize(cross(a, b));

	for( int i = 0 ; i < 3 ; i++ )
	{
		gWorldPos = vWorldPos[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}
