#version 410 core

in vec3 a_position;

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;

out vec3 worldPos;

void main(void)
{
    mat4 MVP    = ProjectionMatrix * ViewMatrix * ModelMatrix;
    gl_Position = MVP * (vec4(a_position, 1.0));
    worldPos    = a_position;
} 
