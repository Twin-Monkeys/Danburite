#version 460 core

#include "header/PostProcess_Header.glsl"
#include "header/Convolutional_Header.glsl"
 
in vec2 texCoord;
out vec4 fragColor;

void main()
{
	fragColor = Convolutional_convolve(PostProcess_getColorAttachment(0), texCoord);
} 