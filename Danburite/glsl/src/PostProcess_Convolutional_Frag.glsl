#version 460 core

#include "header/PostProcess_Header.glsl"
#include "header/Convolutional_Header.glsl"
 
out vec3 fragColor;

void main()
{
	fragColor = Convolutional_convolve(PostProcess_getRectColorAttachment(0), gl_FragCoord.xy);
} 