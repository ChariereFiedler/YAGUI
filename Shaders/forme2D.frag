#version 410 core

// Uniform

layout(location = 0)in vec3 in_Color;

// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur du pixel

    out_Color = vec4(in_Color, 1);
}
