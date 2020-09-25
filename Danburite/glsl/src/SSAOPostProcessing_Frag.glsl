#version 460 core

#include "header/TextureContainer_Header.glsl"
#include "header/SSAO_Header.glsl"
 
out float postProcessedAmbientOcclusionInv;

void main()
{
	const ivec2 screenCoord = ivec2(gl_FragCoord.xy);
	const sampler2DRect ambientOcclusionInvTex = TextureContainer_getTextureAs2DRect(0);

	postProcessedAmbientOcclusionInv = SSAO_getPostProcessedAmbientOcclusionInv(screenCoord, ambientOcclusionInvTex);
} 