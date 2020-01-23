#version 460 core

#include "header/Material_Header.glsl"

layout(early_fragment_tests) in;
 
out vec4 fragColor;

void main()
{
	fragColor = material.outlineColor;
} 