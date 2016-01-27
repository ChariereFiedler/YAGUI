// Version du GLSL
#version 330 core

// Entrées
in vec3 in_Vertex;
in vec3 in_Normals;
in vec3 in_Uv;


out float specular;
// Uniform
uniform mat4 MV;
uniform mat4 P;

// Fonction main
void main()
{
    // Position finale du vertex en 3D

    gl_Position = P * MV * vec4(in_Vertex, 1.0);


	vec3 n = in_Vertex - vec3(0,0,5);
	n *= n;

	float distance = sqrt(n.x + n.y + n.z);
	specular = 0.3 + dot(normalize(vec3(0,-1,1)),in_Normals)* (5/ (distance+1));


}