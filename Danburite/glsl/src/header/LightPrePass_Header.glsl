//? #version 460 core

#ifndef __LIGHT_PREPASS_HEADER__
#define __LIGHT_PREPASS_HEADER__

#extension GL_ARB_bindless_texture : require

#include "Constant_Header.glsl"

struct LightPrePass_LightVolume
{
	uint type;
};

struct LightPrePass_LightingPass
{
	uint currentLightIdx;
	uvec2 lightAmbientTex;
	uvec2 lightDiffuseTex;
	uvec2 lightSpecularTex;
};

layout(binding = BINDING_POINT_LIGHT_PREPASS) uniform UBLightPrePass
{
	LightPrePass_LightVolume lightPrePass_lightVolume;
	LightPrePass_LightingPass lightPrePass_lightingPass;
};

uint LightPrePass_getLightVolumeType()
{
	return lightPrePass_lightVolume.type;
}

uint LightPrePass_getCurrentLightIdx()
{
	return lightPrePass_lightingPass.currentLightIdx;
}

vec3 LightPrePass_getLightAmbient(const vec2 screenCoord)
{
	return texture(sampler2DRect(lightPrePass_lightingPass.lightAmbientTex), screenCoord).rgb;
}

vec3 LightPrePass_getLightDiffuse(const vec2 screenCoord)
{
	return texture(sampler2DRect(lightPrePass_lightingPass.lightDiffuseTex), screenCoord).rgb;
}

vec3 LightPrePass_getLightSpecular(const vec2 screenCoord)
{
	return texture(sampler2DRect(lightPrePass_lightingPass.lightSpecularTex), screenCoord).rgb;
}

#endif