#version 460 core

#include "header/TextureContainer_Header.glsl"
 
out vec4 outColor;

void main()
{
	const sampler2DRect accumulationTex = TextureContainer_getTextureAs2DRect(0);
	const sampler2DRect revealageTex = TextureContainer_getTextureAs2DRect(1);

	const vec4 accumulation = texture(accumulationTex, gl_FragCoord.xy);
	const float revealage = texture(revealageTex, gl_FragCoord.xy).r;

	if (accumulation.a < EPSILON)
		discard;

	outColor.rgb = (accumulation.rgb / accumulation.a);
	outColor.a = (1.f - revealage);
} 