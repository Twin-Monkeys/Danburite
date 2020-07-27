#version 460 core

#include "header/TextureContainer_Header.glsl"

out vec3 fragColor;

void main()
{
	fragColor = vec3(0.f);

	const sampler2DMS srcTex = TextureContainer_getTextureAs2DMS(0);

	for (uint i = 0; i < NUM_SAMPLE_POINTS; i++)
		fragColor += texelFetch(srcTex, ivec2(gl_FragCoord.xy), int(i)).rgb;

	fragColor /= float(NUM_SAMPLE_POINTS);
} 