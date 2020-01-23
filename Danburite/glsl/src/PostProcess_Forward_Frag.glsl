#version 460 core

#include "header/PostProcess_Header.glsl"
 
in vec2 texCoord;
out vec4 fragColor;

void main()
{
	fragColor = PostProcess_getPixel(0, texCoord);
} 