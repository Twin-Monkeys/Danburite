//? #version 460 core

#ifndef __LIGHT_PREPASS_HEADER__
#define __LIGHT_PREPASS_HEADER__

#extension GL_ARB_bindless_texture : require

#include "Constant_Header.glsl"

layout(std140, binding = BINDING_POINT_LIGHT_PREPASS) uniform UBLightPrePass
{
	layout(offset = 0) uvec2 ambientTex;
	layout(offset = 16) uvec2 diffuseTex;
	layout(offset = 32) uvec2 specularTex;
	layout(offset = 48) uint lightVolumeType;
	layout(offset = 64) uint currentLightIdx;
}
lightPrePass;

uint LightPrePass_getLightVolumeType()
{
	return lightPrePass.lightVolumeType;
}

uint LightPrePass_getCurrentLightIdx()
{
	return lightPrePass.currentLightIdx;
}

vec3 LightPrePass_getLightAmbient(const vec2 screenCoord)
{
	return texture(sampler2DRect(lightPrePass.ambientTex), screenCoord).rgb;
}

vec3 LightPrePass_getLightDiffuse(const vec2 screenCoord)
{
	return texture(sampler2DRect(lightPrePass.diffuseTex), screenCoord).rgb;
}

vec3 LightPrePass_getLightSpecular(const vec2 screenCoord)
{
	return texture(sampler2DRect(lightPrePass.specularTex), screenCoord).rgb;
}

#endif