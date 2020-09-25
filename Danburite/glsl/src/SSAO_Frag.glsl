#version 460 core

#include "header/Camera_Header.glsl"
#include "header/TextureContainer_Header.glsl"
#include "header/SSAO_Header.glsl"
 
out float ambientOcclusionInv;

void main()
{
	const ivec2 screenCoord = ivec2(gl_FragCoord.xy);

	const sampler2DRect posTex = TextureContainer_getTextureAs2DRect(0);
	const sampler2DRect normalTex = TextureContainer_getTextureAs2DRect(1);

	const mat4 viewMat = Camera_getViewMatrix();
	const mat4 projMat = Camera_getProjMatrix();

	const vec3 worldSpaceNormal = texelFetch(normalTex, screenCoord).xyz;
	ambientOcclusionInv = SSAO_getAmbientOcclusionInv(screenCoord, viewMat, projMat, posTex, worldSpaceNormal);
} 