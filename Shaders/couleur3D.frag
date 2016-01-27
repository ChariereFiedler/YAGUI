// Version du GLSL

#version 330 core

// Entr�e
// Sortie

in vec3 normals;
in float specular;

uniform mat4 MV;

out vec4 out_Color;
// Fonction main

void main()
{
    out_Color = vec4(1.0) * specular + vec4(0.3,0.18,0.1,1);
}

