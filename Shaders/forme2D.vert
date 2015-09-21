// Version du GLSL
#version 410 core

// Entrées
layout(location = 0)in vec2 in_Vertex;
layout(location = 1)in vec2 in_Pos;
layout(location = 2)in vec3 in_Color;
layout(location = 3)in float in_Angle;
layout(location = 4)in float in_Size;


uniform mat4 P;

layout(location = 0) out vec3 out_color;

// Fonction main
void main()
{
    // Position finale du vertex en 3D
    float angle = in_Angle / 360;
    float cos = cos(angle);
    float sin = sin(angle);
    mat2 transform =  in_Size * mat2( vec2( cos, sin), vec2(  -sin , cos ));

    gl_Position = P * vec4( in_Vertex * transform + in_Pos  ,1.0,1.0) ;

    out_color = in_Color;

}