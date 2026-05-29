#version 410 core

uniform vec2 u_worldMin;
uniform vec2 u_worldSize;
uniform sampler2D u_texture;
uniform float u_cursorRadius;
uniform vec2  u_cursorWorld;
uniform vec4  u_cursorColor;
uniform vec3 u_color;
uniform float u_alpha;

in vec3 gWorldPos;
in vec3 gNormal;

out vec4 fragment;

void main()
{
    vec2 uv = (gWorldPos.xy - u_worldMin)/u_worldSize;
    vec4 c = texture(u_texture, uv);
    if (u_cursorRadius > 0) {
        float d = length(u_cursorWorld - gWorldPos.xy);
        float t = smoothstep(u_cursorRadius, 0.5*u_cursorRadius, d);
        vec4 ccursor = (1 - u_cursorColor.a)*c + u_cursorColor.a*u_cursorColor;
        c = mix(c, ccursor, t);
    }
    fragment = vec4(u_color*gNormal.z, u_alpha);
    //fragment = vec4(0.1, gl_FragCoord.z/3, 0.2, 1.0);
}
