#version 460 core

#include "header/PostProcess_Header.glsl"
#include "header/Bloom_Header.glsl"

out vec3 fragColor;

void main()
{
	 const vec3 originalColor = PostProcess_getRectPixel(0, gl_FragCoord.xy).rgb;
	 const vec3 bloomColor = PostProcess_getRectPixel(1, gl_FragCoord.xy).rgb;

	 fragColor = (originalColor + (bloomColor * Bloom_getEffectStrength()));
} 