// Version du GLSL
#version 330 core

// Entrées
in vec3 in_Vertex;
in vec3 in_Normals;
in vec3 in_Uv;


// Uniform
uniform mat4 MV;
uniform mat4 P;

// Fonction main
void main()
{
    // Position finale du vertex en 3D

    gl_Position = P * MV * vec4(in_Vertex, 1.0);
	
}