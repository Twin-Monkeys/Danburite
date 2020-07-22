#version 460 core

#include "header/MSAA_Header.glsl"

out vec3 fragColor;

void main()
{
	fragColor = vec3(0.f);

	for (uint i = 0; i < NUM_SAMPLE_POINTS; i++)
		fragColor += MSAA_getPixel(0, ivec2(gl_FragCoord.xy), int(i)).rgb;

	fragColor /= float(NUM_SAMPLE_POINTS);
} 