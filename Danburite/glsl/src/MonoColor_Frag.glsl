#version 460 core

#include "header/Material_Header.glsl"

out vec4 fragColor;

void main()
{
	fragColor = material.diffuseColor;
} 