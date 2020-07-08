#version 460 core

#include "header/MSAA_Header.glsl"

out vec4 fragColor;

void main()
{
	vec3 retVal = vec3(0.f);
	for (uint i = 0; i < NUM_SAMPLE_POINTS; i++)
		retVal += MSAA_getPixel(0, int(i)).rgb;

	fragColor = vec4(retVal / float(NUM_SAMPLE_POINTS), 1.f);
} 