#version 460 core

#include "header/PostProcess_Header.glsl"
#include "header/GammaCorrection_Header.glsl"

out vec3 fragColor;

void main()
{
	fragColor = PostProcess_getRectPixel(0, gl_FragCoord.xy).rgb;
	fragColor = pow(fragColor, vec3(1.f / GammaCorrection_getGamma()));
} 