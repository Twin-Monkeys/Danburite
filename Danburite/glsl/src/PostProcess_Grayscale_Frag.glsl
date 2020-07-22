#version 460 core

#include "header/PostProcess_Header.glsl"
#include "header/Grayscale_Header.glsl"
 
out vec3 fragColor;

void main()
{
	fragColor = PostProcess_getRectPixel(0, gl_FragCoord.xy).rgb;
	fragColor = vec3(Grayscale_getGrayscaledColor(fragColor));
} 