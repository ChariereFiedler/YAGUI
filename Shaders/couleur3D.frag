// Version du GLSL

#version 330 core

// Entr�e

in vec3 color;
in vec3 oeilDirection_camera;
in vec3 lumDirection_camera;
in vec3 normal_camera;
in float distance;

in vec4 ombreCoord;
// Uniform

uniform vec3 lumCouleur;
uniform float lumPuissance;

uniform sampler2DShadow shadowMap;

// Sortie 

layout(location = 0)out vec4 out_Color;

vec2 poissonDisk[16] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 ), 
   vec2( -0.91588581, 0.45771432 ), 
   vec2( -0.81544232, -0.87912464 ), 
   vec2( -0.38277543, 0.27676845 ), 
   vec2( 0.97484398, 0.75648379 ), 
   vec2( 0.44323325, -0.97511554 ), 
   vec2( 0.53742981, -0.47373420 ), 
   vec2( -0.26496911, -0.41893023 ), 
   vec2( 0.79197514, 0.19090188 ), 
   vec2( -0.24188840, 0.99706507 ), 
   vec2( -0.81409955, 0.91437590 ), 
   vec2( 0.19984126, 0.78641367 ), 
   vec2( 0.14383161, -0.14100790 ) 
);
// Fonction main

void main()
{
	vec3 n = normalize( normal_camera );
	vec3 l = normalize( lumDirection_camera );
	float cosTheta = clamp( dot( n , l ), 0 , 1 );
	// Fixed bias, or...
	float bias = 0.005;
	float v = 1;
	
	for(int i = 0; i < 8 ; ++i){
		v -= 0.1 * (1.0 - texture(shadowMap, vec3(ombreCoord.xy + poissonDisk[i]/700.0, (ombreCoord.z - bias)/ombreCoord.w) ));
	}
	
	vec3 color2 =  color * ( vec3(0.05,0.05,0.05) + v * lumPuissance * lumCouleur * cosTheta / (distance*5) );
    out_Color = vec4(color2,1.0);
}

