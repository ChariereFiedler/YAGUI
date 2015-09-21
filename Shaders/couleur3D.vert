// Version du GLSL
#version 330 core

// Entrées
(layout location = 0)in vec3 in_Vertex;
in vec3 in_Color;
in vec3 in_Normal;

// Uniform
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 P;

uniform mat4 depthMVP;

uniform vec3 lumPosition;


// Sortie
out vec3 color;
out vec3 oeilDirection_camera;	// Vecteur allant de l'oeil à la caméra
out vec3 lumDirection_camera;
out vec3 normal_camera;
out float distance;

out vec4 ombreCoord;
// Fonction main
void main()
{
    // Position finale du vertex en 3D

    gl_Position = MVP * vec4(in_Vertex, 1.0);
	
	ombreCoord = depthMVP * vec4(in_Vertex, 1.0);
	
	//Vecteur allant du vertex à la caméra
	//La caméra étant l'origine au sein de son propre repère
	vec3 vertex_camera = (V * vec4(in_Vertex,1) ).xyz;
	oeilDirection_camera = vec3(0,0,0) - vertex_camera;
	
	//Vecteur allant du vertex à la lumière
	vec3 lumPosition_camera = ( V * vec4(lumPosition,1)).xyz;
	lumDirection_camera = normalize( oeilDirection_camera);
	normal_camera = normalize( ( V * vec4(in_Normal,0)).xyz);
	
	
	vec3 n = in_Vertex - lumPosition;
	n *= n;
	distance = sqrt( n.x + n.y + n.z);

    // Envoi de la couleur au Fragment Shader
    color = in_Color;
	
}